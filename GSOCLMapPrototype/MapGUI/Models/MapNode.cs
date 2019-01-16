using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MapGUI.Models
{ 
   public unsafe struct Map_Node_Struct
    {
        char name;
        int map_id;
        byte surface;
        int terrain;
        byte port_level;
        byte airport_level;
        byte elevator_level;
        byte polity; // PLACEHOLDER
        byte climate; // PLACEHOLDER
        float nuclear;
        float chemical;
        int area; // Square miles
        float oxygen; // Oxygen ppm per cubic foot or something
        float air_quality; // Measure of common pollutants
        int resource_type; // PLACEHOLDER
        int resource_amount; // Tons of the resource available
    }
}
