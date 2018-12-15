using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace DLL_Tester
{
    class Program
    {

        [DllImport("Test_Research.dll")]
        public static extern int DoStuff();
        static void Main(string[] args)
        {
            try
            {
                int v = 3;
                int x = DoStuff();
                var y = 2;
            }
            catch(Exception e)
            {
                var z = 2;
            }
        }
    }
}
