#pragma once
#include "box2d.h"
#include "raylib.h"

class Caja {
private:
    b2Body* body;
    Texture2D texture;
    Vector2 size;
    float escala;

public:
    Caja(b2World* mundo, Vector2 posPx, Vector2 tamPx, Texture2D tex, float escalaM2P);
    void Dibujar();

    void SetStatic(bool isStatic);
    void Rotar(float radianes);

    ~Caja() {}
};