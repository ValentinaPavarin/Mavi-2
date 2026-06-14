#pragma once
#include "box2d.h"
#include "raylib.h"
#include "Puente.h"
#include "Caja.h"

class Game {
private:
    // Dimensiones de la pantalla
    const int screenWidth = 1024;
    const int screenHeight = 768;
    float scale = 30.0f;

    b2World* world;

    Puente* puente;
    Caja* caja;

    Texture2D texTronco;
    Texture2D texTabla;

    Texture2D texFondo;

    Vector2 posIzqPx;
    Vector2 posDerPx;
    Vector2 posCajaPx;

    bool victoria;
    bool derrota; 

    void InicializarEscena();
    void LimpiarEscena();

public:
    ~Game();

    void Update();
    void Draw();  
    void Run();    
};