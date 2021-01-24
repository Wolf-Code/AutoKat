namespace DatabaseManagement
{
	class Program
	{
		static void Main(string[] args)
		{
			using (var context = new AutoKat.Data.AutoKatContext())
			{
				context.Database.EnsureCreated();
			}
		}
	}
}
