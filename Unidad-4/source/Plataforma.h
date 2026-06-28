#pragma once
#include "box2d.h"
#include "raylib.h"
#include "MyContactListener.h" 

class Plataforma {
private:
    b2Body* m_body;         
    Texture2D m_texture;    
    float m_escala;        

    // Dimensiones físicas en metros
    float m_anchoM;
    float m_altoM;

public:
    // Constructor parametrizado y moldeable
    Plataforma(b2World* mundo, Vector2 posCentroPx, float escalaM2P, float anchoMetros, float altoMetros, Texture2D textura);
    ~Plataforma() {}

    // Renderiza el sprite de la plataforma estirándolo a sus dimensiones reales en píxeles
    void Dibujar();

    inline void Draw() { Dibujar(); }

    float GetAnchoM() const { return m_anchoM; }
    float GetAltoM() const { return m_altoM; }
};