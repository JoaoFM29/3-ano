using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace BirdBoxFull.Server.Migrations
{
    public partial class Fith5 : Migration
    {
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropForeignKey(
                name: "FK_Encomendas_Leiloes_LeilaoCodLeilao",
                table: "Encomendas");

            migrationBuilder.DropForeignKey(
                name: "FK_Encomendas_Leiloes_LeilaoCodLeilao1",
                table: "Encomendas");

            migrationBuilder.DropIndex(
                name: "IX_Encomendas_LeilaoCodLeilao",
                table: "Encomendas");

            migrationBuilder.DropIndex(
                name: "IX_Encomendas_LeilaoCodLeilao1",
                table: "Encomendas");

            migrationBuilder.DropColumn(
                name: "LeilaoCodLeilao1",
                table: "Encomendas");

            migrationBuilder.CreateIndex(
                name: "IX_Encomendas_LeilaoCodLeilao",
                table: "Encomendas",
                column: "LeilaoCodLeilao",
                unique: true);

            migrationBuilder.AddForeignKey(
                name: "FK_Encomendas_Leiloes_LeilaoCodLeilao",
                table: "Encomendas",
                column: "LeilaoCodLeilao",
                principalTable: "Leiloes",
                principalColumn: "CodLeilao",
                onDelete: ReferentialAction.Cascade);
        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropForeignKey(
                name: "FK_Encomendas_Leiloes_LeilaoCodLeilao",
                table: "Encomendas");

            migrationBuilder.DropIndex(
                name: "IX_Encomendas_LeilaoCodLeilao",
                table: "Encomendas");

            migrationBuilder.AddColumn<string>(
                name: "LeilaoCodLeilao1",
                table: "Encomendas",
                type: "nvarchar(450)",
                nullable: true);

            migrationBuilder.CreateIndex(
                name: "IX_Encomendas_LeilaoCodLeilao",
                table: "Encomendas",
                column: "LeilaoCodLeilao");

            migrationBuilder.CreateIndex(
                name: "IX_Encomendas_LeilaoCodLeilao1",
                table: "Encomendas",
                column: "LeilaoCodLeilao1",
                unique: true,
                filter: "[LeilaoCodLeilao1] IS NOT NULL");

            migrationBuilder.AddForeignKey(
                name: "FK_Encomendas_Leiloes_LeilaoCodLeilao",
                table: "Encomendas",
                column: "LeilaoCodLeilao",
                principalTable: "Leiloes",
                principalColumn: "CodLeilao");

            migrationBuilder.AddForeignKey(
                name: "FK_Encomendas_Leiloes_LeilaoCodLeilao1",
                table: "Encomendas",
                column: "LeilaoCodLeilao1",
                principalTable: "Leiloes",
                principalColumn: "CodLeilao");
        }
    }
}
