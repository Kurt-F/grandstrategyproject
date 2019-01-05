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
            
            for(int i = 0; i < 10; i++)
            {
                for(int j = 0; j < 10; j++)
                {
                    Button btn = new Button();
                    btn.Width = 10;
                    btn.Height = 10;
                    Map.Children.Add(btn);
                    Grid.SetRow(btn, i);
                    Grid.SetColumn(btn, j);
                }
            }

        
        }

        private void Plus_Btn(object sender, RoutedEventArgs e)
        {
            _view_model.AddRow_Column(1);
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
