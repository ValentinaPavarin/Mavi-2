#pragma once
#include "box2d.h"
#include "raylib.h"
#include "Mecanismo.h"

class Game {
private:
    // Configuración de la pantalla y escala física
    const int screenWidth = 800;
    const int screenHeight = 600;
    float scale = 30.0f;

    // Punteros del motor físico y nuestro objeto articulado
    b2World* world;
    Mecanismo* mecanismo;

public:
    Game(); 
    ~Game(); 

    void Run();   
    void Update(); 
    void Draw();   
};