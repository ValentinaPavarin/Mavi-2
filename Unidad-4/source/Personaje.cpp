#include "Personaje.h"

Personaje::Personaje(b2World* mundo, Vector2 posSpawnPx, float escalaM2P, float anchoMetros, float altoMetros, Texture2D textura) {
    m_escala = escalaM2P;
    m_anchoM = anchoMetros;
    m_altoM = altoMetros;
    m_texture = textura;

    // Valores por defecto para el movimiento
    m_velocidadCaminar = 7.0f; 
    m_fuerzaSalto = 30.0f;  

    // 1. Definir la posición de spawn en metros
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(posSpawnPx.x / m_escala, posSpawnPx.y / m_escala);

 
    bodyDef.fixedRotation = true;

    // 2. Crear el cuerpo en el mundo físico
    m_body = mundo->CreateBody(&bodyDef);

    // 3. Definir la forma
    b2PolygonShape cajaShape;
    cajaShape.SetAsBox(m_anchoM / 2.0f, m_altoM / 2.0f);

    // 4. Configurar las propiedades física
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &cajaShape;
    fixtureDef.density = 1.0f;    
    fixtureDef.friction = 0.2f;  
    fixtureDef.restitution = 0.0f;

    m_body->CreateFixture(&fixtureDef);


    m_body->GetUserData().pointer = (uintptr_t)TIPO_PERSONAJE;
}

void Personaje::Controlar() {
    // Obtenemos la velocidad lineal actual
    b2Vec2 velocidadActual = m_body->GetLinearVelocity();

    // Movimiento Horizontal
    if (IsKeyDown(KEY_LEFT)) {
        velocidadActual.x = -m_velocidadCaminar;
    }
    else if (IsKeyDown(KEY_RIGHT)) {
        velocidadActual.x = m_velocidadCaminar;
    }
    else {
        velocidadActual.x = 0.0f;
    }

    if (IsKeyPressed(KEY_SPACE) && b2Abs(velocidadActual.y) < 0.15f) {

        m_body->SetLinearVelocity(b2Vec2(velocidadActual.x, 0.0f));


        m_body->ApplyLinearImpulseToCenter(b2Vec2(0.0f, -m_fuerzaSalto), true);
    }
    else {

        m_body->SetLinearVelocity(velocidadActual);
    }
}

void Personaje::Dibujar() {
    // Obtenemos la posición actual desde el motor físico
    b2Vec2 posM = m_body->GetPosition();

    // Convertimos la posición central y dimensiones de metros a píxeles de pantalla
    float posX = posM.x * m_escala;
    float posY = posM.y * m_escala;
    float anchoPx = m_anchoM * m_escala;
    float altoPx = m_altoM * m_escala;

    // Rectángulo origen en la textura
    Rectangle sourceRec = { 0.0f, 0.0f, (float)m_texture.width, (float)m_texture.height };

    // Rectángulo de destino en la pantalla
    Rectangle destRec = { posX, posY, anchoPx, altoPx };


    Vector2 origin = { anchoPx / 2.0f, altoPx / 2.0f };

    // Dibujamos el sprite con la rotación real
    float anguloGrados = m_body->GetAngle() * RAD2DEG;
    DrawTexturePro(m_texture, sourceRec, destRec, origin, anguloGrados, WHITE);
}

Vector2 Personaje::GetPosicionPx() const {
    b2Vec2 posM = m_body->GetPosition();
    return Vector2{ posM.x * m_escala, posM.y * m_escala };
}