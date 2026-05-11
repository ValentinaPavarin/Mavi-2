#pragma once
#include "box2d.h"
#include "raylib.h"
#include "Escenario.h"
#include "Caja.h"
#include <vector>

class Game {
private:
    // Dimensiones de pantalla
    const int screenWidth = 800;
    const int screenHeight = 600;

    // Física
    b2World* world;
    float scale = 30.0f;

    // Elementos del juego
    Escenario* escenario;
    std::vector<Caja*> cajas;

    
    Caja* cajaActual;          
    bool esperandoColocacion;  
    Texture2D texCaja;         

public:
    Game();
    ~Game();

    void Run();
    void Update();
    void Draw();
};