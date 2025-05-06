using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace BirdBoxFull.Server.Migrations
{
    public partial class Fith4 : Migration
    {
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.CreateTable(
                name: "Encomendas",
                columns: table => new
                {
                    codEncomenda = table.Column<string>(type: "nvarchar(450)", nullable: false),
                    LeilaoCodLeilao = table.Column<string>(type: "nvarchar(450)", nullable: false),
                    UtilizadorUsername = table.Column<string>(type: "nvarchar(450)", nullable: false),
                    numeroSeguimento = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    LeilaoCodLeilao1 = table.Column<string>(type: "nvarchar(450)", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Encomendas", x => x.codEncomenda);
                    table.ForeignKey(
                        name: "FK_Encomendas_Leiloes_LeilaoCodLeilao",
                        column: x => x.LeilaoCodLeilao,
                        principalTable: "Leiloes",
                        principalColumn: "CodLeilao");
                    table.ForeignKey(
                        name: "FK_Encomendas_Leiloes_LeilaoCodLeilao1",
                        column: x => x.LeilaoCodLeilao1,
                        principalTable: "Leiloes",
                        principalColumn: "CodLeilao");
                    table.ForeignKey(
                        name: "FK_Encomendas_Utilizadores_UtilizadorUsername",
                        column: x => x.UtilizadorUsername,
                        principalTable: "Utilizadores",
                        principalColumn: "Username");
                });

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

            migrationBuilder.CreateIndex(
                name: "IX_Encomendas_UtilizadorUsername",
                table: "Encomendas",
                column: "UtilizadorUsername");
        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "Encomendas");
        }
    }
}
