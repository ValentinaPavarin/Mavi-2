#include "Caja.h"

Caja::Caja(b2World* mundo, Vector2 posSpawnPx, float escalaM2P, Texture2D textura) {
    escala = escalaM2P;
    texCaja = textura;

    
    posicionInicial.Set(posSpawnPx.x / escala, posSpawnPx.y / escala);

    ancho = 1.0f;
    alto = 1.0f;

    // Definición del cuerpo dinámico
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = posicionInicial;
    bodyDef.bullet = true; 
    body = mundo->CreateBody(&bodyDef);

    b2PolygonShape boxShape;
    boxShape.SetAsBox(ancho / 2.0f, alto / 2.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;
    fixtureDef.density = 1.0f;    
    fixtureDef.friction = 0.8f;    
    fixtureDef.restitution = 0.1f; 

    body->CreateFixture(&fixtureDef);
}

void Caja::Controlar() {
 
    float fuerzaGiro = 15.0f;

    if (IsKeyDown(KEY_LEFT)) {
        body->ApplyTorque(-fuerzaGiro, true);
    }

    if (IsKeyDown(KEY_RIGHT)) {
        body->ApplyTorque(fuerzaGiro, true);
    }
}

void Caja::Resetear() {
    body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
    body->SetAngularVelocity(0.0f);
    body->SetTransform(posicionInicial, 0.0f);
}

void Caja::Dibujar() {
    Vector2 pCaja = { body->GetPosition().x * escala, body->GetPosition().y * escala };
    float anguloGrados = body->GetAngle() * RAD2DEG;

    Rectangle dest = { pCaja.x, pCaja.y, ancho * escala, alto * escala };
    Vector2 origen = { dest.width / 2.0f, dest.height / 2.0f };

    DrawTexturePro(texCaja, { 0, 0, (float)texCaja.width, (float)texCaja.height }, dest, origen, anguloGrados, WHITE);
}