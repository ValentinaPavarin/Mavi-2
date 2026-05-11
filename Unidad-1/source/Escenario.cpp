#include "Escenario.h"

Escenario::Escenario(b2World& mundo, int screenWidth, int screenHeight, float escalaM2P) {
    escala = escalaM2P;

    // 1. SUELO
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set((screenWidth / 2.0f) / escala, (screenHeight - 20.0f) / escala);
    groundBody = mundo.CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;
    groundBox.SetAsBox((screenWidth / 2.0f) / escala, 10.0f / escala);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &groundBox;
    fixtureDef.friction = 0.5f;
    groundBody->CreateFixture(&fixtureDef);

    // 2. PARED IZQUIERDA
    b2BodyDef leftWallDef;
    leftWallDef.position.Set(-0.2f, (screenHeight / 2.0f) / escala);
    b2Body* leftWall = mundo.CreateBody(&leftWallDef);

    b2PolygonShape leftBox;
    leftBox.SetAsBox(0.2f, (screenHeight / 2.0f) / escala);
    leftWall->CreateFixture(&leftBox, 0.0f);

    // 3. PARED DERECHA
    b2BodyDef rightWallDef;
    rightWallDef.position.Set((screenWidth / escala) + 0.2f, (screenHeight / 2.0f) / escala);
    b2Body* rightWall = mundo.CreateBody(&rightWallDef);

    b2PolygonShape rightBox;
    rightBox.SetAsBox(0.2f, (screenHeight / 2.0f) / escala);
    rightWall->CreateFixture(&rightBox, 0.0f);
}

void Escenario::Dibujar() {
    ClearBackground(SKYBLUE); // El cielo celeste

    b2Vec2 pos = groundBody->GetPosition();
    // Suelo verde
    DrawRectangle(0, (pos.y * escala) - 10, GetScreenWidth(), 40, GREEN);
}