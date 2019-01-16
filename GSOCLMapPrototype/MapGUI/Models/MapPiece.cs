using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media;

namespace MapGUI.Models
{
    public class MapPiece
    {
        int x_pos, y_pos, map_node_id;
        System.Windows.Media.Brush background;
        public MapPiece()
        {
            
        }

        public MapPiece(int x_pos, int y_pos, int id)
        {
            this.x_pos = x_pos;
            this.y_pos = y_pos;
            this.map_node_id = id;
        }
       
        public int X_pos { get => x_pos; set => x_pos = value; }
        public int Y_pos { get => y_pos; set => y_pos = value; }
        public int Map_node_id { get => map_node_id; set => map_node_id = value; }
        public Brush Background { get => background; set => background = value; }
    }
}