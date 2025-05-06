//
// Created by nuno on 20-02-2024.
//
// ponto.cpp

#include <sstream>
#include <cmath>
#include "ponto.hpp"
using namespace std;

// Constructor

Ponto::Ponto() {
    x_ = 0;
    y_ = 0;
    z_ = 0;
}

Ponto::Ponto(double x, double y, double z) {
    x_ = x;
    y_ = y;
    z_ = z;
}
Ponto::Ponto(const std::string& pointString) {
    std::stringstream ss(pointString);
    std::string token;

    getline(ss, token, ',');
    x_ = std::stod(token);

    getline(ss, token, ',');
    y_ = std::stod(token);

    getline(ss, token, ',');
    z_ = std::stod(token);
}
// Getter methods
double Ponto::getX(){
    return x_;
}

double Ponto::getY(){
    return y_;
}

double Ponto::getZ(){
    return z_;
}

// Setter methods
void Ponto::setX(double x) {
    x_ = x;
}

void Ponto::setY(double y) {
    y_ = y;
}

void Ponto::setZ(double z) {
    z_ = z;
}

Ponto Ponto::translacao(double x, double y, double z){

    return Ponto(x_+x,y_+y,z_+z);

}

Ponto Ponto::invert(){

    return Ponto(-x_,-y_,-z_);

}

double Ponto::dotProduct(Ponto& other) {
    return x_ * other.x_ + y_ * other.y_ + z_ * other.z_;
}


std::string Ponto::toString() {
    return std::to_string(x_) + ',' + std::to_string(y_) + ',' + std::to_string(z_);
}

std::vector<float> Ponto::toVector() {
    std::vector<float> p;
    p.push_back(static_cast<float>(x_));
    p.push_back(static_cast<float>(y_));
    p.push_back(static_cast<float>(z_));
    return p;
}

Ponto Ponto::crossProduct(const Ponto& other) {
    double newX = y_ * other.z_ - z_ * other.y_;
    double newY = z_ * other.x_ - x_ * other.z_;
    double newZ = x_ * other.y_ - y_ * other.x_;
    return Ponto(newX, newY, newZ);
}

// Normalize method
Ponto Ponto::normalize(){
    double length = sqrt(x_ * x_ + y_ * y_ + z_ * z_);

    if (length == 0) {
        return Ponto(0, 0, 0); // Avoid division by zero
    }

    double newX = x_ / length;
    double newY = y_ / length;
    double newZ = z_ / length;

    return Ponto(newX, newY, newZ);
}

Ponto Ponto::slope(double angle) {
    // Calculate distance from the origin (0,0,0)
    double distance = sqrt(x_ * x_ + y_ * y_ + z_ * z_);

    // Calculate height using trigonometry
    double height = distance * tan(angle);

    // Calculate new z-coordinate
    double newZ = z_ + height;

    // Return new point with updated z-coordinate
    return Ponto(x_, y_, newZ);
}


