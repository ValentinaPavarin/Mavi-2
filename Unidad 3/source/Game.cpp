#include "Game.h"

Game::Game() {

    InitWindow(screenWidth, screenHeight, "UNL - MAVI II - Unidad 3");
    SetTargetFPS(60);

    // 2. Crear el mundo físico

    b2Vec2 gravity(0.0f, 9.8f);
    world = new b2World(gravity);

    // 3. Crear mecanismo
    Vector2 posInicialPx = { screenWidth / 2.0f, 120.0f };
    mecanismo = new Mecanismo(world, posInicialPx, scale);
}

Game::~Game() {
    if (mecanismo) delete mecanismo;
    if (world) delete world;

    CloseWindow(); 
}

void Game::Update() {
    
    float timeStep = 1.0f / 60.0f;
    world->Step(timeStep, 8, 3);

    // INTERACTIVIDAD: Al presionar la FLECHA DERECHA, le pegamos un empujón al péndulo
    if (IsKeyPressed(KEY_RIGHT)) {
        mecanismo->AplicarImpulso();
    }
}

void Game::Draw() {
    BeginDrawing();
    ClearBackground(WHITE);

    // DibujaR el péndulo compuesto
    mecanismo->Dibujar();

    // Textos informativos
    DrawText("- Arriba: Revolute Joint", 20, 55, 16, DARKGRAY);
    DrawText("- Abajo: Distance Joint", 20, 75, 16, RED);

    DrawText("Presiona FLECHA DERECHA para aplicar un impulso a la punta", 20, screenHeight - 40, 18, GREEN);


    DrawFPS(screenWidth - 100, 20);

    EndDrawing();
}

void Game::Run() {
        while (!WindowShouldClose()) {
        Update();
        Draw();
    }
}