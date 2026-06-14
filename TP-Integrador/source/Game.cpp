#include "Game.h"

Game::Game() {
   
    InitWindow(screenWidth, screenHeight, "Mavix - TP Integrador: Puente Articulado Elastico");
    SetTargetFPS(60);

    // Cargar Sprites
    texTronco = LoadTexture("resources/tronco.png");
    texTabla = LoadTexture("resources/tabla.png");
    texCaja = LoadTexture("resources/caja.png");
    texFondo = LoadTexture("resources/fondo.png");

    posIzqPx = { 130.0f, 520.0f };         
    posDerPx = { 894.0f, 520.0f };         
    posCajaPx = { 130.0f, 150.0f };        

    world = nullptr;
    puente = nullptr;
    caja = nullptr;
    InicializarEscena();
}

Game::~Game() {
    LimpiarEscena();

    UnloadTexture(texTronco);
    UnloadTexture(texTabla);
    UnloadTexture(texCaja);
    UnloadTexture(texFondo);

    CloseWindow();
}

void Game::InicializarEscena() {
    LimpiarEscena();

    b2Vec2 gravity(0.0f, 9.8f);
    world = new b2World(gravity);

    // Instanciar el mecanismo del puente
    puente = new Puente(world, posIzqPx, posDerPx, 20, scale, texTronco, texTabla);
    caja = new Caja(world, posCajaPx, scale, texCaja);

    victoria = false;
    derrota = false;
}

void Game::LimpiarEscena() {
    if (caja) { delete caja; caja = nullptr; }
    if (puente) { delete puente; puente = nullptr; }
    if (world) { delete world; world = nullptr; }
}

void Game::Update() {

    if (IsKeyPressed(KEY_R)) {
        InicializarEscena();
        return;
    }

    // Si ya se alcanzó la victoria o la derrota, congelamos la física y los controles
    if (victoria || derrota) return;

    float timeStep = 1.0f / 60.0f;
    world->Step(timeStep, 8, 3);

    // Permitir al jugador controlar la caja
    if (caja) {
        caja->Controlar();

        if (caja->GetX() >= (posDerPx.x - 100.0f)) {

            // Si la caja entra al tramo final de forma descontrolada o choca fuerte
            if (caja->GetVelocidad() > 12.0f) {
                derrota = true;
                return; // Cortamos el flujo inmediatamente
            }

            // Si entra a la plataforma de meta a una velocidad controlada y segura
            if (caja->GetX() >= (posDerPx.x - 30.0f)) {
                victoria = true;
            }
        }
    }
}

void Game::Draw() {
    BeginDrawing();
    ClearBackground(BLACK);

    // 1. Dibujar el fondo adaptado
    if (texFondo.id > 0) {
        Rectangle sourceRec = { 0, 0, (float)texFondo.width, (float)texFondo.height };
        Rectangle destRec = { 0, 0, (float)screenWidth, (float)screenHeight };
        Vector2 origin = { 0, 0 };
        DrawTexturePro(texFondo, sourceRec, destRec, origin, 0.0f, WHITE);
    }

    // 2. Dibujar el entorno físico encima del fondo
    if (puente) puente->Dibujar();
    if (caja) caja->Dibujar();

    // 3. Interfaz de usuario
    DrawRectangle(10, 10, 540, 110, Fade(BLACK, 0.6f));
    DrawText("Mavix - TRABAJO PRACTICO INTEGRADOR", 20, 20, 20, GREEN);
    DrawText("Mecanismo: Puente colgante articulado con tensores elasticos.", 20, 45, 15, WHITE);
    DrawText("FLECHAS (Derecha / Izquierda): Hacer rodar la caja.", 20, 70, 15, RAYWHITE);
    DrawText("Tecla [R]: Reiniciar simulacion por completo.", 20, 90, 15, RAYWHITE);

    // Dimensiones y dibujo del recuadro central para los carteles de estado
    int cartelAncho = 500;
    int cartelAlto = 160;
    int posX = screenWidth / 2 - cartelAncho / 2;
    int posY = screenHeight / 2 - cartelAlto / 2;

    // 4. Cartel de victoria
    if (victoria) {
        DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.4f));

        DrawRectangle(posX, posY, cartelAncho, cartelAlto, RAYWHITE);
        DrawRectangleLines(posX, posY, cartelAncho, cartelAlto, LIME);

        DrawText("PUENTE CRUZADO CON EXITO!", posX + 40, posY + 30, 24, LIME);
        DrawText("La caja llego a destino de forma segura.", posX + 80, posY + 75, 16, DARKGRAY);
        DrawText("Presiona la tecla [R] para volver a jugar.", posX + 85, posY + 105, 16, GRAY);
    }

    // 5. Cartel de derrota
    if (derrota) {
        DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.5f));

        DrawRectangle(posX, posY, cartelAncho, cartelAlto, RAYWHITE);
        DrawRectangleLines(posX, posY, cartelAncho, cartelAlto, RED);

        DrawText("CAJA DESTRUIDA EN EL IMPACTO!", posX + 35, posY + 30, 24, MAROON);
        DrawText("Tene mas cuidado al aproximarte al objetivo.", posX + 65, posY + 75, 16, DARKGRAY);
        DrawText("Presiona la tecla [R] para volver a intentar.", posX + 80, posY + 105, 16, GRAY);
    }

    DrawFPS(screenWidth - 100, 20);
    EndDrawing();
}

void Game::Run() {
    while (!WindowShouldClose()) {
        Update();
        Draw();
    }
}