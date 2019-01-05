using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

namespace MapGUI.ViewModels
{
    public class MainViewModel
    {
        #region private variables
        const int MAX_COL_ROWS = 100;
        int num_col_row; // will always be the same
        int x_orig;
        int y_orig;
        Grid map;
        #endregion

        #region Properties
        public int Num_col_row { get => num_col_row; set => num_col_row = value; }
        public int X_orig { get => x_orig; set => x_orig = value; }
        public int Y_orig { get => y_orig; set => y_orig = value; }
        #endregion

        #region Functions
        public MainViewModel(Grid grid)
        {
            this.map = grid; 
        }

        public void AddRow_Column(int add)
        {
            Num_col_row += add; 
        }

        public void MoveGridUpDown(int add)
        {
            Y_orig += add; 
        }

        public void MoveGridLeftRight(int add)
        {
            X_orig += add; 
        }
        #endregion


    }
}
