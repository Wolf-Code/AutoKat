using AutoKat.Core.Users;
using Microsoft.EntityFrameworkCore.Migrations;
using Npgsql.EntityFrameworkCore.PostgreSQL.Metadata;
using System;
using System.Net;

namespace AutoKat.Data.Migrations
{
	public partial class InitialCreate : Migration
	{
		protected override void Up(MigrationBuilder migrationBuilder)
		{
			migrationBuilder.CreateTable(
				name: "User",
				columns: table => new
				{
					Id = table.Column<int>(type: "integer", nullable: false)
						.Annotation("Npgsql:ValueGenerationStrategy", NpgsqlValueGenerationStrategy.IdentityByDefaultColumn),
					Email = table.Column<string>(type: "text", nullable: false),
					Password = table.Column<string>(type: "character varying(128)", maxLength: 128, nullable: false),
					Salt = table.Column<byte[]>(type: "bytea", nullable: false),
					Preferences = table.Column<UserPreferences>(type: "jsonb", nullable: true)
				},
				constraints: table =>
				{
					table.PrimaryKey("PK_User", x => x.Id);
				});

			migrationBuilder.CreateTable(
				name: "Device",
				columns: table => new
				{
					Id = table.Column<Guid>(type: "uuid", nullable: false),
					UserId = table.Column<int>(type: "integer", nullable: false),
					MacAddress = table.Column<string>(type: "text", nullable: false),
					Name = table.Column<string>(type: "text", nullable: false)
				},
				constraints: table =>
				{
					table.PrimaryKey("PK_Device", x => x.Id);
					table.ForeignKey(
						name: "FK_Device_User_UserId",
						column: x => x.UserId,
						principalTable: "User",
						principalColumn: "Id",
						onDelete: ReferentialAction.Cascade);
				});

			migrationBuilder.CreateTable(
				name: "Feeding",
				columns: table => new
				{
					Id = table.Column<Guid>(type: "uuid", nullable: false),
					DeviceId = table.Column<Guid>(type: "uuid", nullable: true),
					AmountBefore = table.Column<decimal>(type: "numeric", nullable: false),
					AmountAfter = table.Column<decimal>(type: "numeric", nullable: false),
					FeedingStart = table.Column<DateTime>(type: "timestamp without time zone", nullable: false),
					FeedingEnd = table.Column<DateTime>(type: "timestamp without time zone", nullable: false)
				},
				constraints: table =>
				{
					table.PrimaryKey("PK_Feeding", x => x.Id);
					table.ForeignKey(
						name: "FK_Feeding_Device_DeviceId",
						column: x => x.DeviceId,
						principalTable: "Device",
						principalColumn: "Id",
						onDelete: ReferentialAction.Restrict);
				});

			migrationBuilder.CreateTable(
				name: "Session",
				columns: table => new
				{
					Id = table.Column<Guid>(type: "uuid", nullable: false),
					UserId = table.Column<int>(type: "integer", nullable: true),
					DeviceId = table.Column<Guid>(type: "uuid", nullable: true),
					Token = table.Column<string>(type: "text", nullable: false),
					IP = table.Column<IPAddress>(type: "inet", nullable: false),
					SessionStart = table.Column<DateTime>(type: "timestamp without time zone", nullable: false),
					SessionEnd = table.Column<DateTime>(type: "timestamp without time zone", nullable: false)
				},
				constraints: table =>
				{
					table.PrimaryKey("PK_Session", x => x.Id);
					table.ForeignKey(
						name: "FK_Session_Device_DeviceId",
						column: x => x.DeviceId,
						principalTable: "Device",
						principalColumn: "Id",
						onDelete: ReferentialAction.Restrict);
					table.ForeignKey(
						name: "FK_Session_User_UserId",
						column: x => x.UserId,
						principalTable: "User",
						principalColumn: "Id",
						onDelete: ReferentialAction.Restrict);
				});

			migrationBuilder.CreateIndex(
				name: "IX_Device_UserId",
				table: "Device",
				column: "UserId");

			migrationBuilder.CreateIndex(
				name: "IX_Feeding_DeviceId",
				table: "Feeding",
				column: "DeviceId");

			migrationBuilder.CreateIndex(
				name: "IX_Session_DeviceId",
				table: "Session",
				column: "DeviceId");

			migrationBuilder.CreateIndex(
				name: "IX_Session_UserId",
				table: "Session",
				column: "UserId");
		}

		protected override void Down(MigrationBuilder migrationBuilder)
		{
			migrationBuilder.DropTable(
				name: "Feeding");

			migrationBuilder.DropTable(
				name: "Session");

			migrationBuilder.DropTable(
				name: "Device");

			migrationBuilder.DropTable(
				name: "User");
		}
	}
}
