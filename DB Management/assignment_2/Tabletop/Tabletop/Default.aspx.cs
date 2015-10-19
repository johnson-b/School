using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace Tabletop
{
    public partial class _Default : Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }

        protected void Insert(object sender, EventArgs e)
        {
            SqlDataSource1.Insert();
            txtName.Text = "";
            txtMinPlayers.Text = "";
            txtMaxPlayers.Text = "";
            txtTimetoPlay.Text = "";
        }

        protected void Select(object sender, EventArgs e)
        {
            string search = txtSearch.Text;
            string select;
            if (string.IsNullOrEmpty(search))
            {
                select = "SELECT * FROM [Tabletop]";
            }
            else
            {
                select = string.Format("SELECT * FROM [Tabletop] WHERE [Name] LIKE '%{0}%' OR [MinimumPlayers] LIKE '%{0}%' OR [MaximumPlayers] LIKE '%{0}%' OR [TimeInMinutes] LIKE '%{0}%'", search);
            }
            
            SqlDataSource1.SelectCommand = select;
            SqlDataSource1.Select(DataSourceSelectArguments.Empty);
        }
    }
}