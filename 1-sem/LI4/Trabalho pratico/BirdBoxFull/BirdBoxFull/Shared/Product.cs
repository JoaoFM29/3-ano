using System;
using System.Collections.Generic;

namespace BirdBoxFull.Shared
{
    public class Product
    {
        public List<string> Images { get; set; }
        public string Name { get; set; }
        public decimal EntryPrice { get; set; }
        public string Location { get; set; }
        public bool IsPublic { get; set; }

        public Product()
        {
        }
    }
}
