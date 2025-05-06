using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BirdBoxFull.Shared
{
    public class WishList
    {
        [Key]
        public string LeilaoCodLeilao { get; set; }
        
        public Leilao Leilao { get; set; }
        [Key]
        public string UtilizadorUsername { get; set; }
        
        public Utilizador Utilizador { get; set; }
    }
}
