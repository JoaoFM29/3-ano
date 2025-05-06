using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace BirdBoxFull.Server.Migrations
{
    public partial class Third : Migration
    {
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.CreateTable(
                name: "LeilaoImages",
                columns: table => new
                {
                    ImageId = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    ImageUrl = table.Column<string>(type: "nvarchar(max)", nullable: false),
                    LeilaoCodLeilao = table.Column<string>(type: "nvarchar(450)", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_LeilaoImages", x => x.ImageId);
                    table.ForeignKey(
                        name: "FK_LeilaoImages_Leiloes_LeilaoCodLeilao",
                        column: x => x.LeilaoCodLeilao,
                        principalTable: "Leiloes",
                        principalColumn: "CodLeilao",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateIndex(
                name: "IX_LeilaoImages_LeilaoCodLeilao",
                table: "LeilaoImages",
                column: "LeilaoCodLeilao");
        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "LeilaoImages");
        }
    }
}
