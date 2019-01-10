using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;


namespace MapGUI
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        MapGUI.ViewModels.MainViewModel _view_model;
        public MainWindow()
        {
            InitializeComponent();
            _view_model = new ViewModels.MainViewModel(Map);
            for(int i = 0; i < 10; i++)
            {
                
                Map.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            }

            for(int i = 0; i < 10; i++)
            {
                Map.ColumnDefinitions.Add(new ColumnDefinition() { Width = Map.RowDefinitions[0].Height });
            }



        
        }

        private void Plus_Btn(object sender, RoutedEventArgs e)
        {
            int number_of_rows = 10;
            double height_per_row = this.Map.ActualHeight / number_of_rows;
            int number_of_columns = (int)(this.Map.ActualWidth / height_per_row);
            _view_model.AddRow_Column(1);
            //for (int i = 0; i < number_of_rows; i++)
            //{
            //    for (int j = 0; j < number_of_columns; j++)
            //    {
            //        Inherited_Controls.MapPieceRepresentor btn = new Inherited_Controls.MapPieceRepresentor();
            //        btn.Width = height_per_row;
            //        btn.Height = height_per_row;
            //        Map.Children.Add(btn);
            //        Grid.SetRow(btn, i);
            //        Grid.SetColumn(btn, j);
            //    }
            //}
        }

        private void Minus_Btn(object sender, RoutedEventArgs e)
        {
            _view_model.AddRow_Column(-1);
        }

        private void Up_Btn(object sender, RoutedEventArgs e)
        {
            _view_model.MoveGridUpDown(-1);
        }


        private void Down_Btn(object sender, RoutedEventArgs e)
        {
            _view_model.MoveGridUpDown(1); 
        }


        private void Left_Btn(object sender, RoutedEventArgs e)
        {
            _view_model.MoveGridLeftRight(-1);
        }


        private void Right_Btn(object sender, RoutedEventArgs e)
        {
            _view_model.MoveGridLeftRight(1);
        }

    }
}
