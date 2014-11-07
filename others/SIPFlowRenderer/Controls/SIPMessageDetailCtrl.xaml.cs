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
    /// Interaction logic for SIPMessageDetailCtrl.xaml
    /// </summary>
    public partial class SIPMessageDetailCtrl : UserControl
    {
        private bool _isMouseLeaved;

        #region DependencyProperties

        public bool IsPinnedState
        {
            get { return (bool)GetValue(IsPinnedStateProperty); }
            set { SetValue(IsPinnedStateProperty, value); }
        }

        // Using a DependencyProperty as the backing store for IsPinnedState.  This enables animation, styling, binding, etc...
        public static readonly DependencyProperty IsPinnedStateProperty =
            DependencyProperty.Register("IsPinnedState", typeof(bool), typeof(SIPMessageDetailCtrl), new PropertyMetadata(false));

        #endregion

        #region Members

        private Window _popup = new Window();

        #endregion

        
        public SIPMessageDetailCtrl(BaseLoader.LogEntry entry)
        {
            InitializeComponent();
            
            _header.Text = String.Format("{0} to {1}", entry.fromHost, entry.toHost);
            _message.Text = entry.payload;

            _popup.Content = this;
            //_popup.PlacementTarget = Parent;
            _popup.WindowStyle = WindowStyle.None;
            _popup.AllowsTransparency = true;
            _popup.Background = new SolidColorBrush(Colors.Transparent);
            _popup.MouseLeave += _popup_MouseLeave;
            _popup.MouseLeftButtonDown += _popup_MouseLeftButtonDown;
            _popup.ResizeMode = ResizeMode.CanResizeWithGrip;
            _popup.Width = 450;
            _popup.Height = 200;
            _popup.Topmost = true;

            DataContext = this;
        }

        public void Show()
        {
            _isMouseLeaved = false;
            Interop.Mouse.ShowCenteredToMouse(_popup);
        }

        public void HideTimeout()
        { 
            DispatcherTimer timer = new DispatcherTimer()
            {
                Interval = TimeSpan.FromSeconds(2)
            };

            timer.Tick += delegate(object s, EventArgs ea)
            {
                ((DispatcherTimer)timer).Stop();
                
                if (!IsMouseOver && !ContextMenu.IsOpen)
                {
                    _popup.Hide();
                }
            };

            timer.Start();
        }

        void _popup_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            _popup.DragMove();
        }

        void _popup_MouseLeave(object sender, MouseEventArgs e)
        {
            _isMouseLeaved = true;
            if (!IsPinnedState && !ContextMenu.IsOpen)
            {
                _popup.Hide();
            }
        }

        internal void CloseDetails()
        {
            _popup.Close();
        }

        private void MenuItem_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                Clipboard.SetText(_message.Text);
            }
            catch(System.Runtime.InteropServices.COMException)
            {
                System.Threading.Thread.Yield();
                try
                {
                    Clipboard.SetText(_message.Text);
                }
                catch(System.Runtime.InteropServices.COMException)
                {
                    MessageBox.Show("Can't Access Clipboard");
                } 
            }
        }
    }
}
