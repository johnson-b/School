<%@ Page Title="Home Page" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="Default.aspx.cs" Inherits="Tabletop._Default" %>

<asp:Content ID="BodyContent" ContentPlaceHolderID="MainContent" runat="server">

    <div class="jumbotron">
        <p>
            <asp:GridView ID="GridView1" CssClass="table table-striped" runat="server" AutoGenerateColumns="False" CellPadding="4" DataKeyNames="tid" DataSourceID="SqlDataSource1" EmptyDataText="There are no data records to display." GridLines="None" AllowSorting="True">
                <AlternatingRowStyle BackColor="White" />
                <Columns>   
                    <asp:CommandField ShowDeleteButton="True" ShowEditButton="True" />
                    <asp:BoundField DataField="tid" HeaderText="" ReadOnly="True" SortExpression="tid" Visible="false" />
                    <asp:BoundField DataField="Name" HeaderText="Name" SortExpression="Name" />
                    <asp:BoundField DataField="MinimumPlayers" HeaderText="Min-Players" SortExpression="MinimumPlayers" />
                    <asp:BoundField DataField="MaximumPlayers" HeaderText="Max-Players" SortExpression="MaximumPlayers" />
                    <asp:BoundField DataField="TimeInMinutes" HeaderText="Time to Play (minutes)" SortExpression="TimeInMinutes" />
                </Columns>
                <%--<EditRowStyle BackColor="#2461BF" />--%>
             <%--   <FooterStyle BackColor="#507CD1" Font-Bold="True" ForeColor="White" />
                <HeaderStyle BackColor="#507CD1" Font-Bold="True" ForeColor="White" />
                <PagerStyle BackColor="#2461BF" ForeColor="White" HorizontalAlign="Center" />
                <RowStyle BackColor="#EFF3FB" />
                <SelectedRowStyle BackColor="#D1DDF1" Font-Bold="True" ForeColor="#333333" />
                <SortedAscendingCellStyle BackColor="#F5F7FB" />
                <SortedAscendingHeaderStyle BackColor="#6D95E1" />
                <SortedDescendingCellStyle BackColor="#E9EBEF" />
                <SortedDescendingHeaderStyle BackColor="#4870BE" />--%>
            </asp:GridView>



            <asp:Table runat="server">
                <asp:TableHeaderRow runat="server">
                    <asp:TableHeaderCell>Name</asp:TableHeaderCell>
                    <asp:TableHeaderCell>Min. Players</asp:TableHeaderCell>
                    <asp:TableHeaderCell>Min. Players</asp:TableHeaderCell>
                    <asp:TableHeaderCell>Time to Play</asp:TableHeaderCell>
                    <asp:TableHeaderCell></asp:TableHeaderCell>
                </asp:TableHeaderRow>
                <asp:TableRow>
                    <asp:TableCell>
                        <asp:TextBox ID="txtName" runat="server" Width="140" BorderStyle="None" />
                    </asp:TableCell>
                    <asp:TableCell>
                        <asp:TextBox ID="txtMinPlayers" runat="server" Width="140" BorderStyle="None" />
                    </asp:TableCell>
                    <asp:TableCell>
                        <asp:TextBox ID="txtMaxPlayers" runat="server" Width="140" BorderStyle="None" />
                    </asp:TableCell>
                    <asp:TableCell>
                        <asp:TextBox ID="txtTimetoPlay" runat="server" Width="140" BorderStyle="None" />
                    </asp:TableCell>
                    <asp:TableCell>
                        <asp:Button ID="btnAdd" runat="server" Text="Add" OnClick="Insert" BorderStyle="None" BackColor="#507CD1" ForeColor="White" />
                    </asp:TableCell>
                </asp:TableRow>
            </asp:Table>

            <asp:Table runat="server">
                <asp:TableHeaderRow runat="server">
                    <asp:TableCell>
                        <asp:TextBox ID="txtSearch" runat="server" Width="340" BorderStyle="None" />
                    </asp:TableCell>
                    <asp:TableCell>
                        <asp:Button ID="btnSearch" runat="server" Text="Search" OnClick="Select" BorderStyle="None" BackColor="#507CD1" ForeColor="White" />
                    </asp:TableCell>
                </asp:TableHeaderRow>
            </asp:Table>

            <asp:SqlDataSource ID="SqlDataSource1" runat="server" ConnectionString="<%$ ConnectionStrings:bmj29_db2015ConnectionString1 %>"
                DeleteCommand="DELETE FROM [Tabletop] WHERE [tid] = @tid"
                InsertCommand="INSERT INTO [Tabletop] ([Name], [MinimumPlayers], [MaximumPlayers], [TimeInMinutes]) VALUES (@Name, @MinimumPlayers, @MaximumPlayers, @TimeInMinutes)"
                ProviderName="<%$ ConnectionStrings:bmj29_db2015ConnectionString1.ProviderName %>"
                SelectCommand="SELECT * FROM [Tabletop]"
                UpdateCommand="UPDATE [Tabletop] SET [Name] = @Name, [MinimumPlayers] = @MinimumPlayers, [MaximumPlayers] = @MaximumPlayers, [TimeInMinutes] = @TimeInMinutes WHERE [tid] = @tid">
                <DeleteParameters>
                    <asp:Parameter Name="tid" Type="Int32" />
                </DeleteParameters>
                <InsertParameters>
                    <asp:ControlParameter Name="Name" ControlID="txtName" Type="String" />
                    <asp:ControlParameter Name="MinimumPlayers" ControlID="txtMinPlayers" Type="Int32" />
                    <asp:ControlParameter Name="MaximumPlayers" ControlID="txtMaxPlayers" Type="Int32" />
                    <asp:ControlParameter Name="TimeInMinutes" ControlID="txtTimetoPlay" Type="Int32" />
                </InsertParameters>
                <UpdateParameters>
                    <asp:Parameter Name="Name" Type="String" />
                    <asp:Parameter Name="MinimumPlayers" Type="Int32" />
                    <asp:Parameter Name="MaximumPlayers" Type="Int32" />
                    <asp:Parameter Name="TimeInMinutes" Type="Int32" />
                    <asp:Parameter Name="tid" Type="Int32" />
                </UpdateParameters>
                <%--<SelectParameters>
                    <asp:ControlParameter Name="Search" ControlID="txtSearch" Type="String" />
                </SelectParameters>--%>
            </asp:SqlDataSource>
        </p>
        <p>
            &nbsp;
        </p>
    </div>
</asp:Content>
