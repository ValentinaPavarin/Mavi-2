#pragma once
#include "box2d.h"


enum TipoObjeto {
    TIPO_SUELO,
    TIPO_PERSONAJE,
    TIPO_ASCENSOR,
    TIPO_META
};


class Ascensor;

class MyContactListener : public b2ContactListener {
private:
    Ascensor* m_ascensor;  
    bool& m_refVictoria;    

public:
 
    MyContactListener(Ascensor* ascensor, bool& refVictoria);

    void BeginContact(b2Contact* contact) override;

    void EndContact(b2Contact* contact) override;
};