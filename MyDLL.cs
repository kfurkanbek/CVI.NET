using System.Text;

namespace MyDLL
{
    public class MyClass
    {
        public MyClass()
        {
        }

        public int MyMethod(string filePath, string message)
        {
            try
            {
                var date = System.DateTime.Now;
                byte[] rawData = new UTF8Encoding(true).GetBytes($"{date:yyyy-MM-dd-HH-mm-ss}: {message}\n");

                using (var fileStream = System.IO.File.Open(filePath, System.IO.FileMode.Append, System.IO.FileAccess.Write, System.IO.FileShare.ReadWrite))
                {
                    fileStream.Write(rawData, 0, rawData.Length);
                }

                return +1;
            }
            catch (System.Exception e)
            {
                System.Console.WriteLine(e.Message);
                return -1;
            }
        }

        public int exampleKnownMethod(string filePath, string message)
        {
            try
            {
                var date = System.DateTime.Now;
                byte[] rawData = new UTF8Encoding(true).GetBytes($"{date:yyyy-MM-dd-HH-mm-ss}: {message}\n");

                using (var fileStream = System.IO.File.Open(filePath, System.IO.FileMode.Append, System.IO.FileAccess.Write, System.IO.FileShare.ReadWrite))
                {
                    fileStream.Write(rawData, 0, rawData.Length);
                }

                return +1;
            }
            catch (System.Exception e)
            {
                System.Console.WriteLine(e.Message);
                return -1;
            }
        }
    }
}
