//
// Created by nuno on 23-02-2024.
//

#include "cena.hpp"


Cena::Cena() = default;

Cena::Cena(std::tuple<int,int> janela,std::vector<float> position, std::vector<float> lookAt, std::vector<float> up,
           std::vector<float> projection, CinemaMode c) {

    _janela = janela;
    _camara.insert({"position",position});
    _camara.insert({"lookAt",lookAt});
    _camara.insert({"up",up});
    _camara.insert({"projection",projection});
    _cm = c;

}

std::vector<std::vector<Ponto>> Cena::getModelos() {
    return _modelos;
}

std::vector<std::vector<float>> Cena::getModelosf() {
    return _modelosf;
}

void Cena::addModelo(std::vector<Ponto> f) {
    _modelos.push_back(f);
}

void Cena::addModelof(std::vector<float> f) {
    _modelosf.push_back(f);
}

std::tuple<int,int> Cena::getJanela(){
    return _janela;
}

std::map<std::string, std::vector<float>> Cena::getCamara() {
    return _camara;
}

void Cena::addLight(Light l){
    _luz.push_back(l);
}

void Cena::addRaiz(Node& node){

    _raizes.push_back(node);

}
std::vector<Node> Cena::getRaizes(){

    return _raizes;
}
int Cena::getTotalModels(const Node& node) {
    int total = node.modelsf.size(); // Count models in the current node

    // Traverse children recursively and sum up the models
    for (const Node& child : node.children) {
        total += getTotalModels(child);
    }

    return total;
}

int Cena::getTotalModelsInTree() {
    int t = 0;
    for (int i = 0; i < _raizes.size();++i){
        t+=getTotalModels(_raizes[i]);
    }
    return t;
}

CinemaMode Cena::getCinemaMode() {
    return _cm;
}

std::vector<Light> Cena::getLuz() {
    return _luz;
}





