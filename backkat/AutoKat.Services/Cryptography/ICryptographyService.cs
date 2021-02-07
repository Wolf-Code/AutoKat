using AutoKat.Core.DependencyInjection;

namespace AutoKat.Services.Cryptography
{
	public interface ICryptographyService : IService
	{
		byte[] GetNewSalt();

		string Hash(string input, byte[] salt);
	}
}
