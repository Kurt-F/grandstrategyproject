using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media;

namespace MapGUI.Util
{
public class Color_Singleton
    {    
    List<Color> colors;
        static Color_Singleton instance;
        private Color_Singleton()
        {
            colors = new List<Color>();
            for (int i = 0; i < 256; i+= 5)
            {
                for (int j = 0; j < 256; j+= 10)
                {
                    for (int k = 0; k < 256; k+= 15)
                    {
                        colors.Add(Color.FromRgb((byte)i, (byte)j, (byte)k));
                    }
                }
            }
            colors.OrderBy(a => Guid.NewGuid()).ToList();
        }
        public static Color_Singleton GetInstance()
        {
            if(instance == null)
            {
                instance = new Color_Singleton();
            }
            return instance;
        }
    }
}
