using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace BirdBoxFull.Server.Migrations
{
    public partial class eight : Migration
    {
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropForeignKey(
                name: "FK_Utilizadores_Leiloes_LeilaoCodLeilao",
                table: "Utilizadores");

            migrationBuilder.DropIndex(
                name: "IX_Utilizadores_LeilaoCodLeilao",
                table: "Utilizadores");

            migrationBuilder.DropColumn(
                name: "LeilaoCodLeilao",
                table: "Utilizadores");
        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.AddColumn<string>(
                name: "LeilaoCodLeilao",
                table: "Utilizadores",
                type: "nvarchar(450)",
                nullable: true);

            migrationBuilder.CreateIndex(
                name: "IX_Utilizadores_LeilaoCodLeilao",
                table: "Utilizadores",
                column: "LeilaoCodLeilao");

            migrationBuilder.AddForeignKey(
                name: "FK_Utilizadores_Leiloes_LeilaoCodLeilao",
                table: "Utilizadores",
                column: "LeilaoCodLeilao",
                principalTable: "Leiloes",
                principalColumn: "CodLeilao");
        }
    }
}
