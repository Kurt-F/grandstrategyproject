using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MapGUI.Models
{
    // A "Province" of the map
    // Note to Kurt: this may need to be altered to fit your JSON file
    //class MapNode
    //{
    //    static int num_map_nodes = 0;
    //    string name;
    //    int id;
    //    int country;
    //    int state;
    //    int climate;
    //    int terrain;

    //    public int Country { get => country; set => country = value; }
    //    public int State { get => state; set => state = value; }
    //    public int Climate { get => climate; set => climate = value; }
    //    public int Terrain { get => terrain; set => terrain = value; }
    //    public string Name { get => name; set => name = value; }

    //    public MapNode(string name, int country = 0, int state = 0, int climate = 0, int terrain = 0)
    //    {
    //        this.id = num_map_nodes++;
    //        this.name = name;
    //        this.climate = climate;
    //        this.country = country;
    //        this.state = state;
    //        this.terrain = terrain;
    //    }
    //}

   public unsafe struct Map_Node_Struct
    {
       public Int32 map_id;
       public Int32 area;
       public Int32 terrain;
       public Int32 number_of_connections;
       public Int32* connection_ids;
    }

}
