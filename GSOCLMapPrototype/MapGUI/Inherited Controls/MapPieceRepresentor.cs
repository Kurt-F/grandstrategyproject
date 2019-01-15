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
        public static MainModel _model_ref;
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
            this.Click += new System.Windows.RoutedEventHandler(SetNodeData);
        }

        public void SetNodeData (object sender, System.Windows.RoutedEventArgs e)
        {
            MapPieceRepresentor mpr = (MapPieceRepresentor)sender;
            MapPiece mp = mpr.Piece;
            DLL_Connector_Singleton singleton = DLL_Connector_Singleton.GetInstance();
            Map_Node_Struct mps = singleton._ReadNodeAtIndex(piece.Map_node_id);
            Dictionary<int, string> ids_to_name = _model_ref.GetSurroundingIds(mp.X_pos, mp.Y_pos);
            Views.MapNodeView view = new Views.MapNodeView(mps, ids_to_name);
            view.ShowDialog();
        }
    }
}