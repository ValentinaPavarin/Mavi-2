#pragma once
#include "box2d.h"
#include "raylib.h"
#include <vector>
#include "MyContactListener.h"
#include "Personaje.h"
#include "Plataforma.h"
#include "Ascensor.h"


enum GameState {
    STATE_PLAYING,
    STATE_VICTORY
};

class Game {
private:

    const int screenWidth = 1024;
    const int screenHeight = 768;
    float scale = 30.0f;

   
    b2World* world;
    MyContactListener* contactListener;
    Personaje* personaje;
    Ascensor* ascensor;
    b2Body* metaSensor; 

    std::vector<Plataforma*> plataformas;

    Texture2D texPersonaje;
    Texture2D texPlataforma;
    Texture2D texAscensor;
    Texture2D texMeta;

    GameState estadoActual;
    bool victoria;


    void InicializarEscena();
    void LimpiarEscena();

public:
    Game(); 
    ~Game(); 

    void Update(); 
    void Draw();   
    void Run();   
};