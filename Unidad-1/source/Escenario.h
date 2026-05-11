#pragma once
#include "box2d.h"
#include "raylib.h"

class Escenario {
private:
    b2Body* groundBody;
    float escala;

public:
    Escenario(b2World& mundo, int screenWidth, int screenHeight, float escalaM2P);
    void Dibujar();
};