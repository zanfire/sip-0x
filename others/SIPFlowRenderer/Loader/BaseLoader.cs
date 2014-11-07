using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using sip0xnet;
using System.Collections.Specialized;

namespace SIPFlowRenderer
{
    public abstract class BaseLoader
    {
        public struct LogEntry
        {
            public string date;
            public string time;
            public string dir;
            public string fromHost;
            public string toHost;
            public string payload;
        }

        #region Members

        protected List<LogEntry> _entries = new List<LogEntry>();
        protected string _filename;

        #endregion

        public BaseLoader(string filename)
        {
            _filename = filename;
        }

        public abstract void Load();

        public List<LogEntry> GetMessages()
        {
            return _entries;
        }

        public StringCollection GetEntities(bool mergePort = true) 
        {
            StringCollection entities = new StringCollection();

            foreach (LogEntry entry in _entries) {
                string ip = mergePort ? StripPort(entry.fromHost) : entry.fromHost;
                if (!entities.Contains(ip)) {
                    entities.Add(ip);
                }
                
                ip = mergePort ? StripPort(entry.toHost) : entry.toHost;
                if (!entities.Contains(ip)) {
                    entities.Add(ip);
                }
            }

            return entities;
        }

        public static string StripPort(string ip) {
            int idx = ip.LastIndexOf(':');
            if (idx >= 0) {
                return ip.Substring(0, idx);
            }
            else {
                return ip;
            }
        }
    }
}
