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

namespace SIPFlowRenderer.Controls
{
    /// <summary>
    /// Interaction logic for SIPEntity.xaml
    /// </summary>
    public partial class SIPEntity : UserControl
    {
        public SIPEntity(string name)
        {
            InitializeComponent();
            _name.Text = name;
            LayoutUpdated += SIPEntity_LayoutUpdated;
        }

        public void getConnectionPoint(int messageNum, out double x, out double y)
        {
            UIElement container = VisualTreeHelper.GetParent(_line) as UIElement;
            Point relativeLocation = _line.TranslatePoint(new Point(0, 0), container);

            x = Canvas.GetLeft(this) + relativeLocation.X + 10;
            y = relativeLocation.Y + messageNum * 25.0 + 10.0;

            if (Double.IsNaN(x)) x = 0;
            if (Double.IsNaN(y)) y = 0;
        }

        public string GetName()
        {
            return _name.Text;
        }

        #region Private methods
        private void SIPEntity_LayoutUpdated(object sender, EventArgs e)
        {
        }

        private void _rectangle_MouseEnter(object sender, MouseEventArgs e)
        {
            _rectangle.Fill = new SolidColorBrush(Colors.Gold);
        }

        private void _rectangle_MouseLeave(object sender, MouseEventArgs e)
        {
            _rectangle.Fill = new SolidColorBrush(Colors.Gray);
        }

        #endregion
    }
}
