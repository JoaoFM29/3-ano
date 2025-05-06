//
// Created by nuno on 27-02-2024.
//

#include <cmath>
#include <vector>
#include "ponto.hpp"
#include "draw.hpp"

std::vector<std::vector<Ponto>>drawCone(double radius,double height,int slices, int stacks){

    std::vector<Ponto> solido;
    std::vector<Ponto> normais;
    std::vector<Ponto> texture; // Vector for 2D texture points
    double sliceStep = 2.0 * M_PI / slices;
    double alfa = 0;

    for ( int i = 0; i < slices; ++i){

        // z = radius * cosf(alfa)
        // x = radius * sinf(alfa)
        Ponto pb1 = Ponto(0,0,0); // raiz
        Ponto pb2 = Ponto(radius * sinf(alfa),0, radius * cosf(alfa));//
        Ponto pb3 = Ponto(radius * sinf(alfa + sliceStep),0, radius * cosf(alfa + sliceStep));//


        solido.push_back(pb1);
        solido.push_back(pb3);
        solido.push_back(pb2);

        normais.push_back(Ponto(0,-1,0));
        normais.push_back(Ponto(0,-1,0));
        normais.push_back(Ponto(0,-1,0));

        texture.push_back(Ponto(0.5, 0.5, 0)); // Base center
        texture.push_back(Ponto(0.5 + 0.5 * sinf(alfa), 0.5 + 0.5 * cosf(alfa), 0));
        texture.push_back(Ponto(0.5 + 0.5 * sinf(alfa + sliceStep), 0.5 + 0.5 * cosf(alfa + sliceStep), 0));

        alfa += sliceStep;
    }

    double stackStep = height / stacks;
    double current_height = 0;
    double textH = 1.0f / slices;
    double textV = 1.0f / stacks;


    for (int i = 0; i< stacks; ++i){

        alfa = 0;
        double topRadius = (height - current_height - stackStep) / (height / radius);
        double bottomRadius = (height  - current_height) / (height  / radius);
        double ny = radius/height;


        for (int j = 0; j < slices; ++j){
            Ponto pl1 = Ponto(bottomRadius * sinf(alfa),current_height,bottomRadius * cosf(alfa)); // raiz
            Ponto pl2 = Ponto(bottomRadius * sinf(alfa+sliceStep),current_height,bottomRadius * cosf(alfa + sliceStep));
            Ponto pl3 = Ponto(topRadius * sinf(alfa),current_height + stackStep, topRadius * cosf(alfa));//
            Ponto pl4 = Ponto(topRadius * sinf(alfa+sliceStep),current_height + stackStep, topRadius * cosf(alfa + sliceStep));//

            Ponto tex1 = Ponto(j * textH, ((i)) * textV, 0);
            Ponto tex2 = Ponto((j + 1) * textH, ((i)) * textV, 0);
            Ponto tex3 = Ponto(j * textH, (i+1) * textV, 0);
            Ponto tex4 = Ponto((j + 1) * textH, (i+1) * textV, 0);



            //triangulo 1
            Ponto t1 = pl4.translacao(-(bottomRadius * sinf(alfa+sliceStep)),-(current_height),-bottomRadius * cosf(alfa + sliceStep));
            Ponto t2 = pl3.translacao(-(topRadius * sinf(alfa+sliceStep)),-(current_height + stackStep),-(topRadius * cosf(alfa + sliceStep)));
            Ponto nt1temp = t1.crossProduct(t2);
            Ponto nt1 = nt1temp.normalize();
            solido.push_back(pl2);
            solido.push_back(pl4);
            solido.push_back(pl3);

            normais.push_back(Ponto(sinf(alfa+sliceStep),ny,cosf(alfa + sliceStep)).normalize());
            normais.push_back(Ponto(sinf(alfa+sliceStep),ny,cosf(alfa + sliceStep)).normalize());
            normais.push_back(Ponto(sinf(alfa),ny,cosf(alfa)).normalize());

            texture.push_back(tex2);
            texture.push_back(tex4);
            texture.push_back(tex3);
            //triangulo 2
            Ponto t12 = pl1.translacao(topRadius * sinf(alfa) * -1,-(current_height + stackStep), -(topRadius * cosf(alfa)));
            Ponto t22 = pl2.translacao(bottomRadius * sinf(alfa) * -1,-(current_height),-(bottomRadius * cosf(alfa)));
            Ponto nt12temp = t12.crossProduct(t22);
            Ponto nt12 = nt12temp.normalize();
            solido.push_back(pl3);
            solido.push_back(pl1);
            solido.push_back(pl2);

            normais.push_back(Ponto(sinf(alfa),ny,cosf(alfa)).normalize());
            normais.push_back(Ponto(sinf(alfa),ny,cosf(alfa)).normalize());
            normais.push_back(Ponto(sinf(alfa+sliceStep),ny,cosf(alfa + sliceStep)).normalize());

            texture.push_back(tex3);
            texture.push_back(tex1);
            texture.push_back(tex2);

            alfa += sliceStep;
        }
        current_height += stackStep;
    }

    std::vector<std::vector<Ponto>> res;
    res.push_back(solido);res.push_back(normais);res.push_back(texture);
    return res;

}