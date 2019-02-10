using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MapGUI.Models
{ 
   public unsafe struct Map_Node_Struct
    {
      public  char* name; // 1
      public  int map_id; //
      public  byte surface;
      public  int terrain;
      public  byte port_level;
      public  byte airport_level;
      public  byte elevator_level;
      public  byte polity; // PLACEHOLDER
      public  byte climate; // PLACEHOLDER
      public  float nuclear;
      public  float chemical;
      public  int area; // Square miles
      public  float oxygen; // Oxygen ppm per cubic foot or something
      public  float air_quality; // Measure of common pollutants
      public  int resource_type; // PLACEHOLDER
      public  int resource_amount; // Tons of the resource available
    }
}
