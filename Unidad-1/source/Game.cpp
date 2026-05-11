#include "Game.h"

Game::Game() {
    InitWindow(screenWidth, screenHeight, "MAVI 2 - U1");
    SetTargetFPS(60);

    b2Vec2 gravity(0.0f, 9.8f);
    world = new b2World(gravity);

    cajaActual = nullptr;
    esperandoColocacion = false;

    // Cargar Recursos
    texCaja = LoadTexture("resources/caja.png");
    escenario = new Escenario(*world, screenWidth, screenHeight, scale);
}

Game::~Game() {
    for (Caja* c : cajas) { delete c; }
    cajas.clear();
    if (cajaActual) delete cajaActual;

    UnloadTexture(texCaja);
    delete escenario;
    delete world;
    CloseWindow();
}

void Game::Update() {
    float timeStep = 1.0f / 60.0f;
    world->Step(timeStep, 6, 2);

    // 1. Iniciar colocación con la tecla ESPACIO
    if (IsKeyPressed(KEY_SPACE) && !esperandoColocacion) {
        // La caja aparece en la parte superior central
        Vector2 posInicial = { (float)screenWidth / 2.0f, 100.0f };
        cajaActual = new Caja(world, posInicial, { 90.0f, 90.0f }, texCaja, scale);
        esperandoColocacion = true;
    }

    // 2. Si hay una caja esperando ser soltada
    if (esperandoColocacion && cajaActual != nullptr) {

        // Rotar con flechas IZQUIERDA y DERECHA
        if (IsKeyDown(KEY_LEFT)) {
            cajaActual->Rotar(-0.05f);
        }
        if (IsKeyDown(KEY_RIGHT)) {
            cajaActual->Rotar(0.05f);
        }

        // 3. Confirmar y soltar con ENTER
        if (IsKeyPressed(KEY_ENTER)) {
            cajaActual->SetStatic(false);
            cajas.push_back(cajaActual);
            cajaActual = nullptr;
            esperandoColocacion = false;
        }
    }
}

void Game::Draw() {
    BeginDrawing();

    escenario->Dibujar();

    // Dibujar las cajas que ya están simulando físicamente
    for (Caja* c : cajas) {
        c->Dibujar();
    }

    // Dibujar la caja que se está rotando actualmente
    if (cajaActual) {
        cajaActual->Dibujar();
    }

    if (esperandoColocacion) {
        DrawText("Mueva a la derecha o izquierda para rotar la caja", 120, 500, 20, DARKGRAY);
        DrawText("Oprima ENTER para soltar la caja", 230, 530, 20, MAROON);
    }
    else {
        DrawText("Presione ESPACIO para generar una caja", 200, 530, 20, DARKGRAY);
    }

    DrawFPS(10, 10);
    EndDrawing();
}

void Game::Run() {
    while (!WindowShouldClose()) {
        Update();
        Draw();
    }
}