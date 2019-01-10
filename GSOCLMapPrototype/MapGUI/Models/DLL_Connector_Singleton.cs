using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

// Should we connect to the DLL through a singleton? 

// Pros: Singleton has 0 risk of going out of scope,  and it is shared by all who need it

// Cons: Thread interference

namespace MapGUI.Models
{
   public class DLL_Connector_Singleton
    {
        // Test imports
        [DllImport("GSOCLMapPrototype.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void TestStructures(IntPtr test);

        [DllImport("GSOCLMapPrototype.dll")]
        private static extern int RunTests();

        [DllImport("GSOCLMapPrototype.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int Add(int x, int y);

        [DllImport("GSOCLMapPrototype.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Add_Many(IntPtr num, int size);

        [DllImport("GSOCLMapPrototype.dll")]
        private static extern void DoNothing();

        // Actual Singleton interaction
        [DllImport("GSOCLMapPrototype.dll")]
        private static extern void AddNode();

        [DllImport("GSOCLMapPrototype.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int RemoveNode(int index);

        [DllImport("GSOCLMapPrototype.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int CreateConnection(int index_a, int index_b, double freight_cost_per_lb, double travel_cost);

        [DllImport("GSOCLMapPrototype.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int RemoveConnection(int index_a, int index_b);

        [DllImport("GSOCLMapPrototype.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int EditMapNode(int map_node_num, int what_is_being_changed, int val);

        [DllImport("GSOCLMapPrototype.dll")]
        private static extern int GetNumberOfNodes();

        [DllImport("GSOCLMapPrototype.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void ReadNodeAtIndex(IntPtr ptr, int index);

        private static DLL_Connector_Singleton instance;
        private Map_Node_Struct temp;
        private DLL_Connector_Singleton()
        {}

        public static DLL_Connector_Singleton GetInstance()
        {
            if(instance == null)
            {
                instance = new DLL_Connector_Singleton();
            }
            return instance; 
        }

        public bool Test()
        {
            try
            {
                RunTests();
                return true; 
            }

            catch(Exception e)
            {
                Console.WriteLine("Execution of the dll failed");
                return false;
            }
        }

        public unsafe void _AddNode()
        {
            AddNode();
        }

        public unsafe int _RemoveNode(int index)
        {
            return RemoveNode(index);
        }

        public unsafe int _CreateConnection(int index_a, int index_b, double freight_cost_per_lb, double freight_cost)
        {
            return CreateConnection(index_a, index_b, freight_cost_per_lb, freight_cost);
        }

        public unsafe int _RemoveConnection(int index_a, int index_b)
        {
            return RemoveConnection(index_a, index_b);
        }

        public unsafe int _EditMapNode(int map_node_num, int what_is_being_changed, int val)
        {
            return EditMapNode(map_node_num, what_is_being_changed, val);
        }

        public unsafe int _GetNumberOfNodes()
        {
            return GetNumberOfNodes();
        }

        public unsafe Map_Node_Struct _ReadNodeAtIndex(int index)
        {
            IntPtr ptr = Marshal.AllocHGlobal(sizeof(Map_Node_Struct));
            ReadNodeAtIndex(ptr, index);
            return (Map_Node_Struct)Marshal.PtrToStructure(ptr, typeof(Map_Node_Struct));
        }
    }
}