//
// Created by nuno on 20-02-2024.
//

#include <vector>
#include "ponto.hpp"
#include "draw.hpp"

std::vector<std::vector<Ponto>> drawBox(double length, double division) {

    std::vector<Ponto> solido;
    std::vector<Ponto> normais;
    std::vector<Ponto> textura;

    double step = length / division; // calcular o salto

    //base tampa
    //base tampa
    for (int i = 0; i < division; ++i) { // x
        for (int j = 0; j < division; ++j) { // z

            double x = -length / 2.0 + i * step; // não esquecer que está centrado na origem
            double z = -length / 2.0 + j * step; // não esquecer que está centrado na origem

            double y = -length / 2.0;

            // Calculate texture coordinates based on normalized position
            double u0 = (double)i / division;
            double v0 = (double)j / division;
            double u1 = (double)(i + 1) / division;
            double v1 = (double)(j + 1) / division;

            solido.push_back(Ponto(x + step, y, z + step)); // canto superipr esquerdo
            solido.push_back(Ponto(x, y, z + step)); // canto superipr esquerdo
            solido.push_back(Ponto(x, y, z)); // canto inferior esquerdo

            normais.push_back(Ponto(0,-1,0));
            normais.push_back(Ponto(0,-1,0));
            normais.push_back(Ponto(0,-1,0));

            textura.push_back(Ponto(u1, v1, 0));
            textura.push_back(Ponto(u0, v1, 0));
            textura.push_back(Ponto(u0, v0, 0));

            solido.push_back(Ponto(x + step, y, z + step)); // canto superipr esquerdo
            solido.push_back(Ponto(x, y, z)); // canto inferior esquerdo
            solido.push_back(Ponto(x + step, y, z)); // canto inferior esquerdo

            normais.push_back(Ponto(0,-1,0));
            normais.push_back(Ponto(0,-1,0));
            normais.push_back(Ponto(0,-1,0));

            textura.push_back(Ponto(u1, v1, 0));
            textura.push_back(Ponto(u0, v0, 0));
            textura.push_back(Ponto(u1, v0, 0));


            y = y * -1;

            solido.push_back(Ponto(x, y, z)); // canto inferior esquerdo
            solido.push_back(Ponto(x, y, z + step)); // canto inferior direito
            solido.push_back(Ponto(x + step, y, z + step)); // canto superipr esquerdo

            normais.push_back(Ponto(0,1,0));
            normais.push_back(Ponto(0,1,0));
            normais.push_back(Ponto(0,1,0));

            textura.push_back(Ponto(u0, v0, 0));
            textura.push_back(Ponto(u0, v1, 0));
            textura.push_back(Ponto(u1, v1, 0));


            solido.push_back(Ponto(x, y, z)); // canto inferior direito
            solido.push_back(Ponto(x + step, y, z + step)); // canto superior direito
            solido.push_back(Ponto(x + step, y, z)); // canto superior esquerdo

            normais.push_back(Ponto(0,1,0));
            normais.push_back(Ponto(0,1,0));
            normais.push_back(Ponto(0,1,0));

            textura.push_back(Ponto(u0, v0, 0));
            textura.push_back(Ponto(u1, v1, 0));
            textura.push_back(Ponto(u1, v0, 0));
        }
    }

    // frente traś
    for (int i = 0; i < division; ++i) { // x = -length / 2 e x = +length / 2
        for (int j = 0; j < division; ++j) {

            double y2 = -length / 2.0 + i * step; // não esquecer que está centrado na origem
            double z2 = -length / 2.0 + j * step; // não esquecer que está centrado na origem

            double x2 = -length / 2; // trás

            // Calculate texture coordinates based on normalized position
            double u0 = (double)i / division;
            double v0 = (double)j / division;
            double u1 = (double)(i + 1) / division;
            double v1 = (double)(j + 1) / division;

            solido.push_back(Ponto(x2, y2 + step, z2 + step));
            solido.push_back(Ponto(x2 , y2 + step, z2));
            solido.push_back(Ponto(x2, y2, z2));

            solido.push_back(Ponto(x2, y2 + step, z2 + step));
            solido.push_back(Ponto(x2, y2, z2));
            solido.push_back(Ponto(x2 , y2, z2  + step ));

            textura.push_back(Ponto(u1, v1, 0));
            textura.push_back(Ponto(u0, v1, 0));
            textura.push_back(Ponto(u0, v0, 0));

            textura.push_back(Ponto(u1, v1, 0));
            textura.push_back(Ponto(u0, v0, 0));
            textura.push_back(Ponto(u1, v0, 0));

            normais.push_back(Ponto(-1,0,0));
            normais.push_back(Ponto(-1,0,0));
            normais.push_back(Ponto(-1,0,0));

            normais.push_back(Ponto(-1,0,0));
            normais.push_back(Ponto(-1,0,0));
            normais.push_back(Ponto(-1,0,0));


            x2 = x2 * -1; // frente

            solido.push_back(Ponto(x2, y2, z2));
            solido.push_back(Ponto(x2 , y2 + step, z2));
            solido.push_back(Ponto(x2, y2 + step, z2 + step));

            normais.push_back(Ponto(1,0,0));
            normais.push_back(Ponto(1,0,0));
            normais.push_back(Ponto(1,0,0));

            textura.push_back(Ponto(u0, v0, 0));
            textura.push_back(Ponto(u1, v0, 0));
            textura.push_back(Ponto(u1, v1, 0));

            solido.push_back(Ponto(x2, y2, z2));
            solido.push_back(Ponto(x2, y2 + step, z2 + step));
            solido.push_back(Ponto(x2 , y2, z2  + step ));

            textura.push_back(Ponto(u0, v0, 0));
            textura.push_back(Ponto(u1, v1, 0));
            textura.push_back(Ponto(u0, v1, 0));

            normais.push_back(Ponto(1,0,0));
            normais.push_back(Ponto(1,0,0));
            normais.push_back(Ponto(1,0,0));
        }
    }

    // esquerda direita
    for (int i = 0; i < division; ++i) { // x = -length / 2 e x = +length / 2
        for (int j = 0; j < division; ++j) {

            double x3 = -length / 2.0 + i * step; // não esquecer que está centrado na origem
            double y3 = -length / 2.0 + j * step; // não esquecer que está centrado na origem

            double z3 = -length / 2; // base


            double u0 = (double)i / division;
            double v0 = (double)j / division;
            double u1 = (double)(i + 1) / division;
            double v1 = (double)(j + 1) / division;

            solido.push_back(Ponto(x3 + step , y3 + step, z3)); // canto superipor esquerdo
            solido.push_back(Ponto(x3 + step , y3, z3)); // canto superipor esquerdo
            solido.push_back(Ponto(x3 , y3, z3)); // canto superipor esquerdo

            normais.push_back(Ponto(0,0,-1));
            normais.push_back(Ponto(0,0,-1));
            normais.push_back(Ponto(0,0,-1));

            textura.push_back(Ponto(u1, v1, 0));
            textura.push_back(Ponto(u1, v0, 0));
            textura.push_back(Ponto(u0, v0, 0));

            solido.push_back(Ponto(x3 + step , y3 + step, z3)); // canto superipor esquerdo
            solido.push_back(Ponto(x3 , y3, z3)); // canto superipor esquerdo
            solido.push_back(Ponto(x3 , y3 + step, z3)); // canto superipor esquerdo

            textura.push_back(Ponto(u1, v1, 0));
            textura.push_back(Ponto(u0, v0, 0));
            textura.push_back(Ponto(u0, v1, 0));

            normais.push_back(Ponto(0,0,-1));
            normais.push_back(Ponto(0,0,-1));
            normais.push_back(Ponto(0,0,-1));

            z3 = z3 * -1; // tampa

            solido.push_back(Ponto(x3, y3, z3)); // canto inferior esquerdo
            solido.push_back(Ponto(x3 + step, y3, z3)); // canto inferior direito
            solido.push_back(Ponto(x3 + step , y3 + step, z3)); // canto superipor esquerdo

            normais.push_back(Ponto(0,0,1));
            normais.push_back(Ponto(0,0,1));
            normais.push_back(Ponto(0,0,1));

            textura.push_back(Ponto(u0, v0, 0));
            textura.push_back(Ponto(u1, v0, 0));
            textura.push_back(Ponto(u1, v1, 0));

            solido.push_back(Ponto(x3, y3, z3)); // canto inferior direito
            solido.push_back(Ponto(x3 + step , y3 + step, z3)); // canto superipor esquerdo
            solido.push_back(Ponto(x3, y3  + step, z3)); // canto inferior direito

            textura.push_back(Ponto(u0, v0, 0));
            textura.push_back(Ponto(u1, v1, 0));
            textura.push_back(Ponto(u0, v1, 0));

            normais.push_back(Ponto(0,0,1));
            normais.push_back(Ponto(0,0,1));
            normais.push_back(Ponto(0,0,1));
        }
    }

    std::vector<std::vector<Ponto>> ret;
    ret.push_back(solido);ret.push_back(normais);ret.push_back(textura);
    return ret;
}
