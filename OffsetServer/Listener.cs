using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace OKPOEAuthServer
{
    class Listener
    {
        private const byte XorKey = 0xF3;

        static char[] ignoredChars = { ' ', '\n', '\0', '\r', '�' };

        private static int  port_listen = 5445;

        public byte[] Decrypt(byte[] inBuffer, int length)
        {
            byte[] msg = new byte[length]; 

            for (int i = 0; i < length; i++) //decrypt   , simple xor       
                msg[i] = (byte)(inBuffer[i] ^ XorKey);
           
            return msg;
        }

        public void AuthenticateUsers() //should be split into more routines, one for packet handling, one for auth, etc.
        {
            TcpListener server = new TcpListener(IPAddress.Any, port_listen);

            server.Start();

            bool listening = true;

            while (listening)   //we wait for a connection
            {
                TcpClient client = server.AcceptTcpClient();  //if a connection exists, the server will accept it

                NetworkStream ns = client.GetStream();

                if (client.Connected)
                {
                    IPEndPoint ipep = (IPEndPoint)client.Client.RemoteEndPoint;
                    IPAddress ipa = ipep.Address;

                    if (FileIO.isIPBanned(Convert.ToString(ipep.Address)))
                    {
                        Console.WriteLine("Detected banned ip: " + ipep.Address);
                        ns.Close();
                        client.Close();
                        continue;
                    }

                    byte[] msg = new byte[512];
                    int bytesRead = 0;

                    try
                    {
                        bytesRead = ns.Read(msg, 0, 500);
                    }
                    catch(Exception e)
                    {
                        Console.WriteLine("Couldn't read client data from stream: {0}", e.Message);
                    }

                    if(bytesRead > 500 || bytesRead == 0)
                    {
                        Console.WriteLine("bytesRead had a wrong length, disconnecting client");
                        client.Close();
                        ns.Close();
                        continue;
                    }
                            
                    byte[] deCryptMsg = Decrypt(msg, bytesRead);

                    string inMsg = Encoding.UTF8.GetString(deCryptMsg); //bytes to string
                        
                    string trimmedMsg = inMsg.Trim(ignoredChars);

                    Console.WriteLine("Got Msg: {0} from IP {1}", trimmedMsg, ipep.Address); //now , we write the message as string

                    if (FileIO.containsHWID(trimmedMsg)) //Hardware ID from client -> checks HWIDs.txt, if correct it sends offsets to client
                    {
                        Offsets OfsList = new Offsets();
                        ulong[] Offsets = OfsList.FormOffsetList(); //get offsets from Offsets.txt

                        byte[] bOffsets = new byte[1024];

                        int count = 0;

                        foreach (ulong Offset in Offsets) //copy them into byte[] payload and send it back to client
                        {
                            Buffer.BlockCopy(Offsets, count * 8, bOffsets, (count * 8), 8);                    
                            count = count + 1;
                        }

                        try
                        {
                            ns.Write(bOffsets, 0, Offsets.Count() * 8);     //sending the message

                            string Content = "[" + DateTime.Now + "] IP: " + ipep.Address + " HWID: " + inMsg.Trim(ignoredChars) + ", VERIFIED\r\n";
                            FileIO.WriteToFile("log.txt", Content);
                        }
                        catch(Exception e)
                        {
                            Console.WriteLine("[WARNING] Failed to send data back to client: {0}", e.Message);

                            string Content = "[WARNING] Failed to send data back to client: " + e.Message + "\r\n";
                            FileIO.WriteToFile("log.txt", Content);
                        }
                    }
                    else //heartbeat from client
                    {
                        if (deCryptMsg[0] == 0x01 && deCryptMsg[1] == 0x02 && deCryptMsg[2] == 0x03 && deCryptMsg[3] == 0x04)
                        {
                            Console.WriteLine("Heartbeat received... sending back pong");
                                
                            byte[] mirror = { 0x02, 0x04, 0x06, 0x08 }; //test msg
                                
                            ns.Write(mirror, 0, 4);     //sending the message

                            string Content = "[" + DateTime.Now + "] IP: " + ipep.Address + " HWID: " + inMsg + " H-B Approved!";
                            FileIO.WriteToFile("log.txt", Content);

                        }
                        else if(deCryptMsg[0] == 2) //player chat/string data (saves trades history) -> save in log.txt
                        {
                            //string Content = "[" + DateTime.Now + "] IP: " + ipep.Address + " HWID: " + inMsg + ", ! H-B REJECTED!";
                            Console.WriteLine("Got Message: {0}", inMsg);
                            string content = "[Ip: " + ipep.Address + " at " + DateTime.Now + "] " + inMsg.Substring(1);
                            FileIO.WriteToFile("msgs.txt", content);
                        }
                        else
                        {
                            Console.WriteLine("Got unknown packet: {0} from {1}", inMsg, ipep.Address); //disconnect client on unknown packet in
                            client.Close();
                            ns.Close();
                            return;
                        }
                    }
                                       
                    ns.Close();
                    client.Close();
                }
            }   

        }   
    }
}
