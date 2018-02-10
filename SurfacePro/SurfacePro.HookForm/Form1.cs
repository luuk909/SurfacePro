using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using SurfacePro.Hooks;

namespace SurfacePro.HookForm
{
    public partial class Form1 : Form
    {
        KeyboardHook kbHook = new KeyboardHook();
        MouseHook mHook = new MouseHook();

        public List<KeyStats> Stats { get; set; }

        public Form1()
        {
            InitializeComponent();

            Stats = new List<KeyStats>();
            UpdateList();

            kbHook.Install();
            kbHook.KeyDown += KeyboardKeyDown;
            kbHook.KeyUp += KeyboardKeyUp;
            //mHook.Install();
            //mHook.
        }

        private void UpdateList()
        {
            dgvKeyboard.Rows.Clear();
            foreach (KeyStats stats in Stats)
                dgvKeyboard.Rows.Add(stats.Key, stats.UpCount, stats.DownCount);
        }

        private KeyStats GetKeyStats(VKeys key)
        {
            KeyStats stat = Stats.FirstOrDefault(s => s.Key == key);
            if (stat == null)
            {
                stat = new KeyStats(key);
                Stats.Add(stat);
            }

            return stat;
        }

        public void KeyboardKeyDown(VKeys key)
        {
            GetKeyStats(key).DownCount++;
            UpdateList();
        }

        public void KeyboardKeyUp(VKeys key)
        {
            GetKeyStats(key).UpCount++;
            UpdateList();
        }
    }
}
