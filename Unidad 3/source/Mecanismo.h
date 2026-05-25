#pragma once
#include "box2d.h"
#include "raylib.h"

class Mecanismo {
private:
    // Cuerpos físicos
    b2Body* bodyBase;      // El punto fijo de anclaje 
    b2Body* bodyMasa1;     // Primer tramo del péndulo 
    b2Body* bodyMasa2;     // Segundo tramo del péndulo

    // Uniones físicas
    b2RevoluteJoint* jointBisagra;
    b2DistanceJoint* jointResorte;

    float escala; 

public:
 
    Mecanismo(b2World* mundo, Vector2 posBasePx, float escalaM2P);

    ~Mecanismo() {}

    void AplicarImpulso();

    void Dibujar();
};