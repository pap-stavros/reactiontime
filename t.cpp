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
    InitWindow(w, h, "Reaction Time");
    srand(static_cast<unsigned int>(time(0))); //random seed, for timer.
    
    GameState gs = wait;
    double sTime = 0.0;
    double cTime = 0.0;
    double rt = 0.0;
    double rDelay = 0.0;
    bool clicked = false;
    
    while (!WindowShouldClose()) {
        switch (gs) {
            case wait: //waits for input, once started generates random delay (2-4s), records start time for delay countdown.
                if (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    gs = red;
                    rDelay = static_cast<double>(rand() % 3 + 2);
                    sTime = GetTime();
                    clicked = false;
                }
                break;
                
            case red: //gets elapsed time since countdown, changes to green when random delay is reached, resets timer for measurement.
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
                        gs = fail;
                    }
                }
                char liveT[20];
                sprintf(liveT, "%.3f", cTime);
                DrawText(liveT,
                         w/2 - MeasureText(liveT, 33)/2,
                         h/2 + 30,
                         33, WHITE);
                break;

                
            case fail:  // tells grandpa hes getting slow
                if (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    gs = wait;
                }
                ClearBackground(BLACK);
                DrawText("You can't be that slow...",
                         w/2 - MeasureText("You can't be that slow...", 30)/2,
                         h/2 - 30,
                         30, WHITE);
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
                int dotSt;
                dotSt = ((int)(GetTime() * 2)) % 4;
                const char* txt;
                switch(dotSt) {
                    case 0: txt = "WAIT"; break;
                    case 1: txt = "WAIT."; break;
                    case 2: txt = "WAIT.."; break;
                    case 3: txt = "WAIT..."; break; // thought it'd be cool
                }
                DrawText(txt,
                         w/2 - MeasureText("WAIT...", 60)/2, // if "WAIT..." is replaced with txt, it recenters each time.
                         h/2 - 30,
                         60, WHITE);
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
                char rText[50];
                sprintf(rText, "Your reaction time: %.3f sec", rt);
                DrawText(rText,
                         w/2 - MeasureText(rText, 30)/2,
                         h/2 - 15,
                         30, RAYWHITE);
                DrawText("Press Space or Click to try again",
                         w/2 - MeasureText("Press Space or Click to try again", 20)/2,
                         h/2 + 30,
                         20, RAYWHITE);
                break;
        }
        
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}
