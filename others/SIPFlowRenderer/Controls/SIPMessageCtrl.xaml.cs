using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;

namespace SIPFlowRenderer.Controls
{
    /// <summary>
    /// Interaction logic for SIPMessage.xaml
    /// </summary>
    public partial class SIPMessageCtrl : UserControl
    {
        #region Members

        private int _message_num = 0;
        private SIPFlowBoard _board = null;
        private SIPEntity _from = null;
        private SIPEntity _to = null;
        private SIPMessageDetailCtrl _details;
        private string _raw_message;
        private int[] _lastCords = new int[4];

        #endregion
        public SIPMessageCtrl(SIPFlowBoard board, SIPEntity from, SIPEntity to, BaseLoader.LogEntry logEntry, int num)
        {
            _message_num = num;
            _board = board;
            _from = from;
            _to = to;
            _raw_message = logEntry.payload;
            _details = new SIPMessageDetailCtrl(logEntry);

            InitializeComponent();
            
            LayoutUpdated += SIPMessageCtrl_LayoutUpdated;
            MouseEnter += SIPMessageCtrl_MouseEnter;
            MouseLeave += SIPMessageCtrl_MouseLeave;

            _name.Text = _raw_message.Substring(0, _raw_message.IndexOf("\r\n"));
        }


        void SIPMessageCtrl_MouseLeave(object sender, MouseEventArgs e)
        {
            _details.HideTimeout();
        }

        void SIPMessageCtrl_MouseEnter(object sender, MouseEventArgs e)
        {
            _details.Show();
        }

        void SIPMessageCtrl_LayoutUpdated(object sender, EventArgs e)
        {
            double x1, y1, x2, y2;
            _from.getConnectionPoint(_message_num, out x1, out y1);
            _to.getConnectionPoint(_message_num, out x2, out y2);

            if (_lastCords[0] != (int)x1 || _lastCords[1] != (int)x2 || _lastCords[2] != (int)y1 || _lastCords[3] != (int)y2)
            {

                if (x1 > x2)
                {
                    Canvas.SetLeft(this, x2);
                    _ellipse1.Visibility = System.Windows.Visibility.Collapsed;
                    _ellipse2.Visibility = System.Windows.Visibility.Visible;
                }
                else
                {
                    Canvas.SetLeft(this, x1);
                    _ellipse1.Visibility = System.Windows.Visibility.Visible;
                    _ellipse2.Visibility = System.Windows.Visibility.Collapsed;
                }
                _line.X1 = 0;
                _line.X2 = Math.Abs(x2 - x1);
                _line.Y1 = 0;
                _line.Y2 = 0;
                Canvas.SetTop(this, y1);
                _lastCords[0] = (int)x1;
                _lastCords[1] = (int)x2; 
                _lastCords[2] = (int)y1; 
                _lastCords[3] = (int)y2;

                System.Diagnostics.Debug.WriteLine("SIPMessageCtr " + _message_num + " x1: " + x1 + ", x2: " + x2 + ", y1: " + y1 + " y2:" + y2);
            }
            else
            {
                //System.Diagnostics.Debug.WriteLine("SIPMessageCtr not updated");
            }
        }

        internal void CloseDetails()
        {
            _details.CloseDetails();
        }
    }
}
