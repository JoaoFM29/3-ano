using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace BirdBoxFull.Server.Migrations
{
    public partial class DecimaQuarta : Migration
    {
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.AddColumn<string>(
                name: "AccountStripeId",
                table: "Utilizadores",
                type: "nvarchar(max)",
                nullable: false,
                defaultValue: "");
        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropColumn(
                name: "AccountStripeId",
                table: "Utilizadores");
        }
    }
}
