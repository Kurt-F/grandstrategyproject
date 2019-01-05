using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MapGUI.Models
{
    class MapPiece
    {
        int x_pos, y_pos;
        MapNode map_node; 

        MapPiece()
        {
            
        }

        public int X_pos { get => x_pos; set => x_pos = value; }
        public int Y_pos { get => y_pos; set => y_pos = value; }
        internal MapNode Map_node { get => map_node; set => map_node = value; }
    }
}
