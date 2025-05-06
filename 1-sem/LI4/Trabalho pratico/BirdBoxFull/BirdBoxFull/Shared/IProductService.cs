using System;

namespace BirdBoxFull.Shared
{
	public interface IProductService
	{
        Task<Product> GetProductDetails();
    }
}

