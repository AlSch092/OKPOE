using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace OKPOEAuthServer
{
    class Program
    {
        static void Main(string[] args)
        {
            Offsets s = new Offsets();

            Listener auth = new Listener();
            auth.AuthenticateUsers();
        }
    }
}
