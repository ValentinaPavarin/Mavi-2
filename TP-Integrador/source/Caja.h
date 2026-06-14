#pragma once
#include "box2d.h"
#include "raylib.h"

class Caja {
private:
    b2Body* body;        
    Texture2D texCaja;   
    float escala;       
    float ancho;
    float alto;


    b2Vec2 posicionInicial;

public:
    
    Caja(b2World* mundo, Vector2 posSpawnPx, float escalaM2P, Texture2D textura);

    ~Caja() {}

    void Controlar();

    // Restablece la posición, velocidad y rotación de la caja al punto de partida original
    void Resetear();

    void Dibujar();

    float GetX() { return body->GetPosition().x * escala; }

    float GetVelocidad() {
        b2Vec2 vel = body->GetLinearVelocity();
        return vel.Length();
    }
};