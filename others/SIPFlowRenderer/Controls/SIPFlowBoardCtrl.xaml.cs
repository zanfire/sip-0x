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
    /// Interaction logic for SIPFlowBoard.xaml
    /// </summary>
    public partial class SIPFlowBoard : UserControl
    {

        #region Members
        
        // Entities
        List<SIPEntity> _entities = new List<SIPEntity>();
        List<SIPMessageCtrl> _messages = new List<SIPMessageCtrl>();
        bool _updated = false;
        
        #endregion


        public SIPFlowBoard()
        {
            InitializeComponent();

            LayoutUpdated += SIPFlowBoard_LayoutUpdated;
        }

        public void AddEntity(string name)
        {
            SIPEntity entity = new SIPEntity(name);
            _entities.Add(entity);
            _board.Children.Add(entity);
        }

        internal void AddMessage(PlainTextLogLoader.LogEntry logEntry)
        {
            SIPEntity from = null;
            SIPEntity to = null;
            foreach (SIPEntity entry in _entities)
            {
                // TODO: remove dir and switch direction automagically in logentry processing
                // Strip Port

                if (entry.GetName().Equals(PlainTextLogLoader.StripPort(logEntry.fromHost)))
                {
                    from = entry;
                }
                if (entry.GetName().Equals(PlainTextLogLoader.StripPort(logEntry.toHost)))
                {
                    to = entry;
                }
            }
            SIPMessageCtrl msg = new SIPMessageCtrl(this, from, to, logEntry, _messages.Count());
            _messages.Add(msg);
            _board.Children.Add(msg);
        }

        internal void InvalidateRegion()
        {
            _updated = false;
        }

        internal void Clear()
        {
            _board.Children.Clear();

            foreach (SIPMessageCtrl ctrl in _messages)
            {
                ctrl.CloseDetails();
            }

            _messages.Clear();
            _entities.Clear();
            _updated = false;
        }

        protected void SIPFlowBoard_LayoutUpdated(object sender, EventArgs e)
        {
            if (_updated) return;
            double h = 0;
            foreach (FrameworkElement fe in _board.Children)
            {
                
                // example 1
                double top1 = Canvas.GetTop(fe);
                if (top1 >= h) h = top1;
            }
            double x = 0.0;
            foreach (var entity in _entities)
            {
                x += entity.ActualWidth;
            }

            h += 100;
            if (_board.Width != x || _board.Height != h)
            {
                _board.Width = x;
                _board.Height = h;
            }
            else
            {
                _updated = true;
            }

            x = 0;
            foreach (var entity in _entities)
            {
                entity.Height = _board.ActualHeight;
                Canvas.SetLeft(entity, x);
                Canvas.SetTop(entity, 0);
                if (entity.ActualWidth <= 0.1 || double.IsNaN(entity.ActualWidth))
                {
                    x += 150;
                }
                else
                {
                    x += entity.ActualWidth;
                }

                System.Diagnostics.Debug.WriteLine(String.Format("Entity x: {0}.", x));
            }
            
            System.Diagnostics.Debug.WriteLine(String.Format("W: {0}, H: {1}.", Width, Height));
        }
    }
}
