#pragma once
#include "Grid.h"

class Simulation
{
    Grid* grid;
    Grid* tempGrid;
    bool isPaused = false;

public:
    Simulation(int width, int height, int cellSize)
    {
        grid = new Grid(width, height, cellSize);
        tempGrid = new Grid(width, height, cellSize);
    }
    //void SetCellValue(int row, int column, int value);
    int CountLiveNeighbors(int row, int column);
    void Update();
    bool IsPaused() { return isPaused; }
    void Unpause() { isPaused = true; }
    void Pause() { isPaused = false; }
    void TogglePause();
    void ClearGrid();
    void CreateRandomState();
    void ToggleCell(int row, int column);
    int GetLivingCells();
    Grid* getGrid(){ return grid; }
};
