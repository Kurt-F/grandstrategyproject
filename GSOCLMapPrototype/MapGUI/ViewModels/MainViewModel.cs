using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using MapGUI.Models;
using MapGUI.Inherited_Controls;
namespace MapGUI.ViewModels
{
    public class MainViewModel
    {
       #region private variables
       private const int MAX_COL_ROWS = 60;
       private int num_col_row; // will always be the same
       private int x_orig;
       private int y_orig;
       private MainModel model;
       private Grid map;
       #endregion

        #region Properties
        public int Num_col_row
        {
            get => num_col_row;
            set
            {
                if (value <= 0)
                {
                    num_col_row = 1;
                }
                else if (value > MAX_COL_ROWS)
                {
                    num_col_row = MAX_COL_ROWS;
                }
                else
                {
                    num_col_row = value;
                }
            }
        }
        public int X_orig {
            get => x_orig;
            set
            {
                x_orig = value;
                UpdateGrid();
            }
        }
        public int Y_orig {
            get => y_orig;
            set
            {
                y_orig = value;
                UpdateGrid();
            }
        }
        #endregion

        #region Functions
        public MainViewModel(Grid grid)
        {
            this.map = grid;
            this.Num_col_row = 5;
            this.model = new MainModel();
        }

        public void AddRow_Column(int add)
        {
            Num_col_row += add;
            UpdateGrid();
        }

        public void MoveGridUpDown(int add)
        {
            Y_orig += add;
            UpdateGrid();
        }

        public void MoveGridLeftRight(int add)
        {
            X_orig += add;
            UpdateGrid();
        }

        public void UpdateGrid()
        {
            map.RowDefinitions.Clear();
            map.ColumnDefinitions.Clear();
            map.Children.Clear();
            double width_height_btn = (double)Math.Min(map.ActualHeight, map.ActualWidth) / Num_col_row;
            int number_of_rows = (int)(map.ActualHeight / width_height_btn);
            int number_of_columns = (int)(map.ActualWidth / width_height_btn);
            for (int i = 0; i < number_of_columns; i++)
            {
                map.ColumnDefinitions.Add(new ColumnDefinition() {Width = new GridLength(width_height_btn)});
            }
            for (int i = 0; i < number_of_rows; i++)
            {
                map.RowDefinitions.Add(new RowDefinition() { Height = new GridLength(width_height_btn) });
            }
          
            List<List<MapPieceRepresentor>> pieces;
            pieces = new List<List<MapPieceRepresentor>>();
            for(int i = 0; i < number_of_rows; i++)
            {
                pieces.Add(new List<MapPieceRepresentor>());
                for(int j = 0; j < number_of_columns; j++)
                {
                    MapPieceRepresentor mpr = new MapPieceRepresentor();
                    pieces[i].Add(mpr);
                 //   mpr.Height = width_height_btn;
                 //   mpr.Width = width_height_btn;
                    Grid.SetRow(mpr, i);
                    Grid.SetColumn(mpr, j);
                    map.Children.Add(mpr);
                }
            }
           model.MapViewPieces(pieces, x_orig, y_orig);
           model.UpdateMapViewPiecesWithBackend(pieces);
        }
 #endregion
    }
}