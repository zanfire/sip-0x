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
    internal class PlainTextLogLoader : BaseLoader
    {

        public PlainTextLogLoader(string filename) : base(filename)
        {
        }

        public override void Load()
        {
            
            using (StreamReader reader = File.OpenText(_filename))
            {
                LogEntry current = new LogEntry();
                bool readingPayload = false;
                while (!reader.EndOfStream)
                {
                    string line = reader.ReadLine();
                    if (!readingPayload)
                    {
                        string[] tokens = line.Split(new string[] { " ", "[", "]" }, StringSplitOptions.RemoveEmptyEntries);
                        if (tokens.Length == 6)
                        {
                            current.date = tokens[0];
                            current.time = tokens[1];
                            current.dir = tokens[2];
                            current.fromHost = tokens[3];
                            current.toHost = tokens[5];

                            reader.ReadLine(); // skip empty line ...
                            readingPayload = true;
                        }
                        else
                        {
                            System.Diagnostics.Debug.WriteLine("Failed parse line.");
                            break;
                        }
                    }
                    else
                    {
                        if (line.Equals("-----------------------"))
                        {
                            readingPayload = false;
                            _entries.Add(current);
                            current = new LogEntry();
                        }
                        else
                        {
                            current.payload += line;
                            current.payload += "\r\n";
                        }
                    }
                }
            }
        }
    }
}
