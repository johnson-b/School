using Microsoft.Owin;
using Owin;

[assembly: OwinStartupAttribute(typeof(Tabletop.Startup))]
namespace Tabletop
{
    public partial class Startup {
        public void Configuration(IAppBuilder app) {
            ConfigureAuth(app);
        }
    }
}
