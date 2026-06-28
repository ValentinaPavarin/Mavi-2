#include "Ascensor.h"

Ascensor::Ascensor(b2World* mundo, b2Body* cuerpoBase, Vector2 posCentroPx, float escalaM2P, float anchoMetros, float altoMetros, Texture2D textura) {
    m_escala = escalaM2P;
    m_anchoM = anchoMetros;
    m_altoM = altoMetros;
    m_texture = textura;

    // 1. Definir y crear el cuerpo de la plataforma como DINÁMICO
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(posCentroPx.x / m_escala, posCentroPx.y / m_escala);
    bodyDef.fixedRotation = true; // El elevador debe mantenerse perfectamente horizontal

    m_body = mundo->CreateBody(&bodyDef);

    // 2. Darle forma
    b2PolygonShape cajaShape;
    cajaShape.SetAsBox(m_anchoM / 2.0f, m_altoM / 2.0f);

    // 3. Definir propiedades físicas
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &cajaShape;
    fixtureDef.density = 4.0f;    
    fixtureDef.friction = 0.6f;   

    m_body->CreateFixture(&fixtureDef);

    m_body->GetUserData().pointer = (uintptr_t)TIPO_ASCENSOR;

    b2PrismaticJointDef jointDef;

    // Definimos el eje de traslación
    b2Vec2 worldAxis(0.0f, 1.0f);

    jointDef.Initialize(cuerpoBase, m_body, m_body->GetPosition(), worldAxis);

    // Configuración de límites 
    jointDef.lowerTranslation = -10.0f; 
    jointDef.upperTranslation = 0.0f;  
    jointDef.enableLimit = true;

    // Configuración inicial del motor
    jointDef.maxMotorForce = 1500.0f;   
    jointDef.motorSpeed = 0.0f;         
    jointDef.enableMotor = false;      

    m_joint = (b2PrismaticJoint*)mundo->CreateJoint(&jointDef);
}

void Ascensor::ActivarMecanismo() {
    if (m_joint != nullptr && !m_joint->IsMotorEnabled()) {
        m_joint->EnableMotor(true);
        m_joint->SetMotorSpeed(-3.5f);
    }
}

void Ascensor::Dibujar() {

    b2Vec2 posM = m_body->GetPosition();


    float posX = posM.x * m_escala;
    float posY = posM.y * m_escala;
    float anchoPx = m_anchoM * m_escala;
    float altoPx = m_altoM * m_escala;

 
    Rectangle sourceRec = { 0.0f, 0.0f, (float)m_texture.width, (float)m_texture.height };
    Rectangle destRec = { posX, posY, anchoPx, altoPx };


    Vector2 origin = { anchoPx / 2.0f, altoPx / 2.0f };
    float anguloGrados = m_body->GetAngle() * RAD2DEG;


    DrawTexturePro(m_texture, sourceRec, destRec, origin, anguloGrados, WHITE);
}