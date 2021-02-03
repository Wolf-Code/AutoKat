using AutoKat.Core.Utilities.DateTime;
using AutoKat.Data.Sessions;
using AutoKat.Data.Users;
using AutoKat.Data.Users.Entities;
using AutoKat.Domain.Authentication;
using AutoKat.Domain.Translations;
using AutoKat.Domain.Users;
using AutoKat.Infrastructure.Authentication;
using AutoKat.Infrastructure.Cryptography;
using AutoKat.Infrastructure.HttpContext;
using AutoKat.Infrastructure.Users.Exceptions;
using System;
using System.Threading.Tasks;

namespace AutoKat.Infrastructure.Users
{
	public class UserService : IUserService
	{
		private readonly IUserRepository userRepository;
		private readonly ICryptographyService cryptographyService;
		private readonly IAuthenticationService authenticationService;
		private readonly IHttpContextService httpContextService;
		private readonly ISessionRepository sessionRepository;
		private readonly IDateTimeProvider dateTimeProvider;

		public UserService(
			IUserRepository userRepository,
			ICryptographyService cryptographyService,
			IAuthenticationService authenticationService,
			IHttpContextService httpContextService,
			ISessionRepository sessionRepository,
			IDateTimeProvider dateTimeProvider
		)
		{
			this.userRepository = userRepository;
			this.cryptographyService = cryptographyService;
			this.authenticationService = authenticationService;
			this.httpContextService = httpContextService;
			this.sessionRepository = sessionRepository;
			this.dateTimeProvider = dateTimeProvider;
		}

		public async Task<User> GetCurrentUser(bool throwIfNone = true)
		{
			var userEmail = this.httpContextService.GetCurrentUserEmail();
			if (userEmail != null)
			{
				return await this.userRepository.FindByEmail(userEmail);
			}

			if (throwIfNone)
			{
				throw new NoSignedInUserException();
			}

			return null;
		}

		public async Task<UserPreferences> GetCurrentUserPreferences()
		{
			var user = await this.GetCurrentUser();

			return user.Preferences;
		}

		public async Task<UserLoginResult> LoginUser(UserLogin login)
		{
			var user = await this.userRepository.FindByEmail(login.Email);
			if (user == null)
			{
				return new UserLoginResult(AuthenticationTranslations.EmailOrPasswordIncorrect);
			}

			if (!string.Equals(this.cryptographyService.Hash(login.Password, user.Salt), user.Password))
			{
				return new UserLoginResult(AuthenticationTranslations.EmailOrPasswordIncorrect);
			}

			var authData = await this.GetTokens(user);
			return new UserLoginResult(authData);
		}

		private async Task<AuthenticationData> GetTokens(User user)
		{
			var refreshToken = this.authenticationService.GetAuthenticationData(user, null);
			var token = this.authenticationService.GetAuthenticationData(user, refreshToken.Token);
			token.RefreshToken = refreshToken.Token;

			var ip = this.httpContextService.GetCurrentUserIpAddress();
			var now = this.dateTimeProvider.NowUtc;
			var duration = DateTimeOffset.FromUnixTimeSeconds(refreshToken.TokenExpirationTime).UtcDateTime - now;
			await this.sessionRepository.StartNewSession(user, refreshToken.Token, ip, duration.TotalSeconds);

			return new AuthenticationData
			{
				Token = token.Token,
				Id = token.Id,
				TokenExpirationTime = token.TokenExpirationTime,
				RefreshToken = refreshToken.Token
			};
		}

		public async Task LogoutUser()
		{
			var user = await this.GetCurrentUser();
			var token = this.httpContextService.GetCookieRefreshToken();
			var ip = this.httpContextService.GetCurrentUserIpAddress();

			await this.sessionRepository.EndActiveSession(user, token, ip);
		}

		public async Task<UserRegistrationResult> RegisterUser(UserRegistration newUser)
		{
			if (newUser.EmailConfirmation != newUser.Email)
			{
				return new UserRegistrationResult(AuthenticationTranslations.EmailConfirmationIsIncorrect);
			}

			var existingUser = await this.userRepository.FindByEmail(newUser.Email);
			if (existingUser != null)
			{
				return new UserRegistrationResult(string.Format(AuthenticationTranslations.EmailAlreadyInUse, newUser.Email));
			}

			var salt = this.cryptographyService.GetNewSalt();

			var user = await this.userRepository.Insert(new User
			{
				Email = newUser.Email.ToLower(),
				Password = this.cryptographyService.Hash(newUser.Password, salt),
				Salt = salt,
				Preferences = new UserPreferences()
			});

			return new UserRegistrationResult();
		}

		public Task<UserInformationResult> GetCurrentUserInformation()
		{
			throw new NotImplementedException();
		}
	}
}
