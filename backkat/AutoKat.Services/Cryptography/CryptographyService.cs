using Microsoft.AspNetCore.Cryptography.KeyDerivation;
using System;
using System.Security.Cryptography;

namespace AutoKat.Services.Cryptography
{
	public class CryptographyService : ICryptographyService
	{
		public byte[] GetNewSalt()
		{
			var salt = new byte[128 / 8];
			using (var rng = RandomNumberGenerator.Create())
			{
				rng.GetBytes(salt);
			}

			return salt;
		}

		public string Hash(string input, byte[] salt)
		{
			return Convert.ToBase64String(KeyDerivation.Pbkdf2(
			   password: input,
			   salt: salt,
			   prf: KeyDerivationPrf.HMACSHA1,
			   iterationCount: 10000,
			   numBytesRequested: 256 / 8
			));
		}
	}
}
