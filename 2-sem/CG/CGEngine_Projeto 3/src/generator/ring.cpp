#include <cmath>
#include <vector>
#include "ponto.hpp"
#include "draw.hpp"

std::vector<std::vector<Ponto>> drawRing(double radiusSmall, double radiusBig, int slices) {
    std::vector<Ponto> solido;
    std::vector<Ponto> normais;
    std::vector<Ponto> tex;
    double sliceStep = 2.0 * M_PI / slices;
    double alfa = 0;
    double texCoordStep = 1.0 / slices; // Step size for texture coordinates along the width

    for (int i = 0; i < slices; ++i) {
        // Calculate texture coordinates along the width of the rectangle
        double texCoordLeft = i * texCoordStep;
        double texCoordRight = (i + 1) * texCoordStep;

        Ponto p1 = Ponto(radiusSmall * sinf(alfa), 0, radiusSmall * cosf(alfa));
        Ponto p2 = Ponto(radiusBig * sinf(alfa), 0, radiusBig * cosf(alfa));
        Ponto p3 = Ponto(radiusSmall * sinf(alfa + sliceStep), 0, radiusSmall * cosf(alfa + sliceStep));
        Ponto p4 = Ponto(radiusBig * sinf(alfa + sliceStep), 0, radiusBig * cosf(alfa + sliceStep));

        solido.push_back(p1);
        solido.push_back(p2);
        solido.push_back(p4);

        normais.push_back(Ponto(0, 1, 0));
        normais.push_back(Ponto(0, 1, 0));
        normais.push_back(Ponto(0, 1, 0));

        // Assign texture coordinates
        tex.push_back(Ponto(texCoordLeft, 0, 0));
        tex.push_back(Ponto(texCoordLeft, 1, 0));
        tex.push_back(Ponto(texCoordRight, 1, 0));

        solido.push_back(p4);
        solido.push_back(p3);
        solido.push_back(p1);

        normais.push_back(Ponto(0, 1, 0));
        normais.push_back(Ponto(0, 1, 0));
        normais.push_back(Ponto(0, 1, 0));

        // Assign texture coordinates
        tex.push_back(Ponto(texCoordRight, 1, 0));
        tex.push_back(Ponto(texCoordRight, 0, 0));
        tex.push_back(Ponto(texCoordLeft, 0, 0));

        solido.push_back(p4);
        solido.push_back(p2);
        solido.push_back(p1);

        normais.push_back(Ponto(0, -1, 0));
        normais.push_back(Ponto(0, -1, 0));
        normais.push_back(Ponto(0, -1, 0));

        // Assign texture coordinates
        tex.push_back(Ponto(texCoordRight, 0, 0));
        tex.push_back(Ponto(texCoordLeft, 0, 0));
        tex.push_back(Ponto(texCoordLeft, 1, 0));

        solido.push_back(p1);
        solido.push_back(p3);
        solido.push_back(p4);

        normais.push_back(Ponto(0, -1, 0));
        normais.push_back(Ponto(0, -1, 0));
        normais.push_back(Ponto(0, -1, 0));

        // Assign texture coordinates
        tex.push_back(Ponto(texCoordLeft, 1, 0));
        tex.push_back(Ponto(texCoordRight, 1, 0));
        tex.push_back(Ponto(texCoordRight, 0, 0));

        alfa += sliceStep;
    }
    std::vector<std::vector<Ponto>> res;
    res.push_back(solido);
    res.push_back(normais);
    res.push_back(tex);
    return res;
}
