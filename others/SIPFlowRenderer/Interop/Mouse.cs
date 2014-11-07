using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace SIPFlowRenderer.Interop
{
    internal static class Mouse
    {
        public static void ShowCenteredToMouse(this Window window)
        {
            // in case the default start-up location isn't set to Manual
            WindowStartupLocation oldLocation = window.WindowStartupLocation;
            // set location to manual -> window will be placed by Top and Left property
            window.WindowStartupLocation = WindowStartupLocation.Manual;
            ComputeTopLeft(ref window);
            window.Show();
            window.WindowStartupLocation = oldLocation;
        }

        private static void ComputeTopLeft( ref Window window )
        {
            W32Point pt = new W32Point();
            if ( !GetCursorPos( ref pt ) )
            {
                Marshal.ThrowExceptionForHR( Marshal.GetHRForLastWin32Error() );
            }
 
            // 0x00000002: return nearest monitor if pt is not contained in any monitor.
            IntPtr monHandle = MonitorFromPoint( pt, 0x00000002 );
            W32MonitorInfo monInfo = new W32MonitorInfo();
            monInfo.Size = Marshal.SizeOf( typeof( W32MonitorInfo ) );
 
            if ( !GetMonitorInfo( monHandle, ref monInfo ) )
            {
                Marshal.ThrowExceptionForHR( Marshal.GetHRForLastWin32Error() );
            }
 
            // use WorkArea struct to include the taskbar position.
            W32Rect monitor = monInfo.WorkArea;
            double offsetX = Math.Round( window.Width / 2 );
            double offsetY = Math.Round( window.Height / 2 );
 
            double top = pt.Y - offsetY;
            double left = pt.X - offsetX;
 
            Rect screen = new Rect (
                new Point( monitor.Left, monitor.Top ),
                new Point( monitor.Right, monitor.Bottom ) );
            Rect wnd = new Rect(
                new Point( left, top ),
                new Point( left + window.Width, top + window.Height ) );
 
            window.Top = wnd.Top;
            window.Left = wnd.Left;
 
            if ( !screen.Contains( wnd ) )
            {
                if ( wnd.Top < screen.Top )
                {
                    double diff = Math.Abs( screen.Top - wnd.Top );
                    window.Top = wnd.Top + diff;
                }
 
                if ( wnd.Bottom > screen.Bottom )
                {
                    double diff = wnd.Bottom - screen.Bottom;
                    window.Top = wnd.Top - diff;
                }
 
                if ( wnd.Left < screen.Left )
                {
                    double diff = Math.Abs( screen.Left - wnd.Left );
                    window.Left = wnd.Left + diff;
                }
 
                if ( wnd.Right > screen.Right )
                {
                    double diff = wnd.Right - screen.Right;
                    window.Left = wnd.Left - diff;
                }
            }
        }
 
        [DllImport( "user32.dll", SetLastError = true )]
        [return: MarshalAs( UnmanagedType.Bool )]
        private static extern bool GetCursorPos( ref W32Point pt );
 
        [DllImport( "user32.dll", SetLastError = true )]
        [return: MarshalAs( UnmanagedType.Bool )]
        private static extern bool GetMonitorInfo( IntPtr hMonitor, ref W32MonitorInfo lpmi );
 
        [DllImport( "user32.dll" )]
        private static extern IntPtr MonitorFromPoint( W32Point pt, uint dwFlags );
 
        [StructLayout( LayoutKind.Sequential )]
        public struct W32Point
        {
            public int X;
            public int Y;
        }
 
        [StructLayout( LayoutKind.Sequential )]
        internal struct W32MonitorInfo
        {
            public int Size;
            public W32Rect Monitor;
            public W32Rect WorkArea;
            public uint Flags;
        }
 
        [StructLayout( LayoutKind.Sequential )]
        internal struct W32Rect
        {
            public int Left;
            public int Top;
            public int Right;
            public int Bottom;
        }

        [DllImport("user32.dll")]
        [return: MarshalAs(UnmanagedType.Bool)]
        internal static extern bool GetCursorPos(ref Win32Point pt);

        [StructLayout(LayoutKind.Sequential)]
        internal struct Win32Point
        {
            public Int32 X;
            public Int32 Y;
        };
        public static Point GetMousePosition()
        {
            Win32Point w32Mouse = new Win32Point();
            GetCursorPos(ref w32Mouse);
            return new Point(w32Mouse.X, w32Mouse.Y);
        }
    }
}
