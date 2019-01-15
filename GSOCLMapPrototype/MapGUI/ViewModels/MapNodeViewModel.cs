using MapGUI.Models;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace MapGUI.ViewModels
{
    class MapNodeViewModel : INotifyPropertyChanged
    {
        #region Private Variables
        private string province_name;
        private string selected_item;
        private List<int> ids;
        private int province_id;
        private Map_Node_Struct mps;
        private Dictionary<int, string> id_to_name;

        public event PropertyChangedEventHandler PropertyChanged;
        private void NotifyPropertyChanged([CallerMemberName] String propertyName = "")
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
        #endregion

        #region Properties
        public string Province_Name
        {
            get
            {
                return province_name; 
            }
            set
            {
                province_name = value;
                id_to_name[Province_ID] = value;
                NotifyPropertyChanged();
            }
        }

        public int Province_ID
        {
            get
            {
                return province_id;
            }
            set
            {
                province_id = value;
                Province_Name = id_to_name[value];
                NotifyPropertyChanged();
            }
        }

        public List<int> IDs
        {
            get
            {
                return ids;
            }
            set
            {
                ids = value;
                NotifyPropertyChanged();
            }
        }

        #endregion

        #region Constructors
        public MapNodeViewModel(Map_Node_Struct mps, Dictionary<int, string> id_to_name)
        {
            this.mps = mps;
            this.id_to_name = id_to_name;
            this.id_to_name.Add(int.MaxValue, "New Id");
            IDs = this.id_to_name.Keys.ToList();
            if(mps.map_id != -1)
            {
                Province_Name = this.id_to_name[mps.map_id];
            }
            else
            {
                Province_Name = this.id_to_name[int.MaxValue];
            }
        }
        #endregion
    }
}