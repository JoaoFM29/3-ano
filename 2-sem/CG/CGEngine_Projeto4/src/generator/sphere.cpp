#include <cmath>
#include <vector>
#include "ponto.hpp"
#include "draw.hpp"

std::vector<std::vector<Ponto>> drawSphere(double radius, int slices, int stacks) {

    std::vector<Ponto> solido;
    std::vector<Ponto> normais;
    std::vector<Ponto> texture; // Vector for 2D texture points
    double sliceStep = 2.0 * M_PI / slices;
    double stackStep = M_PI / stacks;

    double alfa = 0;
    double beta = -M_PI/2;

    for( int i = 0; i < stacks ; ++i){
        alfa = 0;
        for (int j = 0; j < slices; ++j){

            Ponto ponto1 = Ponto(radius * sinf(alfa) * cosf(beta),radius * sinf(beta),radius * cosf(alfa) * cosf(beta));
            Ponto ponto2 = Ponto(radius * sinf(alfa + sliceStep) * cosf(beta),radius * sinf(beta),radius * cosf(alfa + sliceStep) * cosf(beta));
            Ponto ponto3 = Ponto(radius * sinf(alfa + sliceStep) * cosf(beta + stackStep),radius * sinf(beta + stackStep),radius * cosf(alfa + sliceStep) * cosf(beta + stackStep));
            Ponto ponto4 = Ponto(radius * sinf(alfa) * cosf(beta+stackStep),radius * sinf(beta + stackStep),radius * cosf(alfa) * cosf(beta + stackStep));


            Ponto texCoord1 = Ponto(static_cast<float>(j) / static_cast<float>(slices), static_cast<float>(i) / static_cast<float>(stacks), 0);
            Ponto texCoord2 = Ponto(static_cast<float>(j+1) / static_cast<float>(slices), static_cast<float>(i) / static_cast<float>(stacks), 0);
            Ponto texCoord3 = Ponto(static_cast<float>(j+1) / static_cast<float>(slices), static_cast<float>(i+1) / static_cast<float>(stacks), 0);
            Ponto texCoord4 = Ponto(static_cast<float>(j) / static_cast<float>(slices), static_cast<float>(i+1) / static_cast<float>(stacks), 0);


            // primeiro triangulo
            solido.push_back(ponto2);
            solido.push_back(ponto3);
            solido.push_back(ponto4);

            texture.push_back(texCoord2);
            texture.push_back(texCoord3);
            texture.push_back(texCoord4);

            normais.push_back(Ponto(sinf(alfa + sliceStep) * cosf(beta),sinf(beta),cosf(alfa + sliceStep) * cosf(beta)));
            normais.push_back(Ponto(sinf(alfa + sliceStep) * cosf(beta + stackStep) ,sinf(beta + stackStep),cosf(alfa + sliceStep) * cosf(beta + stackStep)));
            normais.push_back(Ponto(sinf(alfa) * cosf(beta+stackStep),sinf(beta + stackStep),cosf(alfa) * cosf(beta + stackStep)));

            // segundo triangulo
            solido.push_back(ponto4);
            solido.push_back(ponto1);
            solido.push_back(ponto2);

            texture.push_back(texCoord4);
            texture.push_back(texCoord1);
            texture.push_back(texCoord2);

            normais.push_back(Ponto(sinf(alfa) * cosf(beta+stackStep),sinf(beta + stackStep),cosf(alfa) * cosf(beta + stackStep)));
            normais.push_back(Ponto(sinf(alfa) * cosf(beta),sinf(beta),cosf(alfa) * cosf(beta)));
            normais.push_back(Ponto(sinf(alfa + sliceStep) * cosf(beta),sinf(beta),cosf(alfa + sliceStep) * cosf(beta)));

            alfa += sliceStep;
        }
        beta += stackStep;
    }
    std::vector<std::vector<Ponto>> res;
    res.push_back(solido);
    res.push_back(normais);
    res.push_back(texture); // Add texture vector to the result
    return res;
}
