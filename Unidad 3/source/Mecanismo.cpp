#include "Mecanismo.h"

Mecanismo::Mecanismo(b2World* mundo, Vector2 posBasePx, float escalaM2P) {
    escala = escalaM2P;


    // 1. CREACIÓN DE LOS CUERPOS FÍSICOS


    // CUERPO A: Base del techo (Estático)
    b2BodyDef baseDef;
    baseDef.position.Set(posBasePx.x / escala, posBasePx.y / escala);
    bodyBase = mundo->CreateBody(&baseDef);

    b2PolygonShape baseBox;
    baseBox.SetAsBox(0.4f, 0.4f); // Un bloque pequeño como soporte
    bodyBase->CreateFixture(&baseBox, 0.0f);


    // CUERPO B: Masa Intermedia
    b2BodyDef m1Def;
    m1Def.type = b2_dynamicBody;
    m1Def.position.Set(posBasePx.x / escala, (posBasePx.y + 90.0f) / escala);
    bodyMasa1 = mundo->CreateBody(&m1Def);

    b2CircleShape m1Shape;
    m1Shape.m_radius = 0.5f; 
    b2FixtureDef fix1;
    fix1.shape = &m1Shape;
    fix1.density = 2.0f;     
    bodyMasa1->CreateFixture(&fix1);


    // CUERPO C: Masa de la Punta
    b2BodyDef m2Def;
    m2Def.type = b2_dynamicBody;
    m2Def.position.Set(posBasePx.x / escala, (posBasePx.y + 180.0f) / escala);
    bodyMasa2 = mundo->CreateBody(&m2Def);

    b2CircleShape m2Shape;
    m2Shape.m_radius = 0.6f;
    b2FixtureDef fix2;
    fix2.shape = &m2Shape;
    fix2.density = 1.0f;
    bodyMasa2->CreateFixture(&fix2);

       
    // 2. CONFIGURACIÓN DEL REVOLUTE JOINT (Bisagra)

    b2RevoluteJointDef revDef;

    // Conecta bodyBase y bodyMasa1 compartiendo el punto de anclaje de la base
    revDef.Initialize(bodyBase, bodyMasa1, bodyBase->GetPosition());

    jointBisagra = (b2RevoluteJoint*)mundo->CreateJoint(&revDef);

    
    // 3. CONFIGURACIÓN DEL DISTANCE JOINT (Resorte Elástico)
    
    b2DistanceJointDef distDef;

    // Conecta bodyMasa1 y bodyMasa2 vinculando sus centros actuales
    distDef.Initialize(bodyMasa1, bodyMasa2, bodyMasa1->GetPosition(), bodyMasa2->GetPosition());

    float frecuenciaHz = 2.0f;   
    float amortiguacion = 0.15f; 

 
    b2LinearStiffness(distDef.stiffness, distDef.damping, frecuenciaHz, amortiguacion, bodyMasa1, bodyMasa2);

    jointResorte = (b2DistanceJoint*)mundo->CreateJoint(&distDef);
}

void Mecanismo::AplicarImpulso() {

    bodyMasa2->ApplyLinearImpulseToCenter(b2Vec2(18.0f, 0.0f), true);
}

void Mecanismo::Dibujar() {
 
    Vector2 pBase = { bodyBase->GetPosition().x * escala, bodyBase->GetPosition().y * escala };
    Vector2 pMasa1 = { bodyMasa1->GetPosition().x * escala, bodyMasa1->GetPosition().y * escala };
    Vector2 pMasa2 = { bodyMasa2->GetPosition().x * escala, bodyMasa2->GetPosition().y * escala };

    // 2. Dibujamos los hilos / conexiones
    DrawLineV(pBase, pMasa1, DARKGRAY); // Hilo superior rígido
    DrawLineV(pMasa1, pMasa2, RED);     // Hilo inferior

    // 3. Dibujamos los cuerpos

    // Soporte cuadrado superior
    DrawRectangle(pBase.x - 12, pBase.y - 12, 24, 24, BLACK);

    // Primera esfera (Masa intermedia)
    DrawCircleV(pMasa1, 0.5f * escala, MAROON);
    DrawCircleLines(pMasa1.x, pMasa1.y, 0.5f * escala, BLACK); // Contorno para notar rotación

    // Segunda esfera (Masa de la punta elástica)
    DrawCircleV(pMasa2, 0.6f * escala, BLUE);
    DrawCircleLines(pMasa2.x, pMasa2.y, 0.6f * escala, BLACK);
}