using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace BirdBoxFull.Server.Migrations
{
    public partial class Second2 : Migration
    {
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.AlterColumn<string>(
                name: "UtilizadorUsername",
                table: "Leiloes",
                type: "nvarchar(450)",
                nullable: false,
                oldClrType: typeof(string),
                oldType: "nvarchar(max)");

            migrationBuilder.CreateIndex(
                name: "IX_Leiloes_UtilizadorUsername",
                table: "Leiloes",
                column: "UtilizadorUsername");

            migrationBuilder.AddForeignKey(
                name: "FK_Leiloes_Utilizadores_UtilizadorUsername",
                table: "Leiloes",
                column: "UtilizadorUsername",
                principalTable: "Utilizadores",
                principalColumn: "Username",
                onDelete: ReferentialAction.Cascade);
        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropForeignKey(
                name: "FK_Leiloes_Utilizadores_UtilizadorUsername",
                table: "Leiloes");

            migrationBuilder.DropIndex(
                name: "IX_Leiloes_UtilizadorUsername",
                table: "Leiloes");

            migrationBuilder.AlterColumn<string>(
                name: "UtilizadorUsername",
                table: "Leiloes",
                type: "nvarchar(max)",
                nullable: false,
                oldClrType: typeof(string),
                oldType: "nvarchar(450)");
        }
    }
}
