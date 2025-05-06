using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace BirdBoxFull.Server.Migrations
{
    public partial class Six : Migration
    {
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.AddColumn<string>(
                name: "LeilaoCodLeilao",
                table: "Utilizadores",
                type: "nvarchar(450)",
                nullable: true);

            migrationBuilder.CreateTable(
                name: "WishLists",
                columns: table => new
                {
                    LeilaoCodLeilao = table.Column<string>(type: "nvarchar(450)", nullable: false),
                    UtilizadorUsername = table.Column<string>(type: "nvarchar(450)", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_WishLists", x => new { x.LeilaoCodLeilao, x.UtilizadorUsername });
                    table.ForeignKey(
                        name: "FK_WishLists_Leiloes_LeilaoCodLeilao",
                        column: x => x.LeilaoCodLeilao,
                        principalTable: "Leiloes",
                        principalColumn: "CodLeilao");
                    table.ForeignKey(
                        name: "FK_WishLists_Utilizadores_UtilizadorUsername",
                        column: x => x.UtilizadorUsername,
                        principalTable: "Utilizadores",
                        principalColumn: "Username");
                });

            migrationBuilder.CreateIndex(
                name: "IX_Utilizadores_LeilaoCodLeilao",
                table: "Utilizadores",
                column: "LeilaoCodLeilao");

            migrationBuilder.CreateIndex(
                name: "IX_WishLists_UtilizadorUsername",
                table: "WishLists",
                column: "UtilizadorUsername");

            migrationBuilder.AddForeignKey(
                name: "FK_Utilizadores_Leiloes_LeilaoCodLeilao",
                table: "Utilizadores",
                column: "LeilaoCodLeilao",
                principalTable: "Leiloes",
                principalColumn: "CodLeilao");
        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropForeignKey(
                name: "FK_Utilizadores_Leiloes_LeilaoCodLeilao",
                table: "Utilizadores");

            migrationBuilder.DropTable(
                name: "WishLists");

            migrationBuilder.DropIndex(
                name: "IX_Utilizadores_LeilaoCodLeilao",
                table: "Utilizadores");

            migrationBuilder.DropColumn(
                name: "LeilaoCodLeilao",
                table: "Utilizadores");
        }
    }
}
