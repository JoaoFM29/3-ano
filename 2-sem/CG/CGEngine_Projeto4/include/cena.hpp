#ifndef CENA_HPP
#define CENA_HPP

#include <map>
#include <string>
#include <vector>
#include "ponto.hpp"
#include "algebra.hpp"

struct Animation{

    float time;
    char type; //t translação e r rotação
    bool align;
    std::vector<Ponto> points;
    float y[3];
    std::vector<Ponto> points_look;


};
struct CinemaMode{

    std::vector<Ponto> points;
    float lookAt[3];
    int time;

};

struct Light{

    char tipo;
    float pos[3];
    float dir[3];
    float cutoff;

};

struct Color{

    float difuse[3];
    float ambient[3];
    float specular[3];
    float emissive[3];
    float shininess;

};


struct Node {
    std::vector<Matrix4x4> matrices; // List of matrices
    //std::vector<std::vector<Ponto> > models;
    std::vector<std::vector<float> > modelsf;
    std::vector<std::vector<float> > normalsf;
    std::vector<std::vector<float> > modelst;
    std::vector<std::string> texVector;
    std::vector<Color> colors;
    std::vector<Node> children;
    std::vector<Animation> animations;
    std::vector<char> indices; // indices das transformações e animações
};

struct Vertex {
    float x, y, z;
};

class Cena{

public:

    Cena();

    Cena(std::tuple<int,int> janela,std::vector<float> position, std::vector<float> lookAt,
         std::vector<float> up,std::vector<float> projection, CinemaMode c);

    void addModelo(std::vector<Ponto> f);

    void addModelof(std::vector<float> f);

    std::vector<std::vector<Ponto>> getModelos();

    std::vector<std::vector<float>> getModelosf();

    std::tuple<int, int> getJanela();

    std::map<std::string,std::vector<float>> getCamara();

    std::vector<Light>  getLuz();

    void addRaiz(Node &node);

    std::vector<Node> getRaizes();

    int getTotalModels(const Node& node);

    int getTotalModelsInTree();

    CinemaMode getCinemaMode();

    void addLight(Light l);

private:

    std::map<std::string,std::vector<float>> _camara;
    std::vector<Light> _luz;
    std::vector<std::vector<Ponto>> _modelos; // muito provavelmente vamos ter de mudar isto
    std::vector<std::vector<float>> _modelosf; // muito provavelmente vamos ter de mudar isto
    std::tuple<int,int> _janela;
    std::vector<Node> _raizes;
    CinemaMode _cm;



};
#endif // CENA_HPP
