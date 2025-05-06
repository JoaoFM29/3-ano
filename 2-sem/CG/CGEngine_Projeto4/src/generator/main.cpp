#include <iostream>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cstring>
#include <vector>
#include <fstream>
#include "ponto.hpp"
#include "draw.hpp"
using namespace std;

void writeToFile(std::vector<std::vector<Ponto>> pontos, std::string filename) {

    std::vector<Ponto> solido = pontos[0];
    std::vector<Ponto> normais = pontos[1];
    std::vector<Ponto> textures = pontos[2];

    filename = "../generated/" + filename;

    std::ofstream file(filename);

    // Check if file is opened successfully
    if (!file.is_open()) {
        std::cerr << "Error: Failed to open file " << filename << std::endl;
        return;
    }

    file << solido.size() << std::endl;

    for ( Ponto ponto : solido) {

        //std::cout << ponto.toString() << std::endl;
        file << ponto.toString() << std::endl;
    }

    file << normais.size() << std::endl;

    for ( Ponto ponto : normais) {
        //std::cout << ponto.toString() << std::endl;
        file << ponto.toString() << std::endl;
    }

    file << textures.size() << std::endl;

    for ( Ponto ponto : textures) {
        //std::cout << ponto.toString() << std::endl;
        file << ponto.toString() << std::endl;
    }

    file.close();
}
int main(int argc,char**argv) {

    if (strcmp(argv[1],"plane") == 0)
        writeToFile(drawPlane(stod(argv[2]), stod(argv[3])),argv[4]);
    else if (strcmp(argv[1],"box") == 0)
        writeToFile(drawBox(stod(argv[2]), stod(argv[3])),argv[4]);
    else if (strcmp(argv[1],"sphere") == 0)
        writeToFile(drawSphere(stod(argv[2]), stoi(argv[3]),stoi(argv[4])),argv[5]);
    else if (strcmp(argv[1],"ring") == 0)
        writeToFile(drawRing(stod(argv[2]), stoi(argv[3]),stoi(argv[4])),argv[5]);
    else if (strcmp(argv[1],"cone") == 0)
        writeToFile(drawCone(stod(argv[2]), stod(argv[3]),stoi(argv[4]),stoi(argv[5])),argv[6]);
    else if (strcmp(argv[1],"patch") == 0)
        writeToFile(drawBezier(argv[2],stoi(argv[3])),argv[4]);
    else
    cout <<"Argumentos inválidos"<<'\n';

  return 0;
}
