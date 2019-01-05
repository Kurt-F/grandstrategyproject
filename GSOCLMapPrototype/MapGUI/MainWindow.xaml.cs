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
