using System;
using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace BirdBoxFull.Server.Migrations
{
    public partial class DecimaTerceira : Migration
    {
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropColumn(
                name: "dataNascimento",
                table: "Utilizadores");
        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.AddColumn<DateTime>(
                name: "dataNascimento",
                table: "Utilizadores",
                type: "datetime2",
                nullable: false,
                defaultValue: new DateTime(1, 1, 1, 0, 0, 0, 0, DateTimeKind.Unspecified));
        }
    }
}
