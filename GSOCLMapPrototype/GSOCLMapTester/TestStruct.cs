using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GSOCLMapTester
{
    unsafe struct TestStruct
    {

        public Int32 x;
        public double y;
        public char z;
        public Int32* list;
        public Int32 size_of_list;
    }

    unsafe struct Map_Node_Struct
    {
        Int32 map_id;
        Int32 area;
        Int32 terrain;
        Int32 number_of_connections;
        Int32* connection_ids;
    }
}