//
// Created by nuno on 20-02-2024.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include "tinyxml2.h"
#include "ponto.hpp"
#include "cena.hpp"

using namespace std;



void printNode(const Node& node, int level = 0) {
    // Print matrices
    std::cout << "Matrix:" << std::endl;
    for (const auto& matrix : node.matrices) {
        printMatrix(matrix);
    }
    // Print models
    std::cout << "Modelos: "<<node.modelsf.size() << std::endl;
    std::cout << "Filhos: "<<node.children.size() << std::endl;

    // Print child nodes
    for (const auto& child : node.children) {
        for (int i = 0; i < level; ++i) {
            std::cout << "  ";
        }
        std::cout << "Child Node:" << std::endl;
        printNode(child, level + 1);
    }
}

std::vector<Ponto> load3dObject(const std::string& path) {
    std::vector<Ponto> pontos;

    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir ficheiro " << path << std::endl;
        return pontos; // Return empty vector if file cannot be opened
    }

    std::string line;
    std::getline(file, line); // Read the first line containing the number of points
    int numPoints = std::stoi(line);

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;
        double x, y, z;

        // Tokenize the line using comma as delimiter
        if (std::getline(iss, token, ',') && std::istringstream(token) >> x &&
            std::getline(iss, token, ',') && std::istringstream(token) >> y &&
            std::getline(iss, token, ',') && std::istringstream(token) >> z) {
            pontos.emplace_back(x, y, z);
        } else {
            std::cerr << "Error: Invalid line format: " << line << std::endl;
            continue; // Skip invalid lines
        }
    }
    // Check if the number of points read matches the expected number
    if (pontos.size() != numPoints) {
        std::cerr << "Warning: Number of points read does not match the expected number." << std::endl;
    }

    file.close();
    return pontos;
}

std::vector<float> load3dObjectf(const std::string& path) {
    std::vector<float> pontos;

    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir ficheiro " << path << std::endl;
        return pontos; // Return empty vector if file cannot be opened
    }

    std::string line;
    std::getline(file, line); // Read the first line containing the number of points
    int numPoints = std::stoi(line);

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;
        float x, y, z;

        // Tokenize the line using comma as delimiter
        if (std::getline(iss, token, ',') && std::istringstream(token) >> x &&
            std::getline(iss, token, ',') && std::istringstream(token) >> y &&
            std::getline(iss, token, ',') && std::istringstream(token) >> z) {
            pontos.push_back(x);pontos.push_back(y);pontos.push_back(z);
        } else {
            std::cerr << "Error: Invalid line format: " << line << std::endl;
            continue; // Skip invalid lines
        }
    }
    // Check if the number of points read matches the expected number
    if (pontos.size()/3 != numPoints) {
        std::cerr << "Warning: Number of points read does not match the expected number." << std::endl;
    }

    file.close();
    return pontos;
}

std::tuple<std::vector<float>, std::vector<float>, std::vector<float>> load3dObjectfn(const std::string& path) {
    std::vector<float> pontos;
    std::vector<float> normals;
    std::vector<float> textures;

    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir ficheiro " << path << std::endl;
        return {pontos, normals,textures}; // Return empty vectors if file cannot be opened
    }

    std::string line;
    std::getline(file, line); // Read the first line containing the number of points
    int numPoints = std::stoi(line);

    // Read the first group of points
    for (int i = 0; i < numPoints; ++i) {
        std::getline(file, line);
        std::istringstream iss(line);
        std::string token;
        float x, y, z;

        // Tokenize the line using comma as delimiter
        if (std::getline(iss, token, ',') && std::istringstream(token) >> x &&
            std::getline(iss, token, ',') && std::istringstream(token) >> y &&
            std::getline(iss, token, ',') && std::istringstream(token) >> z) {
            pontos.push_back(x); pontos.push_back(y); pontos.push_back(z);
        } else {
            std::cerr << "Error: Invalid line format: " << line << std::endl;
        }
    }
    // Read the second group of points (normals)
    std::getline(file, line); // Read the first line containing the number of points

    int numPoints2 = std::stoi(line);
    for (int i = 0; i < numPoints2; ++i) {
        std::getline(file, line);
        std::istringstream iss(line);
        std::string token;
        float x, y, z;

        // Tokenize the line using comma as delimiter
        if (std::getline(iss, token, ',') && std::istringstream(token) >> x &&
            std::getline(iss, token, ',') && std::istringstream(token) >> y &&
            std::getline(iss, token, ',') && std::istringstream(token) >> z) {
            normals.push_back(x); normals.push_back(y); normals.push_back(z);
        } else {

            std::cerr << "Error: Invalid line format: " << line << std::endl;
        }
    }

    std::getline(file, line); // Read the first line containing the number of points
    int numPoints3 = std::stoi(line);

    for (int i = 0; i < numPoints3; ++i) {
        std::getline(file, line);
        std::istringstream iss(line);
        std::string token;
        float x, y, z;

        // Tokenize the line using comma as delimiter
        if (std::getline(iss, token, ',') && std::istringstream(token) >> x &&
            std::getline(iss, token, ',') && std::istringstream(token) >> y &&
            std::getline(iss, token, ',') && std::istringstream(token) >> z) {
            textures.push_back(x); textures.push_back(y);
        } else {

            std::cerr << "Error: Invalid line format: " << line << std::endl;
        }
    }

    file.close();
    return {pontos, normals,textures};
}

void parseTransform(tinyxml2::XMLElement* element, Node& node) {
    for (tinyxml2::XMLElement* transform = element->FirstChildElement(); transform; transform = transform->NextSiblingElement()) {
        float x,y,z,angle;
        const char* name = transform->Name();

        if (strcmp(name, "translate") == 0) {

            if (transform->Attribute("time")) {
                // The "time" attribute exists
                Animation a;
                transform->QueryFloatAttribute("time", &a.time);
                transform->QueryBoolAttribute("align",&a.align);
                a.type = 't';
                // Iterate through <point> elements inside <translate>
                for (tinyxml2::XMLElement* point = transform->FirstChildElement(); point; point = point->NextSiblingElement()) {
                    const char* pointName = point->Name();
                    if (strcmp(pointName, "point") == 0) {
                        float xa,ya,za;
                        point->QueryFloatAttribute("x", &xa);
                        point->QueryFloatAttribute("y", &ya);
                        point->QueryFloatAttribute("z", &za);
                        Ponto p = Ponto(xa,ya,za);
                        a.points.push_back(p);

                    }
                }

                a.y[0] = 0.0f;a.y[1] = 1.0f;a.y[2] = 0.0f;
                node.animations.push_back(a);
                node.indices.push_back('a');
            } // caso seja animação
            else{

                transform->QueryFloatAttribute("x", &x);
                transform->QueryFloatAttribute("y", &y);
                transform->QueryFloatAttribute("z", &z);
                Matrix4x4 m{};
                m.data[0][0] = 1;m.data[0][1] = 0;m.data[0][2] = 0;m.data[0][3] = x;
                m.data[1][0] = 0;m.data[1][1] = 1;m.data[1][2] = 0;m.data[1][3] = y;
                m.data[2][0] = 0;m.data[2][1] = 0;m.data[2][2] = 1;m.data[2][3] = z;
                m.data[3][0] = 0;m.data[3][1] = 0;m.data[3][2] = 0;m.data[3][3] = 1;
                node.matrices.push_back(m);
                node.indices.push_back('t');
                std::cout << "Transformation: "<<name<<" (" << x << ", " << y << ", " << z << ")" << std::endl;

            }

        }
        if (strcmp(name, "rotate") == 0) {

            if (transform->Attribute("time")){

                Animation a;
                transform->QueryFloatAttribute("time", &a.time);
                float xr,yr,zr;
                transform->QueryFloatAttribute("x", &xr);
                transform->QueryFloatAttribute("y", &yr);
                transform->QueryFloatAttribute("z", &zr);
                a.type = 'r';
                a.y[0] = xr;
                a.y[1] = yr;
                a.y[2] = zr;
                node.animations.push_back(a);
                node.indices.push_back('a');
                //cout

            }else{


            transform->QueryFloatAttribute("angle", &angle);
            transform->QueryFloatAttribute("x", &x);
            transform->QueryFloatAttribute("y", &y);
            transform->QueryFloatAttribute("z", &z);

            Matrix4x4 m{};
            float ang = angle * (M_PI / 180); // converter para radianos
            if (x == 1){

                m.data[0][0] = 1;m.data[0][1] = 0;m.data[0][2] = 0;m.data[0][3] = 0;
                m.data[1][0] = 0;m.data[1][1] = cosf(ang);m.data[1][2] = -sinf(ang);m.data[1][3] = 0;
                m.data[2][0] = 0;m.data[2][1] = sinf(ang);m.data[2][2] = cosf(ang);m.data[2][3] = 0;
                m.data[3][0] = 0;m.data[3][1] = 0;m.data[3][2] = 0;m.data[3][3] = 1;

            } else if(y == 1){
                m.data[0][0] = cosf(ang);m.data[0][1] = 0;m.data[0][2] = sinf(ang);m.data[0][3] = 0;
                m.data[1][0] = 0;m.data[1][1] = 1;m.data[1][2] = 0;m.data[1][3] = 0;
                m.data[2][0] = -sinf(ang);m.data[2][1] = 0;m.data[2][2] = cosf(ang);m.data[2][3] = 0;
                m.data[3][0] = 0;m.data[3][1] = 0;m.data[3][2] = 0;m.data[3][3] = 1;

            }else if(z==1){
                m.data[0][0] = cosf(ang);m.data[0][1] = -sinf(ang);m.data[0][2] =0;m.data[0][3] = 0;
                m.data[1][0] = sinf(ang);m.data[1][1] = cosf(ang);m.data[1][2] = 0;m.data[1][3] = 0;
                m.data[2][0] = 0;m.data[2][1] = 0;m.data[2][2] = 1;m.data[2][3] = 0;
                m.data[3][0] = 0;m.data[3][1] = 0;m.data[3][2] = 0;m.data[3][3] = 1;
            }

            node.matrices.push_back(m);
            node.indices.push_back('t');
            std::cout << "Transformation: "<<name<<" (" << x << ", " << y << ", " << z << ")" << std::endl;
            }
        } if (strcmp(name, "scale") == 0) {

            transform->QueryFloatAttribute("x", &x);
            transform->QueryFloatAttribute("y", &y);
            transform->QueryFloatAttribute("z", &z);
            Matrix4x4 m{};
            m.data[0][0] = x;m.data[0][1] = 0;m.data[0][2] = 0;m.data[0][3] = 0;
            m.data[1][0] = 0;m.data[1][1] = y;m.data[1][2] = 0;m.data[1][3] = 0;
            m.data[2][0] = 0;m.data[2][1] = 0;m.data[2][2] = z;m.data[2][3] = 0;
            m.data[3][0] = 0;m.data[3][1] = 0;m.data[3][2] = 0;m.data[3][3] = 1;
            node.matrices.push_back(m);
            node.indices.push_back('t');
            std::cout << "Transformation: "<<name<<" (" << x << ", " << y << ", " << z << ")" << std::endl;
        }

       // node.transformations.push_back(trans);
    }
}

void parseGroup(tinyxml2::XMLElement* element, Node& node) {
    // Parse transformations
    tinyxml2::XMLElement* transformElement = element->FirstChildElement("transform");
    if (transformElement) {
        parseTransform(transformElement, node);
    }

    // Parse models
    tinyxml2::XMLElement* modelsElement = element->FirstChildElement("models");
    if (modelsElement) {
        for (tinyxml2::XMLElement* model = modelsElement->FirstChildElement("model"); model; model = model->NextSiblingElement("model")) {
            const char* file = model->Attribute("file");
            if (file) {
                // Load the model using the provided file path
                std::string filename = "../generated/" + std::string(file);
                // Assuming you have a method to load 3D models from file

                //std::vector<Ponto> modelo = load3dObject(filename);

                std::tuple<std::vector<float>, std::vector<float>, std::vector<float>> r = load3dObjectfn(filename);
                std::vector<float> modelof,modelon,modelot;
                modelof = std::get<0>(r);
                modelon = std::get<1>(r);
                modelot = std::get<2>(r);
                Color c;


                tinyxml2::XMLElement* colorElement = model->FirstChildElement("color");
                if (colorElement) {
                    // Parse and assign values for diffuse
                    tinyxml2::XMLElement* diffuseElement = colorElement->FirstChildElement("diffuse");
                    if (diffuseElement) {
                        int r, g, b;
                        diffuseElement->QueryIntAttribute("R", &r);
                        diffuseElement->QueryIntAttribute("G", &g);
                        diffuseElement->QueryIntAttribute("B", &b);

                        c.difuse[0] = static_cast<float>(r) / 255.0f;
                        c.difuse[1] = static_cast<float>(g) / 255.0f;
                        c.difuse[2] = static_cast<float>(b) / 255.0f;
                    } else {
                        c.difuse[0] = 200.0f / 255.0f;
                        c.difuse[1] = 200.0f / 255.0f;
                        c.difuse[2] = 200.0f / 255.0f;
                    }

                    // Parse and assign values for ambient
                    tinyxml2::XMLElement* ambientElement = colorElement->FirstChildElement("ambient");
                    if (ambientElement) {
                        int r, g, b;
                        ambientElement->QueryIntAttribute("R", &r);
                        ambientElement->QueryIntAttribute("G", &g);
                        ambientElement->QueryIntAttribute("B", &b);

                        c.ambient[0] = static_cast<float>(r) / 255.0f;
                        c.ambient[1] = static_cast<float>(g) / 255.0f;
                        c.ambient[2] = static_cast<float>(b) / 255.0f;
                    } else {
                        c.ambient[0] = 50.0f / 255.0f;
                        c.ambient[1] = 50.0f / 255.0f;
                        c.ambient[2] = 50.0f / 255.0f;
                    }

                    // Parse and assign values for specular
                    tinyxml2::XMLElement* specularElement = colorElement->FirstChildElement("specular");
                    if (specularElement) {
                        int r, g, b;
                        specularElement->QueryIntAttribute("R", &r);
                        specularElement->QueryIntAttribute("G", &g);
                        specularElement->QueryIntAttribute("B", &b);

                        c.specular[0] = static_cast<float>(r) / 255.0f;
                        c.specular[1] = static_cast<float>(g) / 255.0f;
                        c.specular[2] = static_cast<float>(b) / 255.0f;
                    } else {
                        c.specular[0] = 0.0f;
                        c.specular[1] = 0.0f;
                        c.specular[2] = 0.0f;
                    }

                    // Parse and assign values for emissive
                    tinyxml2::XMLElement* emissiveElement = colorElement->FirstChildElement("emissive");
                    if (emissiveElement) {
                        int r, g, b;
                        emissiveElement->QueryIntAttribute("R", &r);
                        emissiveElement->QueryIntAttribute("G", &g);
                        emissiveElement->QueryIntAttribute("B", &b);

                        c.emissive[0] = static_cast<float>(r) / 255.0f;
                        c.emissive[1] = static_cast<float>(g) / 255.0f;
                        c.emissive[2] = static_cast<float>(b) / 255.0f;
                    } else {
                        c.emissive[0] = 0.0f;
                        c.emissive[1] = 0.0f;
                        c.emissive[2] = 0.0f;
                    }

                    // Parse and assign value for shininess
                    tinyxml2::XMLElement* shininessElement = colorElement->FirstChildElement("shininess");
                    if (shininessElement) {
                        float shininessValue;
                        shininessElement->QueryFloatAttribute("value", &shininessValue);

                        c.shininess = shininessValue;
                    } else {
                        c.shininess = 0.0f;
                    }
                }
                else{
                    c.difuse[0] = 200.0f / 255.0f;
                    c.difuse[1] = 200.0f / 255.0f;
                    c.difuse[2] = 200.0f / 255.0f;

                    c.ambient[0] = 50.0f / 255.0f;
                    c.ambient[1] = 50.0f / 255.0f;
                    c.ambient[2] = 50.0f / 255.0f;

                    c.specular[0] = 0.0f;
                    c.specular[1] = 0.0f;
                    c.specular[2] = 0.0f;

                    c.emissive[0] = 0.0f;
                    c.emissive[1] = 0.0f;
                    c.emissive[2] = 0.0f;

                    c.shininess = 0.0f;

                }

                tinyxml2::XMLElement* textureElement = model->FirstChildElement("texture");
                const char* textureFile;
                if (textureElement) {
                    textureFile = textureElement->Attribute("file");

                }
                else{
                    textureFile = "";
                }

                // Add the model to the node's list of models
                node.modelsf.push_back(modelof);
                node.normalsf.push_back(modelon);
                node.modelst.push_back(modelot);
                node.colors.push_back(c);

                std::string cppString(textureFile);
                cout<<textureFile<<"\n";
                node.texVector.push_back(cppString);
            }
        }
    }

    // Parse child elements
    for (tinyxml2::XMLElement* child = element->FirstChildElement(); child; child = child->NextSiblingElement()) {
        if (strcmp(child->Name(), "group") == 0) {
            // Create a new child node
            Node childNode;
            // Recursively parse the child group
            parseGroup(child, childNode);
            // Add the child node to the parent node's list of children
            node.children.push_back(childNode);
        }
    }
}
Cena fromXml(const char* path) {
    tinyxml2::XMLDocument doc;
    std::tuple<int,int> janela_;
    std::vector<float> position_,lookAt_,up_,projection_;
    std::vector<float> point_,directional_,spotlight_;
    CinemaMode cm;
    std::vector<std::vector<Ponto>> modelos_;
    Cena c;
    if (doc.LoadFile(path) == tinyxml2::XML_SUCCESS) {
        tinyxml2::XMLElement* root = doc.FirstChildElement("world");
        if (root) {
            // Parsing da janela
            tinyxml2::XMLElement* window = root->FirstChildElement("window");
            int width, height;
            if (window) {

                window->QueryIntAttribute("width", &width);
                window->QueryIntAttribute("height", &height);
                std::cout << "Window Width: " << width << ", Height: " << height << std::endl;
            }
            janela_ = make_tuple( width,height); // criar par da janela

            // Parsing camera element
            tinyxml2::XMLElement* camera = root->FirstChildElement("camera");
            if (camera) {
                // Parsing position
                tinyxml2::XMLElement* position = camera->FirstChildElement("position");
                float x = 0, y = 0, z = 0;
                if (position) {

                    position->QueryFloatAttribute("x", &x);
                    position->QueryFloatAttribute("y", &y);
                    position->QueryFloatAttribute("z", &z);
                    std::cout << "Camera Position: (" << x << ", " << y << ", " << z << ")" << std::endl;
                }
                position_ = {x,y,z};
                // Parsing lookAt
                tinyxml2::XMLElement* lookAt = camera->FirstChildElement("lookAt");
                if (lookAt) {

                    lookAt->QueryFloatAttribute("x", &x);
                    lookAt->QueryFloatAttribute("y", &y);
                    lookAt->QueryFloatAttribute("z", &z);
                    std::cout << "Camera LookAt: (" << x << ", " << y << ", " << z << ")" << std::endl;
                }
                lookAt_ = {x,y,z};
                // Parsing up
                tinyxml2::XMLElement* up = camera->FirstChildElement("up");
                if (up) {

                    up->QueryFloatAttribute("x", &x);
                    up->QueryFloatAttribute("y", &y);
                    up->QueryFloatAttribute("z", &z);
                    std::cout << "Camera Up: (" << x << ", " << y << ", " << z << ")" << std::endl;
                }
                up_ = {x,y,z};

                // Parsing projection
                tinyxml2::XMLElement* projection = camera->FirstChildElement("projection");
                float fov, near, far;
                fov = near = far = 0;

                if (projection) {

                    projection->QueryFloatAttribute("fov", &fov);
                    projection->QueryFloatAttribute("near", &near);
                    projection->QueryFloatAttribute("far", &far);
                    std::cout << "Camera Projection: FOV=" << fov << ", Near=" << near << ", Far=" << far << std::endl;
                }
                projection_ = {fov,near,far};

                tinyxml2::XMLElement* cinema = camera->FirstChildElement("cinema");

                if (cinema){

                    cinema->QueryFloatAttribute("x", &x);
                    cinema->QueryFloatAttribute("y", &y);
                    cinema->QueryFloatAttribute("z", &z);
                    cinema->QueryIntAttribute("time", &cm.time);
                    cm.lookAt[0] = x;
                    cm.lookAt[1]=y;
                    cm.lookAt[2]=z;

                    for (tinyxml2::XMLElement* point = cinema->FirstChildElement(); point; point = point->NextSiblingElement()) {
                        const char* pointName = point->Name();
                        if (strcmp(pointName, "point") == 0) {
                            float xa,ya,za;
                            point->QueryFloatAttribute("x", &xa);
                            point->QueryFloatAttribute("y", &ya);
                            point->QueryFloatAttribute("z", &za);
                            Ponto p = Ponto(xa,ya,za);
                            cm.points.push_back(p);

                        }
                    }
                    for (tinyxml2::XMLElement* point = cinema->FirstChildElement(); point; point = point->NextSiblingElement()) {
                        const char* pointName = point->Name();
                        if (strcmp(pointName, "point") == 0) {
                            float xa,ya,za;
                            point->QueryFloatAttribute("x", &xa);
                            point->QueryFloatAttribute("y", &ya);
                            point->QueryFloatAttribute("z", &za);
                            Ponto p = Ponto(xa,ya,za);
                            cm.points.push_back(p);

                        }
                    }
                }
            }
            std::vector<Light> luzes;
            tinyxml2::XMLElement* lights = root->FirstChildElement("lights");
            if (lights) {
                for (tinyxml2::XMLElement* light = lights->FirstChildElement("light"); light; light = light->NextSiblingElement("light")) {
                    const char* type = light->Attribute("type");
                    Light l;
                    if (type) {
                        std::cout << "Light Type: " << type << std::endl;

                        if (strcmp(type, "point") == 0) {
                            float posX, posY, posZ;
                            l.tipo = 'p';
                            light->QueryFloatAttribute("posX", &posX);
                            light->QueryFloatAttribute("posY", &posY);
                            light->QueryFloatAttribute("posZ", &posZ);
                            std::cout << "Point Light Position: (" << posX << ", " << posY << ", " << posZ << ")" << std::endl;
                            // Handle point light parsing here
                            l.pos[0] = posX;l.pos[1]=posY;l.pos[2]=posZ;
                        }
                        else if (strcmp(type, "directional") == 0) {
                            float dirX, dirY, dirZ;
                            l.tipo = 'd';
                            light->QueryFloatAttribute("dirX", &dirX);
                            light->QueryFloatAttribute("dirY", &dirY);
                            light->QueryFloatAttribute("dirZ", &dirZ);
                            std::cout << "Directional Light Direction: (" << dirX << ", " << dirY << ", " << dirZ << ")" << std::endl;
                            // Handle directional light parsing here
                            l.dir[0] = dirX;l.dir[1]=dirY;l.dir[2]=dirZ;
                        }
                        else if (strcmp(type, "spot") == 0) {
                            float posX, posY, posZ,dirX, dirY, dirZ,cut;
                            l.tipo = 's';
                            light->QueryFloatAttribute("posX", &posX);
                            light->QueryFloatAttribute("posY", &posY);
                            light->QueryFloatAttribute("posZ", &posZ);
                            light->QueryFloatAttribute("dirX", &dirX);
                            light->QueryFloatAttribute("dirY", &dirY);
                            light->QueryFloatAttribute("dirZ", &dirZ);
                            light->QueryFloatAttribute("cutoff", &cut);

                            std::cout << "Spotlight Position: (" << posX << ", " << posY << ", " << posZ << ")" << std::endl;
                            // Handle spotlight parsing here
                            l.pos[0] = posX;l.pos[1]=posY;l.pos[2]=posZ;
                            l.dir[0] = dirX;l.dir[1]=dirY;l.dir[2]=dirZ;
                            l.cutoff = cut;
                        }
                    }
                    luzes.push_back(l);
                }
            }

            // Parsing group
            tinyxml2::XMLElement* group = root->FirstChildElement("group");
            c = Cena(janela_,position_,lookAt_,up_,projection_,cm);
            for (int j = 0; j <luzes.size();++j){
                c.addLight(luzes[j]);
            }
            tinyxml2::XMLElement* groupElement = root->FirstChildElement("group");

            if (groupElement) {
                // Parse the root group element
                Node rootNode;
                parseGroup(groupElement, rootNode);
                c.addRaiz(rootNode);

            }

        }

        // std::cout<<c.getRaizes().size()<<std::endl;
        // printNode(c.getRaizes()[0],0);
        return c;
    } else {
        std::cerr << "Failed to load XML file." << std::endl;
        return {};
    }

}




