#include "Game.h"

Game::Game() {
    InitWindow(screenWidth, screenHeight, "Mavix - TP 2: Mecanismo Automatizado por Eventos");
    SetTargetFPS(60);

    texPersonaje = LoadTexture("resources/personaje.png");
    texPlataforma = LoadTexture("resources/plataforma.png");
    texAscensor = LoadTexture("resources/ascensor.png");
    texMeta = LoadTexture("resources/meta.png");

    world = nullptr;
    contactListener = nullptr;
    personaje = nullptr;
    ascensor = nullptr;
    metaSensor = nullptr;

    InicializarEscena();
}

Game::~Game() {
    LimpiarEscena();

    UnloadTexture(texPersonaje);
    UnloadTexture(texPlataforma);
    UnloadTexture(texAscensor);
    UnloadTexture(texMeta);

    CloseWindow();
}

void Game::InicializarEscena() {
    LimpiarEscena();

    b2Vec2 gravity(0.0f, 16.0f);
    world = new b2World(gravity);

    victoria = false;
    estadoActual = STATE_PLAYING;

    Plataforma* suelo = new Plataforma(world, Vector2{ 512.0f, 740.0f }, scale, 35.0f, 1.5f, texPlataforma);
    plataformas.push_back(suelo);

    b2Body* cuerpoSuelo = world->GetBodyList();

    plataformas.push_back(new Plataforma(world, Vector2{ 220.0f, 600.0f }, scale, 4.0f, 0.8f, texPlataforma));
    plataformas.push_back(new Plataforma(world, Vector2{ 250.0f, 250.0f }, scale, 10.0f, 0.8f, texPlataforma));

    ascensor = new Ascensor(world, cuerpoSuelo, Vector2{ 540.0f, 480.0f }, scale, 4.5f, 0.6f, texAscensor);

    personaje = new Personaje(world, Vector2{ 440.0f, 480.0f }, scale, 1.2f, 1.8f, texPersonaje);

    b2BodyDef metaDef;
    metaDef.type = b2_staticBody;
    metaDef.position.Set(180.0f / scale, 180.0f / scale);
    metaSensor = world->CreateBody(&metaDef);

    b2PolygonShape metaBox;
    metaBox.SetAsBox(1.5f / 2.0f, 1.5f / 2.0f);

    b2FixtureDef metaFixture;
    metaFixture.shape = &metaBox;
    metaFixture.isSensor = true;
    metaSensor->CreateFixture(&metaFixture);
    metaSensor->GetUserData().pointer = (uintptr_t)TIPO_META;

    contactListener = new MyContactListener(ascensor, victoria);
    world->SetContactListener(contactListener);
}

void Game::LimpiarEscena() {
    if (contactListener) { delete contactListener; contactListener = nullptr; }
    if (personaje) { delete personaje; personaje = nullptr; }
    if (ascensor) { delete ascensor; ascensor = nullptr; }

    metaSensor = nullptr;

    for (auto p : plataformas) {
        delete p;
    }
    plataformas.clear();

    if (world) { delete world; world = nullptr; }
}

void Game::Update() {
    if (IsKeyPressed(KEY_R)) {
        InicializarEscena();
        return;
    }

    if (estadoActual == STATE_VICTORY) return;

    if (personaje) personaje->Controlar();

    if (world) {
        world->Step(1.0f / 60.0f, 8, 3);
    }

    if (victoria) {
        estadoActual = STATE_VICTORY;
    }
}

void Game::Draw() {
    BeginDrawing();
    ClearBackground(GetColor(0x1a233aFF));

    for (size_t i = 0; i < plataformas.size(); i++) {
        if (i == 0) {
    .
            DrawRectangle(0, 740 - 22, screenWidth, 45, GREEN);
        }
        else {

            plataformas[i]->Draw();
        }
    }

    if (ascensor) ascensor->Dibujar();

    if (metaSensor != nullptr) {
        b2Vec2 posMeta = metaSensor->GetPosition();
        float anchoPx = 1.5f * scale;
        float altoPx = 1.5f * scale;

        Rectangle sourceRec = { 0.0f, 0.0f, (float)texMeta.width, (float)texMeta.height };
        Rectangle destRec = { posMeta.x * scale, posMeta.y * scale, anchoPx, altoPx };
        Vector2 origin = { anchoPx / 2.0f, altoPx / 2.0f };

        DrawTexturePro(texMeta, sourceRec, destRec, origin, 0.0f, Fade(GREEN, 0.8f));
        DrawText("META", (int)(posMeta.x * scale) - 20, (int)(posMeta.y * scale) - 40, 16, GREEN);
    }

    if (personaje) personaje->Dibujar();

    DrawRectangle(15, 15, 480, 95, Fade(BLACK, 0.6f));
    DrawText("MAVIX - TP 2: ACTIVADOR DE MECANISMO (U4)", 25, 25, 16, GOLD);
    DrawText("- FLECHAS (Izquierda/Derecha) para caminar. [ESPACIO] para saltar.", 25, 50, 13, WHITE);
    DrawText("- Parate en el ascensor para activar el PrismaticJoint de subida.", 25, 70, 13, LIGHTGRAY);
    DrawText("- Tecla [R]: Reiniciar nivel.", 25, 88, 12, RAYWHITE);

    if (estadoActual == STATE_VICTORY) {
        DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.75f));

        int cAncho = 520;
        int cAlto = 160;
        int px = screenWidth / 2 - cAncho / 2;
        int py = screenHeight / 2 - cAlto / 2;

        DrawRectangle(px, py, cAncho, cAlto, RAYWHITE);
        DrawRectangleLines(px, py, cAncho, cAlto, LIME);

        DrawText("¡DESAFIO COMPLETADO CON EXITO!", px + 35, py + 30, 22, LIME);
        DrawText("Presioná la tecla [R] para volver a jugar.", px + 120, py + 110, 15, GRAY);
    }

    DrawFPS(screenWidth - 90, 25);
    EndDrawing();
}

void Game::Run() {
    while (!WindowShouldClose()) {
        Update();
        Draw();
    }
}