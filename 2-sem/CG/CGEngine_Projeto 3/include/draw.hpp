#include <vector>
#include "ponto.hpp"

std::vector<std::vector<Ponto>> drawPlane(double length,double division); // desenhar os planos
std::vector<std::vector<Ponto>> drawBox(double length,double division); // desenhar as caixas
std::vector<std::vector<Ponto>> drawSphere(double radius, int slices, int stacks);
std::vector<std::vector<Ponto>> drawCone(double radius,double height,int slices, int stacks);
std::vector<std::vector<Ponto>> drawRing(double radiusSmall, double radiusBig, int slices);
std::vector<std::vector<Ponto>> drawBezier(const std::string& path, int tesselation);