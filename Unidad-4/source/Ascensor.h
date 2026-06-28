#pragma once
#include "box2d.h"
#include "raylib.h"
#include "MyContactListener.h" 

class Ascensor {
private:
    b2Body* m_body;                
    b2PrismaticJoint* m_joint; 
    Texture2D m_texture;            
    float m_escala;                
    float m_anchoM;
    float m_altoM;

public:
  
    Ascensor(b2World* mundo, b2Body* cuerpoBase, Vector2 posCentroPx, float escalaM2P, float anchoMetros, float altoMetros, Texture2D textura);
    ~Ascensor() {}

    void ActivarMecanismo();

    void Dibujar();


    b2Body* GetBody() const { return m_body; }
};