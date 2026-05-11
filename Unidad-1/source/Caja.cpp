#include "Caja.h"

Caja::Caja(b2World* mundo, Vector2 posPx, Vector2 tamPx, Texture2D tex, float escalaM2P) {
    texture = tex;
    size = tamPx;
    escala = escalaM2P;

    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(posPx.x / escala, posPx.y / escala);

    body = mundo->CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox((size.x / 2.0f) / escala, (size.y / 2.0f) / escala);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.5f;

    body->CreateFixture(&fixtureDef);
}

void Caja::SetStatic(bool isStatic) {
    if (isStatic) body->SetType(b2_staticBody);
    else body->SetType(b2_dynamicBody);
}

void Caja::Rotar(float radianes) {
    // SetTransform permite cambiar ángulo y posición manualmente en Box2D
    body->SetTransform(body->GetPosition(), body->GetAngle() + radianes);
}

void Caja::Dibujar() {
    b2Vec2 pos = body->GetPosition();
    float angulo = body->GetAngle() * RAD2DEG;
    Rectangle dest = { pos.x * escala, pos.y * escala, size.x, size.y };
    Rectangle source = { 0, 0, (float)texture.width, (float)texture.height };
    Vector2 origin = { size.x / 2.0f, size.y / 2.0f };

    DrawTexturePro(texture, source, dest, origin, angulo, WHITE);
}