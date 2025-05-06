using System;
using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace BirdBoxFull.Server.Migrations
{
    public partial class Fourth9 : Migration
    {
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.CreateTable(
                name: "Licitacoes",
                columns: table => new
                {
                    codLicitacao = table.Column<string>(type: "nvarchar(450)", nullable: false),
                    LeilaoCodLeilao = table.Column<string>(type: "nvarchar(450)", nullable: false),
                    UtilizadorUsername = table.Column<string>(type: "nvarchar(450)", nullable: false),
                    valor = table.Column<float>(type: "real", nullable: false),
                    timestamp = table.Column<DateTime>(type: "datetime2", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Licitacoes", x => x.codLicitacao);
                    table.ForeignKey(
                        name: "FK_Licitacoes_Leiloes_LeilaoCodLeilao",
                        column: x => x.LeilaoCodLeilao,
                        principalTable: "Leiloes",
                        principalColumn: "CodLeilao");
                    table.ForeignKey(
                        name: "FK_Licitacoes_Utilizadores_UtilizadorUsername",
                        column: x => x.UtilizadorUsername,
                        principalTable: "Utilizadores",
                        principalColumn: "Username");
                });

            migrationBuilder.CreateIndex(
                name: "IX_Licitacoes_LeilaoCodLeilao",
                table: "Licitacoes",
                column: "LeilaoCodLeilao");

            migrationBuilder.CreateIndex(
                name: "IX_Licitacoes_UtilizadorUsername",
                table: "Licitacoes",
                column: "UtilizadorUsername");
        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "Licitacoes");
        }
    }
}
