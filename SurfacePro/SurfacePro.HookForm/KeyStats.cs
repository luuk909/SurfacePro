using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SurfacePro.Hooks;

namespace SurfacePro.HookForm
{
    public class KeyStats
    {
        public KeyStats(VKeys key)
        {
            Key = key;
        }

        public VKeys Key { get; set; }
        public int UpCount { get; set; }
        public int DownCount { get; set; }
    }
}
