using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.IO;
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

namespace SIPFlowRenderer
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private BaseLoader _last_loader = null;
        private DispatcherTimer _timer = null;
        private int _current_start_point = 0;
        private int _count_per_show = 20;

        public MainWindow()
        {
            InitializeComponent();

            Closed += MainWindow_Closed;

            _timer = new DispatcherTimer()
            {
                Interval = TimeSpan.FromMilliseconds(750)
            };

            _timer.Tick += delegate(object s, EventArgs ea)
            {
                ((DispatcherTimer)_timer).Stop();
                _sipflow.Clear();
                RenderLoader(_last_loader, _txbx_search.Text, _current_start_point);
            };
        }

        void MainWindow_Closed(object sender, EventArgs e)
        {
            _sipflow.Clear();
        }


        private void LoadContent(string filename)
        {
        }

        private void _btn_minimize_Click(object sender, RoutedEventArgs e)
        {
            WindowState = System.Windows.WindowState.Minimized;
        }

        private void _btn_close_Click(object sender, RoutedEventArgs e)
        {
            Close();
        }

        private void _btn_maximaize_Click(object sender, RoutedEventArgs e)
        {
            if (WindowState == System.Windows.WindowState.Maximized)
            {
                WindowState = System.Windows.WindowState.Normal;
            }
            else
            {
                WindowState = System.Windows.WindowState.Maximized;
            }
        }

        private void _open_Click(object sender, RoutedEventArgs e)
        {

            Microsoft.Win32.OpenFileDialog dlg = new Microsoft.Win32.OpenFileDialog();
            dlg.FileName = "sip trace";
            dlg.DefaultExt = ".log";
            dlg.Filter = "Log documents (.log)|*.log";
            dlg.InitialDirectory = System.Environment.CurrentDirectory;
            if (dlg.ShowDialog() == true)
            {
                // Open document
                string filename = dlg.FileName;
                //PlainTextLogLoader loader = new PlainTextLogLoader(filename);
                MirialLogLoader loader = new MirialLogLoader(filename);
                loader.Load();
                _current_start_point = 0;
                RenderLoader(loader, _txbx_search.Text, _current_start_point);
                _last_loader = loader;
            }
        }


        private void RenderLoader(BaseLoader loader, string search, int start)
        {
            StringCollection col = loader.GetEntities();
            foreach (String str in col)
            {
                _sipflow.AddEntity(str);
            }

            int idx = 0;
            int count = 0;
            int firstMessage = -1;
            var messages = loader.GetMessages();
            foreach (PlainTextLogLoader.LogEntry log in messages)
            {
                if ((search == String.Empty || log.payload.Contains(search)) && idx >= start)
                {
                    if (firstMessage == -1) firstMessage = idx;
                    _sipflow.AddMessage(log);
                    count++;
                }
                idx++;

                if (count >= _count_per_show) break;
            }
            _sipflow.InvalidateRegion();

            _txbx_start_message.Text = String.Format("{0}/{1} ({2})", firstMessage, messages.Count, count);
        }

        private void Window_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            DragMove();
        }


        private void ResizeGripDragDelta(object aSender, DragDeltaEventArgs aEventArgs)
        {
            double lWidth = ActualWidth + aEventArgs.HorizontalChange;
            double lHeight = ActualHeight + aEventArgs.VerticalChange;
            TrySetSize(lWidth, lHeight);
        }

        private void ResizeGripMouseDown(object aSender, MouseButtonEventArgs aEventArgs)
        {
            if (aEventArgs.LeftButton == MouseButtonState.Pressed &&
                  aEventArgs.RightButton == MouseButtonState.Released &&
                  aEventArgs.MiddleButton == MouseButtonState.Released)
            {
                Mouse.Capture(ResizeGrip);
            }
        }

        private void ResizeGripMouseUp(object aSender, MouseButtonEventArgs aEventArgs)
        {
            if (Mouse.Captured == ResizeGrip)
            {
                Mouse.Capture(null);
            }
        }

        private void TrySetSize(double aWidth, double aHeight)
        {
            if (aWidth < MinWidth || aHeight < MinHeight)
            {
                return;
            }

            Width = aWidth;
            Height = aHeight;
        }

        private void _txbx_search_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (_last_loader == null) return;

            if (_timer.IsEnabled)
            {
                _timer.Stop();
            }
            _timer.Start();
        }

        private void _btn_prev_Click(object sender, RoutedEventArgs e)
        {
            if (_current_start_point == 0) return;
            _current_start_point -= _count_per_show;
            _sipflow.Clear();
            RenderLoader(_last_loader, _txbx_search.Text, _current_start_point);
        }

        private void _btn_next_Click(object sender, RoutedEventArgs e)
        {
            _current_start_point += _count_per_show;
            _sipflow.Clear();
            RenderLoader(_last_loader, _txbx_search.Text, _current_start_point);
        }
    }
}
