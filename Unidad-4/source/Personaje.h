#pragma once
#include "box2d.h"
#include "raylib.h"
#include "MyContactListener.h" 

class Personaje {
private:
    b2Body* m_body;       
    Texture2D m_texture;   
    float m_escala;      

    // Dimensiones físicas del personaje en metros
    float m_anchoM;
    float m_altoM;

    // Características de movimiento configurables
    float m_velocidadCaminar;
    float m_fuerzaSalto;

public:

    Personaje(b2World* mundo, Vector2 posSpawnPx, float escalaM2P, float anchoMetros, float altoMetros, Texture2D textura);
    ~Personaje() {}

    void Controlar();

    void Dibujar();


    Vector2 GetPosicionPx() const;
    b2Body* GetBody() const { return m_body; }
};