#include "Puente.h"

Puente::Puente(b2World* mundo, Vector2 posIzqPx, Vector2 posDerPx, int cantidadTablas, float escalaM2P, Texture2D tTronco, Texture2D tTabla) {
    escala = escalaM2P;
    texTronco = tTronco;
    texTabla = tTabla;

    altoTabla = 0.2f; 

    // 1. CREACIÓN DE LOS PUNTOS DE APOYO (Troncos Grandes)
    float anchoTronco = 3.0f;
    float altoTronco = 5.5f;

    // Tronco Izquierdo
    b2BodyDef troncoIzqDef;
    troncoIzqDef.position.Set(posIzqPx.x / escala, posIzqPx.y / escala);
    troncoIzquierdo = mundo->CreateBody(&troncoIzqDef);
    b2PolygonShape shapeTronco;
    shapeTronco.SetAsBox(anchoTronco / 2.0f, altoTronco / 2.0f);
    troncoIzquierdo->CreateFixture(&shapeTronco, 0.0f);

    // Tronco Derecho
    b2BodyDef troncoDerDef;
    troncoDerDef.position.Set(posDerPx.x / escala, posDerPx.y / escala);
    troncoDerecho = mundo->CreateBody(&troncoDerDef);
    troncoDerecho->CreateFixture(&shapeTronco, 0.0f);

    // 2. CREACIÓN DE LAS TABLAS DEL PUENTE
    float inicioX = (posIzqPx.x + (anchoTronco / 2.0f) * escala) / escala;
    float finX = (posDerPx.x - (anchoTronco / 2.0f) * escala) / escala;
    float distanciaTotal = finX - inicioX;

    anchoTabla = distanciaTotal / cantidadTablas;
    float alturaY = (posIzqPx.y - (altoTronco / 2.0f) * escala + 10.0f) / escala;

    for (int i = 0; i < cantidadTablas; i++) {
        b2BodyDef tablaDef;
        tablaDef.type = b2_dynamicBody;
        tablaDef.position.Set(inicioX + (anchoTabla * i) + (anchoTabla / 2.0f), alturaY);

        b2Body* nuevaTabla = mundo->CreateBody(&tablaDef);

        b2PolygonShape shapeTabla;
        shapeTabla.SetAsBox(anchoTabla / 2.0f, altoTabla / 2.0f);

        b2FixtureDef fixDef;
        fixDef.shape = &shapeTabla;
        fixDef.density = 1.2f;
        fixDef.friction = 0.7f;

        nuevaTabla->CreateFixture(&fixDef);
        tablas.push_back(nuevaTabla);
    }

    // 3. CONEXIÓN MEDIANTE REVOLUTE JOINTS
    b2RevoluteJointDef revDef;

    b2Vec2 anclajeInicial(inicioX, alturaY);
    revDef.Initialize(troncoIzquierdo, tablas[0], anclajeInicial);
    mundo->CreateJoint(&revDef);

    for (size_t i = 0; i < tablas.size() - 1; i++) {
        b2Vec2 puntoAnclaje(tablas[i]->GetPosition().x + (anchoTabla / 2.0f), alturaY);
        revDef.Initialize(tablas[i], tablas[i + 1], puntoAnclaje);
        mundo->CreateJoint(&revDef);
    }

    b2Vec2 anclajeFinal(finX, alturaY);
    revDef.Initialize(tablas.back(), troncoDerecho, anclajeFinal);
    mundo->CreateJoint(&revDef);

    // 4. DISTANCE JOINTS
    if (tablas.size() > 3) {
        b2DistanceJointDef distDef1;
        b2DistanceJointDef distDef2;

        size_t indiceMedioIzq = tablas.size() / 3;
        size_t indiceMedioDer = (tablas.size() * 2) / 3;

        b2Vec2 soporteAltoIzq = troncoIzquierdo->GetPosition();
        soporteAltoIzq.y -= 2.5f;

        b2Vec2 soporteAltoDer = troncoDerecho->GetPosition();
        soporteAltoDer.y -= 2.5f;

        distDef1.Initialize(troncoIzquierdo, tablas[indiceMedioIzq], soporteAltoIzq, tablas[indiceMedioIzq]->GetPosition());
        distDef2.Initialize(troncoDerecho, tablas[indiceMedioDer], soporteAltoDer, tablas[indiceMedioDer]->GetPosition());

        b2LinearStiffness(distDef1.stiffness, distDef1.damping, 1.4f, 0.4f, troncoIzquierdo, tablas[indiceMedioIzq]);
        b2LinearStiffness(distDef2.stiffness, distDef2.damping, 1.4f, 0.4f, troncoDerecho, tablas[indiceMedioDer]);

        mundo->CreateJoint(&distDef1);
        mundo->CreateJoint(&distDef2);
    }
}

void Puente::Dibujar() {
    float anchoTroncoM = 3.0f;
    float altoTroncoM = 5.5f;

    // 1. Dibujar Tronco Izquierdo
    Vector2 pTroncoIzq = { troncoIzquierdo->GetPosition().x * escala, troncoIzquierdo->GetPosition().y * escala };
    Rectangle destIzq = { pTroncoIzq.x, pTroncoIzq.y, anchoTroncoM * escala, altoTroncoM * escala };
    Vector2 origenTronco = { destIzq.width / 2.0f, destIzq.height / 2.0f };
    DrawTexturePro(texTronco, { 0, 0, (float)texTronco.width, (float)texTronco.height }, destIzq, origenTronco, 0.0f, WHITE);

    // 2. Dibujar Tronco Derecho
    Vector2 pTroncoDer = { troncoDerecho->GetPosition().x * escala, troncoDerecho->GetPosition().y * escala };
    Rectangle destDer = { pTroncoDer.x, pTroncoDer.y, anchoTroncoM * escala, altoTroncoM * escala };
    DrawTexturePro(texTronco, { 0, 0, (float)texTronco.width, (float)texTronco.height }, destDer, origenTronco, 0.0f, WHITE);

    // 3. Dibujar las Cuerdas de los Distance Joints
    b2Vec2 soporteAltoIzq = troncoIzquierdo->GetPosition(); soporteAltoIzq.y -= 2.5f;
    b2Vec2 soporteAltoDer = troncoDerecho->GetPosition(); soporteAltoDer.y -= 2.5f;

    if (tablas.size() > 3) {
        Vector2 s1 = { soporteAltoIzq.x * escala, soporteAltoIzq.y * escala };
        Vector2 t1 = { tablas[tablas.size() / 3]->GetPosition().x * escala, tablas[tablas.size() / 3]->GetPosition().y * escala };
        Vector2 s2 = { soporteAltoDer.x * escala, soporteAltoDer.y * escala };
        Vector2 t2 = { tablas[(tablas.size() * 2) / 3]->GetPosition().x * escala, tablas[(tablas.size() * 2) / 3]->GetPosition().y * escala };

        DrawLineV(s1, t1, DARKGRAY);
        DrawLineV(s2, t2, DARKGRAY);
    }

    // 4. Dibujar cada una de las Tablas
    for (b2Body* tabla : tablas) {
        Vector2 pTabla = { tabla->GetPosition().x * escala, tabla->GetPosition().y * escala };
        float anguloGrados = tabla->GetAngle() * RAD2DEG;

        Rectangle destTabla = { pTabla.x, pTabla.y, anchoTabla * escala, altoTabla * escala };
        Vector2 origenTabla = { destTabla.width / 2.0f, destTabla.height / 2.0f };

        DrawTexturePro(texTabla, { 0, 0, (float)texTabla.width, (float)texTabla.height }, destTabla, origenTabla, anguloGrados, WHITE);
    }
}