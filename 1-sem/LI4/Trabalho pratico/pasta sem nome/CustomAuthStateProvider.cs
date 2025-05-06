using Microsoft.AspNetCore.Components.Authorization;
using System.Security.Authentication;

namespace BirdBoxFull.Client
{
    public class CustomAuthStateProvider : AuthenticationStateProvider
    {
        public override async Task<AuthenticationState> GetAuthenticationStateAsync()
        {
            throw new NotImplementedException();
        }
    }
}
