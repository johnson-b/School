<%@ Page Title="Tabletop Games" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="About.aspx.cs" Inherits="Tabletop.About" %>

<asp:Content ID="BodyContent" ContentPlaceHolderID="MainContent" runat="server">
    <h2><%: Title %>.</h2>
    <h3>Simple CRUD for Tabletop games.</h3>
    <p>There are four main functions to our web form. Users can do the following:</p>
    <ul>
        <li>
            <b>Create</b> - fill out the necessary text boxes and click <i>'Add'</i>.
        </li>
        <li>
            <b>Read</b> - simply look at the table.
        </li>
        <li>
            <b>Update</b> - Click <i>'Edit'</i> and modify the values. Click <i>'Update'</i> when you are done.
        </li>
        <li>
            <b>Delete</b> - Click <i>'Delete'</i> to delete a row from the table.
        </li>
        <li>
            <b>Sort</b> - Clicking on any of the table headers will sort the row by that column.
        </li>
        <li>
            <b>Search</b> - Type anything into the search box and click <i>'Search'</i>.
        </li>
    </ul>
</asp:Content>
