using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using MapGUI.Models;

namespace MapGUI.Inherited_Controls
{
  public class MapPieceRepresentor : Button
    {
        MapPiece piece;
       public MapPiece Piece { get => piece; set => piece = value; }
        public System.Windows.Media.Brush Background
        {
            get
            {
                return this.Background; 
            }
            set
            {
                this.Background = value; 
            }
        }

       public MapPieceRepresentor(MapPiece piece = null)
        {
            if (piece != null)
            {
                this.piece = piece;
            }
            else
            {
                this.piece = new MapPiece();
            }
        }
    }
}
