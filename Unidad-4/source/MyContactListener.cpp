#include "MyContactListener.h"
#include "Ascensor.h" 

MyContactListener::MyContactListener(Ascensor* ascensor, bool& refVictoria)
    : m_ascensor(ascensor), m_refVictoria(refVictoria) {
}

void MyContactListener::BeginContact(b2Contact* contact) {

    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();


    uintptr_t labelA = fixtureA->GetBody()->GetUserData().pointer;
    uintptr_t labelB = fixtureB->GetBody()->GetUserData().pointer;

    if ((labelA == TIPO_PERSONAJE && labelB == TIPO_ASCENSOR) ||
        (labelB == TIPO_PERSONAJE && labelA == TIPO_ASCENSOR)) {

        if (m_ascensor != nullptr) {
            m_ascensor->ActivarMecanismo();
        }
    }

    if ((labelA == TIPO_PERSONAJE && labelB == TIPO_META) ||
        (labelB == TIPO_PERSONAJE && labelA == TIPO_META)) {

        m_refVictoria = true; 
    }
}

void MyContactListener::EndContact(b2Contact* contact) {
   
}