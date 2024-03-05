using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OKPOEAuthServer
{
    class FileIO
    {
        public static bool containsHWID(string hardwareID)
        {
            string[] lines = System.IO.File.ReadAllLines("HWIDs.txt");
            char[] ignoredChars = { ' ', '\n', '\0' };

            foreach (string line in lines)
            {
                if (hardwareID.Trim(ignoredChars).Equals(line))
                {
                    Console.WriteLine("Found requested HWID...");
                    return true;
                }
            }

            return false;
        }
 
        public static bool isIPBanned(string IP)
        {
            string[] lines = System.IO.File.ReadAllLines("bannedIPs.txt");
            char[] ignoredChars = { ' ', '\n', '\0' };

            foreach (string line in lines)
            {
                if (IP.Trim(ignoredChars).Equals(line))
                {
                    Console.WriteLine("Found banned IP...");
                    return true;
                }

            }

            return false;
        }

        public static async void WriteToFile(string Filename, string Content)
        {
            StreamWriter file = new StreamWriter(Filename, append: true);
            using (file)
            {
                await file.WriteLineAsync(Content);
            }
        }
    }
}
