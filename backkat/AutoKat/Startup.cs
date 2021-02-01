using AutoKat.Core.DependencyInjection;
using AutoKat.Data;
using AutoKat.Data.Sessions;
using AutoKat.Infrastructure.Authentication;
using AutoKat.Infrastructure.HttpContext;
using AutoKat.Infrastructure.Users;
using Microsoft.AspNetCore.Authentication.JwtBearer;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Hosting;
using Microsoft.AspNetCore.HttpOverrides;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using Microsoft.IdentityModel.Tokens;
using System.IdentityModel.Tokens.Jwt;
using System.Text;
using System.Text.Json.Serialization;
using System.Threading.Tasks;

namespace AutoKat
{
	public class Startup
	{
		public Startup(IConfiguration configuration)
		{
			Configuration = configuration;
		}

		public IConfiguration Configuration { get; }

		// This method gets called by the runtime. Use this method to add services to the container.
		public void ConfigureServices(IServiceCollection services)
		{
			services.AddCors();

			services
				.AddControllers()
				.AddJsonOptions(options =>
				{
					options.JsonSerializerOptions.Converters.Add(new JsonStringEnumConverter());
				});

			services.AddHttpContextAccessor();
			services.Scan(
				x => x.FromApplicationDependencies()
					.AddClasses(x => x.AssignableTo<ITransientService>())
						.AsImplementedInterfaces()
						.WithTransientLifetime()
			);

			services.AddDbContext<AutoKatContext>(
				options => options.UseNpgsql(Configuration.GetConnectionString("AutoKat"))
			);

			var jwtSecret = Configuration.GetValue<string>("JwtSecret");
			services.AddAuthentication(JwtBearerDefaults.AuthenticationScheme)
				.AddJwtBearer(options =>
				{
					options.TokenValidationParameters = new TokenValidationParameters
					{
						ValidateIssuer = false,
						ValidateAudience = false,
						ValidateLifetime = true,
						ValidateIssuerSigningKey = true,

						IssuerSigningKey = new SymmetricSecurityKey(
							Encoding.UTF8.GetBytes(jwtSecret)
						)
					};

					options.Events = new JwtBearerEvents
					{
						OnMessageReceived = context =>
						{
							var cookies = context.HttpContext.Request.Cookies;
							var cookie = cookies["Token"];
							if (!string.IsNullOrEmpty(cookie))
							{
								context.Token = cookie;
							}

							return Task.CompletedTask;
						},
						OnTokenValidated = async context =>
						{
							if (context.Result == null || !context.Result.Succeeded)
							{
								return;
							}

							var accessToken = context.SecurityToken as JwtSecurityToken;
							if (accessToken == null)
							{
								return;
							}

							var authenticationService = context.HttpContext.RequestServices.GetRequiredService<IAuthenticationService>();
							var userService = context.HttpContext.RequestServices.GetRequiredService<IUserService>();
							var user = await userService.GetCurrentUser();
							if (!await authenticationService.ValidateTokenWithSession(accessToken.RawCiphertext, user))
							{
								context.Fail("Invalid session for this token.");
								return;
							}
						},
						OnAuthenticationFailed = context =>
						{
							if (context.Exception.GetType() == typeof(SecurityTokenExpiredException))
							{
								context.Response.Headers.Add("Token-Expired", "true");
							}

							return Task.CompletedTask;
						}
					};
				});

			services.AddTransient<IAuthenticationService>(serviceProvider =>
				new AuthenticationService(
					jwtSecret,
					Configuration.GetValue<int>("JwtLifespan"),
					serviceProvider.GetRequiredService<IHttpContextService>(),
					serviceProvider.GetRequiredService<ISessionRepository>()
				)
			);
		}

		// This method gets called by the runtime. Use this method to configure the HTTP request pipeline.
		public void Configure(IApplicationBuilder app, IWebHostEnvironment env)
		{
			if (env.IsDevelopment())
			{
				app.UseDeveloperExceptionPage();
				app.UseCors(builder =>
				{
					builder
						.SetIsOriginAllowed(x => true)
						.AllowCredentials()
						.AllowAnyHeader()
						.AllowAnyMethod();
				});
			}

			app.UseForwardedHeaders(new ForwardedHeadersOptions
			{
				ForwardedHeaders = ForwardedHeaders.XForwardedFor | ForwardedHeaders.XForwardedProto
			});

			app.UseHttpsRedirection();

			app.UseRouting();

			app.UseAuthentication();
			app.UseAuthorization();

			app.UseEndpoints(endpoints =>
			{
				endpoints.MapControllers();
			});
		}
	}
}
