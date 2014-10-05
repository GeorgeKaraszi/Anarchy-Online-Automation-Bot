using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace InjectionApp
{
    class WindowNode
    {
        public string WindowsName { get; set; }
        public int HWID { get; set; }

        public WindowNode(string WindowsName, int HWID)
        {
            this.WindowsName = WindowsName;
            this.HWID = HWID;
        }
    }
}
