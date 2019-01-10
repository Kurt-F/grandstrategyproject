using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MapGUI.Inherited_Controls;
namespace MapGUI.Models
{
    public class MainModel
    {
        public const int SIZE = 707; // The approximate square root of 500000
        List<List<MapPiece>> mapPieces; 

        public MainModel()
        {
            mapPieces = new List<List<MapPiece>>();
            for(int i = 0; i < SIZE; i++)
            {
                mapPieces.Add(new List<MapPiece>());
                for(int j = 0; j < SIZE; j++)
                {
                    mapPieces[i].Add(new MapPiece(i, j, -1));
                }
            }
        }

        public void  MapViewPieces(List<List<MapPieceRepresentor>> representors ,int start_x, int start_y)
        {
            if(start_x < 0 || start_y < 0)
            {
                return; 
            }
            
            for(int i = 0; i < representors.Count; i++)
            {
                for(int j = 0; j < representors[i].Count; j++)
                {
                    if(start_x + i < SIZE && start_y + j < SIZE)
                    {
                        representors[i][j].Piece = mapPieces[start_x + i][start_y + j];
                    }
                    else
                    {
                        representors[i][j] = null;
                    }
                }
            }
        }

        public void UpdateMapViewPiecesWithBackend(List<List<MapPieceRepresentor>> representors)
        {
            DLL_Connector_Singleton instance = DLL_Connector_Singleton.GetInstance();
            for(int i = 0; i < representors.Count; i++)
            {
                for(int j = 0; j < representors[i].Count; j++)
                {
                    Map_Node_Struct map_node = instance._ReadNodeAtIndex(representors[i][j].Piece.Map_node_id);
                }
            }
        }
    }
}
