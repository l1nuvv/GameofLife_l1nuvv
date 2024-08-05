#include <raylib.h>
#include "Simulation.h"

int main()
{
    Color GREY = {29, 29, 29, 255};
    const int WINDOW_WIDTH = 750;
    const int WINDOW_HEIGHT = 750;
    const int CELL_SIZE = 25;
    int FPS = 12;
    
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT,"Game of l1nuvv");
    SetTargetFPS(FPS);
    Simulation Simulation{WINDOW_WIDTH, WINDOW_HEIGHT, CELL_SIZE};

    //Simulation loop
    while(!WindowShouldClose())
    {
        //(1)Event Handling

        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            Vector2 mousePosition = GetMousePosition();
            int row = mousePosition.y / CELL_SIZE;
            int column = mousePosition.x / CELL_SIZE;
            Simulation.ToggleCell(row, column);
        }
        
        if(IsKeyPressed(KEY_ENTER))
        {
            Simulation.Start();
            SetWindowTitle("Game of Life is running... ");
        }
        else if (IsKeyPressed(KEY_SPACE))
        {
            Simulation.Stop();
            SetWindowTitle("Game of Life has stopped... ");
        }

        if(IsKeyPressed(KEY_LEFT_SHIFT))
        {
            FPS += 2;
            SetTargetFPS(FPS);
        }
        else if(IsKeyPressed(KEY_LEFT_CONTROL))
        {
            if(FPS > 5)
            {
                FPS -= 2;
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
        Simulation.Draw();
        EndDrawing();
    }
    
    CloseWindow();
}