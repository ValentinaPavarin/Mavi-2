#include "Plataforma.h"

Plataforma::Plataforma(b2World* mundo, Vector2 posCentroPx, float escalaM2P, float anchoMetros, float altoMetros, Texture2D textura) {
    m_escala = escalaM2P;
    m_anchoM = anchoMetros;
    m_altoM = altoMetros;
    m_texture = textura;

    // 1. Definir la posición del cuerpo estático en metros
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(posCentroPx.x / m_escala, posCentroPx.y / m_escala);

    // 2. Crear el cuerpo en el mundo físico
    m_body = mundo->CreateBody(&bodyDef);

    // 3. Definir la forma
    b2PolygonShape cajaShape;
    cajaShape.SetAsBox(m_anchoM / 2.0f, m_altoM / 2.0f);

    // 4. Configurar las propiedades físicas fijas
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &cajaShape;
    fixtureDef.friction = 0.5f;  
    fixtureDef.density = 0.0f;   

    m_body->CreateFixture(&fixtureDef);

    m_body->GetUserData().pointer = (uintptr_t)TIPO_SUELO;
}

void Plataforma::Dibujar() {
  
    b2Vec2 posM = m_body->GetPosition();


    float posX = posM.x * m_escala;
    float posY = posM.y * m_escala;
    float anchoPx = m_anchoM * m_escala;
    float altoPx = m_altoM * m_escala;

  
    Rectangle sourceRec = { 0.0f, 0.0f, (float)m_texture.width, (float)m_texture.height };

    // Definimos el destino en la pantalla
    Rectangle destRec = { posX, posY, anchoPx, altoPx };

    // El centro de rotación y origen
    Vector2 origin = { anchoPx / 2.0f, altoPx / 2.0f };


    float anguloGrados = m_body->GetAngle() * RAD2DEG;

    // Dibujamos el sprite estirado a la dimensión física
    DrawTexturePro(m_texture, sourceRec, destRec, origin, anguloGrados, WHITE);
}