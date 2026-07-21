#include <iostream>
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

int main(void){
    const int screenWidth = 800;
    const int screenHeight = 450;

    float playerX = screenWidth / 2;
    float playerY = screenHeight / 2;

    SetTraceLogLevel(LOG_WARNING);

    InitWindow(screenWidth, screenHeight, "Brodilka game");

    int coins = 0;
    float coinX = GetRandomValue(20, screenWidth - 20);
    float coinY = GetRandomValue(20, screenHeight - 20);

    int currentSkin = 0;
    bool skin1_bought = false;
    bool skin2_bought = false;
    bool skin3_bought = false;

    Image img1 = LoadImage("textures/1.png");
    ImageResize(&img1, 70, 70);
    Texture2D textureCoin1 = LoadTextureFromImage(img1);
    UnloadImage(img1);

    Image img2 = LoadImage("textures/2.png");
    ImageResize(&img2, 70, 70);
    Texture2D textureCoin2 = LoadTextureFromImage(img2);
    UnloadImage(img2);

    Image img3 = LoadImage("textures/3.png");
    ImageResize(&img3, 70, 70);
    Texture2D textureCoin3 = LoadTextureFromImage(img3);
    UnloadImage(img3);


    int gameState = 0;

    float fps = 60;

    SetTargetFPS(fps);

    while (!WindowShouldClose()){

        if(gameState == 0){
            if (IsKeyDown(KEY_D) && playerX < screenWidth) playerX += 2.0f;
            if (IsKeyDown(KEY_A) && playerX > 0) playerX -= 2.0f;
            if (IsKeyDown(KEY_W) && playerY > 0) playerY -= 2.0f;
            if (IsKeyDown(KEY_S) && playerY < screenHeight) playerY += 2.0f;

            if (CheckCollisionCircles({playerX, playerY}, 20, {coinX, coinY}, 15)) {
                coins++;
                coinX = GetRandomValue(20, screenWidth - 20);
                coinY = GetRandomValue(20, screenHeight - 20);
            }
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);

            if(gameState == 0){
                switch(currentSkin){
                    case 0:
                        DrawCircle(coinX, coinY, 15, YELLOW);
                        break;
                    case 1:
                        DrawTexturePro(
                            textureCoin1, 
                            {0.0f, 0.0f, (float)textureCoin1.width, (float)textureCoin1.height},
                            {coinX - 15, coinY - 15, 40.0f, 40.0f},
                            {0.0f, 0.0f},
                            0.0f,
                            WHITE
                        );
                        break;
                    case 2:
                        DrawTexturePro(
                            textureCoin2, 
                            {0.0f, 0.0f, (float)textureCoin2.width, (float)textureCoin2.height},
                            {coinX - 15, coinY - 15, 50.0f, 50.0f},
                            {0.0f, 0.0f},
                            0.0f,
                            WHITE
                        );
                        break;
                    case 3:
                        DrawTexturePro(
                            textureCoin3, 
                            {0.0f, 0.0f, (float)textureCoin2.width, (float)textureCoin2.height},
                            {coinX - 15, coinY - 15, 40.0f, 40.0f},
                            {0.0f, 0.0f},
                            0.0f,
                            WHITE
                        );
                        break;
                }
                DrawCircle(playerX, playerY, 20, DARKBLUE);
                

                if (GuiButton({(float)5, screenHeight - 45, 40, 40}, "#141#")){
                    gameState = 1;
                }

                if (GuiButton({(float)50, screenHeight - 45, 40, 40 }, "#146#")){
                    gameState = 2;
                }

                DrawFPS(screenWidth - 100, 10);
                int textWidth = MeasureText(TextFormat("Coins: %i", coins), 20);
                DrawText(TextFormat("Coins: %i", coins), screenWidth / 2 - textWidth / 2, 5, 20, GRAY);
                DrawText("Esc for leave", 5, 5, 20, LIGHTGRAY);
            } else if(gameState == 1){
                int titleWidth = MeasureText("SETTINGS MENU", 30);
                
                DrawText("SETTINGS MENU", screenWidth / 2 - titleWidth / 2, 10, 30, DARKGRAY);

                DrawText(TextFormat("Target FPS: %.0f", fps), screenWidth / 2 - 100, screenHeight / 2 - 85, 20, DARKGRAY);
                GuiSlider({screenWidth / 2 - 100, screenHeight / 2 - 60, 200, 20}, NULL, NULL, &fps, 30.0f, 250.0f);

                SetTargetFPS((int)fps);

                if (GuiButton({screenWidth / 2 - 100, screenHeight / 2 - 20, 200, 40}, "Back to Game")) {
                    gameState = 0;
                }
            } else{
                int titleWidth = MeasureText("SHOP", 30);
                
                DrawText("SHOP", screenWidth / 2 - titleWidth / 2, 10, 30, DARKGRAY);

                DrawText(TextFormat("Your Coins: %i", coins), 20, 20, 20, GOLD);
                
                float startX = (screenWidth - (150 * 3 + 40 * 2)) / 2;

                float x1 = startX;
                DrawRectangleLinesEx({x1, 90, 150, 180}, 3, BLACK);
                DrawText("50", x1 + 75 - MeasureText("50", 20)/2, 100, 20, BLACK);
                
                DrawTextureV(textureCoin1, {x1 + 40, 135}, WHITE);
                
                const char* textBtn1 = skin1_bought ? (currentSkin == 1 ? "Equipped" : "Equip") : "buy";
                if (GuiButton({x1, 235, 150, 35}, textBtn1)){
                    if (!skin1_bought && coins >= 50) {coins -= 50; skin1_bought = true; currentSkin = 1;}
                    else if (skin1_bought) currentSkin = 1;
                }

                float x2 = startX + 190;
                DrawRectangleLinesEx({x2, 90, 150, 180}, 3, BLACK);
                DrawText("150", x2 + 75 - MeasureText("150", 20)/2, 90 + 10, 20, BLACK);
                
                DrawTextureV(textureCoin2, { x2 + 40, 90 + 45 }, WHITE);
                
                const char* textBtn2 = skin2_bought ? (currentSkin == 2 ? "Equipped" : "Equip") : "buy";
                if (GuiButton({x2, 235, 150, 35}, textBtn2)){
                    if (!skin2_bought && coins >= 150) {coins -= 150; skin2_bought = true; currentSkin = 2;}
                    else if (skin2_bought) currentSkin = 2;
                }

                float x3 = startX + 380;
                DrawRectangleLinesEx({x3, 90, 150, 180}, 3, BLACK);
                DrawText("300", x3 + 75 - MeasureText("300", 20)/2, 90 + 10, 20, BLACK);
                
                DrawTextureV(textureCoin3, {x3 + 40, 135}, WHITE);
                
                const char* textBtn3 = skin3_bought ? (currentSkin == 3 ? "Equipped" : "Equip") : "buy";
                if (GuiButton({x3, 235, 150, 35}, textBtn3)){
                    if (!skin3_bought && coins >= 300) {coins -= 300; skin3_bought = true; currentSkin = 3;}
                    else if (skin3_bought) currentSkin = 3;
                }

                if (GuiButton({screenWidth / 2 - 100, screenHeight - 90, 200, 40}, "Default skin")){
                    currentSkin = 0;
                }

                if (GuiButton({screenWidth / 2 - 100, screenHeight - 45, 200, 40}, "Back to Game")){
                    gameState = 0;
                }
            }

        EndDrawing();
    }

    UnloadTexture(textureCoin1);
    UnloadTexture(textureCoin2);
    UnloadTexture(textureCoin3);
    CloseWindow();

    return 0;
}