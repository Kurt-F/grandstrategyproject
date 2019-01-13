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
using MapGUI.ViewModels;
using MapGUI.Models;
namespace MapGUI.Views
{
    /// <summary>
    /// Interaction logic for MapNodeView.xaml
    /// </summary>
    public partial class MapNodeView : Window
    {
        private MapNodeViewModel _view_model;
        public MapNodeView(Map_Node_Struct mps, Dictionary<int, string> id_to_name)
        {
            InitializeComponent();
            _view_model = new MapNodeViewModel(mps, id_to_name);
            this.DataContext = _view_model; 
        }

        public Map_Node_Struct GetFinishedStruct()
        {
            return new Map_Node_Struct();
        }
     
    }
}
