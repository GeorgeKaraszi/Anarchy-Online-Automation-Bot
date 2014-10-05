using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace InjectionApp
{
    public partial class SWTORHookGUI : Form
    {

        private Boolean foundGame = false;
        private List<WindowNode> Windows = new List<WindowNode>();

        public delegate bool WindowEnumCallback(int hwnd, int lparam);

        [DllImport("user32.dll")]
        [return: MarshalAs(UnmanagedType.Bool)]
        static extern bool EnumWindows(WindowEnumCallback lpEnumFunc, int lParam);

        [DllImport("user32.dll")]
        public static extern void GetWindowText(int h, StringBuilder s, int nMaxCount);

        [DllImport("user32.dll")]
        public static extern bool IsWindowVisible(int h);


        private bool AddWnd(int hwnd, int lparam)
        {
            if (IsWindowVisible(hwnd))
            {
                StringBuilder sb = new StringBuilder(255);
                GetWindowText(hwnd, sb, sb.Capacity);
                Windows.Add(new WindowNode(sb.ToString(), hwnd));
            }
            return true;
        }

        private void bw_DoWork(object sender, DoWorkEventArgs e)
        {
            int index = 0;
            Process[] processList = Process.GetProcessesByName("AnarchyOnline");
            DllInjector dllInjector = new DllInjector("C:\\Users\\George\\Source\\Repos\\Artemis\\Artemis\\Debug\\AO.dll");

            while (foundGame == false)
            {
                processList = Process.GetProcessesByName("AnarchyOnline");
                if (processList.Length > 0)
                    foundGame = true;

            }

            dllInjector.Inject(processList[0]);


            BeginInvoke(new MethodInvoker(Close));

        }

        public SWTORHookGUI()
        {
            InitializeComponent();
        }

        private void SWTORHookGUI_Load(object sender, EventArgs e)
        {
            bgFindGameThread.WorkerSupportsCancellation = true;
            bgFindGameThread.WorkerReportsProgress = false;
            bgFindGameThread.DoWork += new DoWorkEventHandler(bw_DoWork);
            bgFindGameThread.RunWorkerAsync();
        }
    }
}
