using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using sip0xnet;
using System.Collections.Specialized;
using System.Text.RegularExpressions;

namespace SIPFlowRenderer
{
    internal class MirialLogLoader : BaseLoader
    {

        public MirialLogLoader(string filename) : base(filename)
        {
        }

        public override void Load()
        {
            /*
2014-09-23 00:00:28,050|8ydy|DEBUG|0x7f7cd198f700-4432|libdylogicsip.SIPManager	|REQ|TLS|2133|OPTIONS|1092b5e0-a0a215e-13c5-45026-54205958-21daf65-54205958|sip:124001728%4050.97.125.156@lifesizecloudbeta.com;user=phone|sip:4801@lifesizecloudbeta.com;transport=TLS|458be5aad3|540| 5.153.18.34:35061 --> 207.114.244.5:13326 TX  540 bytes
OPTIONS sip:4801@10.10.33.94;transport=TLS SIP/2.0
To: <sip:4801@lifesizecloudbeta.com;transport=TLS>;tag=10924428-a0a215e-13c5-45026-54205958-3992cddb-54205958
From: "ClearSea" <sip:124001728%4050.97.125.156@lifesizecloudbeta.com;user=phone>;tag=DL31adb3006b;epid=0x2be7ab0
CSeq: 2133 OPTIONS
Call-ID: 1092b5e0-a0a215e-13c5-45026-54205958-21daf65-54205958
Max-Forwards: 70
Via: SIP/2.0/TLS 5.153.18.34:35061;branch=z9hG4bK-64c1f32861-DL;alias
Contact: "ClearSea" <sip:ClearSea@5.153.18.34:35061;transport=tls>
Content-Length: 0


2014-09-23 00:00:28,050|8ydy|DEBUG|0x7f7cd198f700-4432|libdylogicsip.SIPManager	|[sent 540 bytes]

             */
            using (StreamReader reader = File.OpenText(_filename))
            {
                Regex regexTX = new Regex("TX  [0-9]* bytes$");
                Regex regexRX = new Regex("\\[received\\] \\[[0-9]* bytes\\]$");
                LogEntry current = new LogEntry();
                bool readingPayload = false;
                while (!reader.EndOfStream)
                {
                    string line = reader.ReadLine();
                    string[] tokens = line.Split(new string[] { "|" }, StringSplitOptions.RemoveEmptyEntries);
                    if (!readingPayload)
                    {
                        // 2014-09-23 00:00:28,050|8ydy|DEBUG|0x7f7cd198f700-4432|libdylogicsip.SIPManager	
                        // |REQ|TLS|2133|OPTIONS|1092b5e0-a0a215e-13c5-45026-54205958-21daf65-54205958|
                        // sip:124001728%4050.97.125.156@lifesizecloudbeta.com;user=phone|
                        // sip:4801@lifesizecloudbeta.com;transport=TLS|458be5aad3|540|
                        // 5.153.18.34:35061 --> 207.114.244.5:13326 TX  540 bytes
                        // 207.114.244.5:13326 --> 5.153.18.34:35061 [received] [775 bytes]
                        if (tokens.Length >= 14 && (tokens[2] == "DEBUG" || tokens[2] == "INFO ") && tokens[4] == "libdylogicsip.SIPManager\t")
                        {

                            bool resTX = regexTX.IsMatch(tokens[14]);
                            bool resRX = !resTX ? regexRX.IsMatch(tokens[14]) : false;
                            if (resTX || resRX)
                            {
                                string[] seps = new string[] { " " };
                                String[] timeRefs = tokens[0].Split(seps, StringSplitOptions.RemoveEmptyEntries);
                                String[] addresses = tokens[14].Split(seps, StringSplitOptions.RemoveEmptyEntries);
                                current.date = timeRefs[0];
                                current.time = timeRefs[1];
                                current.dir = tokens[2];
                                current.fromHost = addresses[0];
                                current.toHost = addresses[2];
                                readingPayload = true;
                            }
                        }
                    }
                    else
                    {
                        if (tokens.Length >= 5)
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
