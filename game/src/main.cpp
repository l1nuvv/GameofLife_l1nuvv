#include <raylib.h>

#include "raymath.h"
#include "Simulation.h"

int main()
{
    Color GREY = {29, 29, 29, 255};

    const int WINDOW_WIDTH = 1200;
    const int WINDOW_HEIGHT = 800;
    const int CELL_SIZE = 4;
    
    int FPS = 12;
    
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT,"Game of danek-dev");
    SetTargetFPS(FPS);
    Simulation Simulation{WINDOW_WIDTH, WINDOW_HEIGHT, CELL_SIZE};

    //Simulation loop
    while(!WindowShouldClose())
    {

        //(1)Event Handling

        if(GetMouseWheelMove() > 0)
        {
           Simulation.getGrid()->ZoomIn();
        }

        if(GetMouseWheelMove() < 0)
        {
            Simulation.getGrid()->ZoomOut();
        }
        
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            Vector2 mousePosition = GetMousePosition();
            int row = mousePosition.y / CELL_SIZE;
            int column = mousePosition.x / CELL_SIZE;
            Simulation.ToggleCell(row, column);
        }
        
        if(IsKeyPressed(KEY_ENTER))
        {
            Simulation.TogglePause();
        }

        if(IsKeyPressed(KEY_LEFT_SHIFT))
        {
            FPS *= 2;
            SetTargetFPS(FPS);
        }
        else if(IsKeyPressed(KEY_LEFT_CONTROL))
        {
            if(FPS > 5)
            {
                FPS /= 2;
                SetTargetFPS(FPS);
            }
        }

        else if(IsKeyPressed(KEY_R))
        {
            Simulation.CreateRandomState();
        }
        else if(IsKeyPressed(KEY_C))
        {
            Simulation.ClearGrid();
        }

        //(2)Updating State
        Simulation.Update();
        
        //(3)Drawing
        BeginDrawing();
        ClearBackground(GREY);
        Simulation.getGrid()->Draw();
        DrawText(TextFormat("Living cells: %i", Simulation.GetLivingCells()),24,6,31,BLACK);
        DrawText(TextFormat("Living cells: %i", Simulation.GetLivingCells()),25,5,30,GOLD);
        DrawText(TextFormat("FPS: %i",FPS),24,46,32,BLACK);
        DrawText(TextFormat("FPS: %i",FPS),25,45,30,MAGENTA);
        EndDrawing();
    }
    
    CloseWindow();
}