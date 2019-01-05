using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace GSOCLMapTester
{
    class Program
    {
        [DllImport("GSOCLMapPrototype.dll")]
        public static extern int RunTests();

        [DllImport("GSOCLMapPrototype.dll")]
        public static extern void AddNode();

        [DllImport("GSOCLMapPrototype.dll")]
        public static extern int GetNumberOfNodes();

        static void Main(string[] args)
        {
            int a = GetNumberOfNodes();
            Console.WriteLine(a);
            AddNode();
            int b = GetNumberOfNodes();
            Console.WriteLine(b);
            AddNode();
            int c = GetNumberOfNodes();
            Console.WriteLine(c);
            AddNode();
            int d = GetNumberOfNodes();
            Console.WriteLine(d);
            int e = GetNumberOfNodes();
            Console.WriteLine(e);
            Console.ReadKey();
        }
    }
}
