#pragma once
#include "box2d.h"
#include "raylib.h"
#include <vector>

class Puente {
private:
    // Cuerpos estáticos
    b2Body* troncoIzquierdo;
    b2Body* troncoDerecho;

    std::vector<b2Body*> tablas;

    Texture2D texTronco;
    Texture2D texTabla;

    float escala; 

    float anchoTabla;
    float altoTabla;

public:

    Puente(b2World* mundo, Vector2 posIzqPx, Vector2 posDerPx, int cantidadTablas, float escalaM2P, Texture2D tTronco, Texture2D tTabla);

    ~Puente() {}

    void Dibujar();
};