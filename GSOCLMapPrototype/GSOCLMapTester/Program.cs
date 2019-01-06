// To use this test stuff, Build the GSOCLMapPrototype project
// Find the produced DLL probably in the root folder in a Debug or Release folder and copy all of the contents over to the release or debug folder of this project
// Feel free to mess with the code and experiment. The currently uncommented code is for demonstrating how expensive invoking a method in a dll is. 
// We may want to design our code so that fewer calls are made. For example, in the sample code that runs AddMany, its execution is much faster than running DoNothing for the
// same number of iterations found in the for loop. When I run Add and DoNothing ten million times while running 

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
       
        [DllImport("GSOCLMapPrototype.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void TestStructures(IntPtr test);

        [DllImport("GSOCLMapPrototype.dll")]
        public static extern int RunTests();

        [DllImport("GSOCLMapPrototype.dll")]
        public static extern void AddNode();

        [DllImport("GSOCLMapPrototype.dll")]
        public static extern int GetNumberOfNodes();

        [DllImport("GSOCLMapPrototype.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int Add(int x, int y);

        [DllImport("GSOCLMapPrototype.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Add_Many(IntPtr num, int size);

        [DllImport("GSOCLMapPrototype.dll")]
        public static extern void DoNothing();

        [DllImport("GSOCLMapPrototype.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void ReadNodeAtIndex(IntPtr ptr, int index);

        static void Main(string[] args)
        {
            //unsafe
            //    {


            //        var watch = System.Diagnostics.Stopwatch.StartNew();
            //        IntPtr ptr = Marshal.AllocHGlobal(sizeof(IntPtr));
            //        int temp;
            //       for(int i = 0; i < 10000000; i++)
            //        {
            //           temp = Add(i, i - 1); 
            //        }
            //        watch.Stop();
            //        Console.WriteLine(watch.ElapsedMilliseconds);
            //        watch = System.Diagnostics.Stopwatch.StartNew();
            //        Add_Many(ptr, 10000000);
            //        watch.Stop();
            //        Console.WriteLine(watch.ElapsedMilliseconds);
            //        watch = System.Diagnostics.Stopwatch.StartNew();
            //        for(int i = 0; i < 10000000; i++)
            //        {
            //            DoNothing();
            //        }
            //        watch.Stop();
            //        Console.WriteLine(watch.ElapsedMilliseconds);
            //        RunTests();
            //    }
            TestStruct t;
            unsafe
            {
                IntPtr ptr = Marshal.AllocHGlobal(sizeof(TestStruct));
                TestStructures(ptr);
                t = (TestStruct)Marshal.PtrToStructure(ptr, typeof(TestStruct));
                for (int i = 0; i < t.size_of_list; i++)
                {
                    Console.WriteLine(t.list[i]);
                }
            }
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
            DoStuff();
            DoStuff();
            DoStuff();
            DoStuff();
            unsafe
            {
                IntPtr nodeptr = Marshal.AllocHGlobal(sizeof(Map_Node_Struct));
                ReadNodeAtIndex(nodeptr, 1);
                Map_Node_Struct m_struct = (Map_Node_Struct)Marshal.PtrToStructure(nodeptr, typeof(Map_Node_Struct));
                 }
            Console.ReadKey();
        }

        static void DoStuff()
        {
            AddNode();
            int a = GetNumberOfNodes();
            Console.WriteLine(a);
            AddNode();
            int b = GetNumberOfNodes();
            Console.WriteLine(b);
            AddNode();
            int c = GetNumberOfNodes();
            Console.WriteLine(c);
        }
    }
}
