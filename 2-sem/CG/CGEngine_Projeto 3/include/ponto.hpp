// ponto.hpp

#include <string>
#include <vector>

#ifndef PONTO_HPP
#define PONTO_HPP



class Ponto {
    
public:
    // Constructor
    Ponto();

    Ponto(double x, double y, double z);

    Ponto(const std::string& pointString);

    // Getter methods
    double getX();
    double getY();
    double getZ();

    // Setter methods
    void setX(double x);
    void setY(double y);
    void setZ(double z);

    std::string toString();

    Ponto translacao(double x, double y, double z);

    Ponto crossProduct(const Ponto& other);

    Ponto normalize();

    Ponto invert();

    Ponto slope(double angle);

    double dotProduct(Ponto& other);

    std::vector<float> toVector();




private:
    double x_;
    double y_;
    double z_;


};

#endif // PONTO_HPP
