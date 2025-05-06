//
// Created by nuno on 20-02-2024.
//
#include <vector>
#include "ponto.hpp"
#include "draw.hpp"

std::vector<std::vector<Ponto>> drawPlane(double length, double division) {
    std::vector<Ponto> solido;
    std::vector<Ponto> normais;
    std::vector<Ponto> textura;

    double step = length / division; // calcular o salto

    for (int i = 0; i < division; ++i) { // x
        for (int j = 0; j < division; ++j) { // z

            double x = -length / 2.0 + i * step; // não esquecer que está centrado na origem
            double z = -length / 2.0 + j * step; // não esquecer que está centrado na origem

            double y = 0;

            solido.push_back(Ponto(x, y, z)); // canto inferior esquerdo
            solido.push_back(Ponto(x, y, z + step)); // canto inferior direito
            solido.push_back(Ponto(x+step, y, z + step)); // canto superipr esquerdo

            normais.push_back(Ponto(0,1,0));
            normais.push_back(Ponto(0,1,0));
            normais.push_back(Ponto(0,1,0));

            textura.push_back(Ponto(0,1,0));
            textura.push_back(Ponto(1,1,0));
            textura.push_back(Ponto(1,0,0));


            solido.push_back(Ponto(x, y, z)); // canto inferior direito
            solido.push_back(Ponto(x + step, y, z + step)); // canto superior direito
            solido.push_back(Ponto(x + step, y, z)); // canto superior esquerdo

            normais.push_back(Ponto(0,1,0));
            normais.push_back(Ponto(0,1,0));
            normais.push_back(Ponto(0,1,0));

            textura.push_back(Ponto(0,1,0));
            textura.push_back(Ponto(1,0,0));
            textura.push_back(Ponto(0,0,0));

            solido.push_back(Ponto(x+step, y, z + step)); // canto superipr esquerdo
            solido.push_back(Ponto(x, y, z + step)); // canto inferior direito
            solido.push_back(Ponto(x, y, z)); // canto inferior esquerdo

            normais.push_back(Ponto(0,-1,0));
            normais.push_back(Ponto(0,-1,0));
            normais.push_back(Ponto(0,-1,0));

            textura.push_back(Ponto(1,0,0));
            textura.push_back(Ponto(1,1,0));
            textura.push_back(Ponto(0,1,0));

            solido.push_back(Ponto(x + step, y, z)); // canto superior esquerdo
            solido.push_back(Ponto(x + step, y, z + step)); // canto superior direito
            solido.push_back(Ponto(x, y, z)); // canto inferior direito

            normais.push_back(Ponto(0,-1,0));
            normais.push_back(Ponto(0,-1,0));
            normais.push_back(Ponto(0,-1,0));

            textura.push_back(Ponto(0,0,0));
            textura.push_back(Ponto(1,0,0));
            textura.push_back(Ponto(0,1,0));


        }
    }

    std::vector<std::vector<Ponto>> ret;
    ret.push_back(solido);ret.push_back(normais);ret.push_back(textura);

    return ret;
}

