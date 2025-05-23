#include "raylib.h"
#include <cstdlib>
#include <ctime>
#include <cstdio>

enum GameState { //self explanatory.
    wait,
    red,
    green,
    fail,
    results
};

int main() {
    const int w = 888;
    const int h = 666;
    InitWindow(w, h, "Reaction Time - Stavros P.");
    srand(static_cast<unsigned int>(time(0))); //random seed, for timer.
    
    GameState gs = wait;
    double sTime = 0.0;
    double cTime = 0.0;
    double rt = 0.0;
    double rDelay = 0.0;
    bool clicked = false;
    bool early = false;
    
    while (!WindowShouldClose()) {
        switch (gs) {
            case wait: //waits for input, once started generates random delay (2-4s), records start time for delay countdown.
                if (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    gs = red;
                    rDelay = static_cast<double>(rand() % 3 + 2);
                    sTime = GetTime();
                    clicked = false;
                    early = false;
                }
                break;
                
            case red: //gets elapsed time since countdown, fails early if clicked, or changes to green when random delay is reached.
                if (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    early = true;
                    gs = fail;
                    break;
                }
                cTime = GetTime() - sTime;
                if (cTime >= rDelay) {
                    gs = green;
                    sTime = GetTime();
                }
                break;
                
            case green: //elapsed time = reaction time -> takes them to results state.
                cTime = GetTime() - sTime;
                if (!clicked) {
                    if (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                        rt = cTime;
                        gs = results;
                    } else if (cTime > 2.0) {
                        early = false;
                        gs = fail;
                    }
                }
                {
                    char liveT[20];
                    sprintf(liveT, "%.3f", cTime);
                    DrawText(liveT,
                             w/2 - MeasureText(liveT, 33)/2,
                             h/2 + 30,
                             33, WHITE);
                }
                break;

            case fail:  // tells grandpa hes getting slow or jumped early cause hes seeing things.
                if (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    if (early) {
                        gs = red;
                        rDelay = static_cast<double>(rand() % 3 + 2);
                        sTime = GetTime();
                        clicked = false;
                        early = false;
                        break;
                    } else {
                        gs = wait;
                    }
                }
                ClearBackground(BLACK);
                if (early) {
                    DrawText("You jumped the start...",
                             w/2 - MeasureText("You jumped the start...", 30)/2,
                             h/2 - 15,
                             30, WHITE);
                } else {
                    DrawText("You can't be that slow...",
                             w/2 - MeasureText("You can't be that slow...", 30)/2,
                             h/2 - 15,
                             30, WHITE);
                }
                DrawText("Press Space or Click to try again",
                         w/2 - MeasureText("Press Space or Click to try again", 20)/2,
                         h/2 + 30,
                         20, DARKGRAY);
                break;

            case results: //displays results and waits for restart.
                if (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    gs = wait;
                }
                break;
        }
        
        BeginDrawing();
        
        switch (gs) {
            case wait:
                ClearBackground(BLACK);
                DrawText("Press Space or Click to Start",
                         w/2 - MeasureText("Press Space or Click to Start", 30)/2,
                         h/2 - 15,
                         30, RAYWHITE);
                break;
                
            case red:
                ClearBackground(RED);
                {
                    int dotSt = ((int)(GetTime() * 2)) % 4;
                    const char* txt;
                    switch(dotSt) {
                        case 0: txt = "WAIT"; break;
                        case 1: txt = "WAIT."; break;
                        case 2: txt = "WAIT.."; break;
                        default: txt = "WAIT..."; break; // thought it'd be cool
                    }
                    DrawText(txt,
                             w/2 - MeasureText("WAIT...", 60)/2,
                             h/2 - 30,
                             60, WHITE);
                }
                break;
                
            case green:
                ClearBackground(GREEN);
                DrawText("GO!",
                         w/2 - MeasureText("GO!", 60)/2,
                         h/2 - 30,
                         60, WHITE);
                break;
                
            case results:
                ClearBackground(BLACK);
                {
                    char rText[50];
                    sprintf(rText, "Your reaction time: %.3f sec", rt);
                    DrawText(rText,
                             w/2 - MeasureText(rText, 30)/2,
                             h/2 - 15,
                             30, RAYWHITE);
                }
                DrawText("Press Space or Click to try again",
                         w/2 - MeasureText("Press Space or Click to try again", 20)/2,
                         h/2 + 30,
                         20, DARKGRAY);
                break;
        }
        
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}
