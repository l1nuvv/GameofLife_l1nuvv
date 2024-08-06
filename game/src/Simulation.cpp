#include <vector>
#include <utility>
#include "Simulation.h"

#include "raylib.h"

int Simulation::CountLiveNeighbors(int row, int column)
{
    int liveNeighbors = 0;
    std::vector<std::pair<int, int>> neighborsOffsets =
    {
        {-1 ,0}, //Directly above
        {1, 0},  //Directly below
        {0, -1}, //To the left
        {0, 1},  //To the right
        {-1, -1},//Diagonal upper left
        {-1, 1}, //Diagonal upper right
        {1, -1}, //Diagonal lower left
        {1, 1}   //Diagonal lower right
    };

    for(const auto& offset : neighborsOffsets)
    {
        int neighborRow = (row + offset.first + grid->GetRows()) % grid->GetRows();
        int neighborColumn = (column + offset.second + grid->GetColumns()) % grid->GetColumns();
        liveNeighbors += grid->GetValue(neighborRow, neighborColumn);
    }
   return liveNeighbors; 
}

void Simulation::Update()
{
    if(IsPaused())
    {
        for(int row = 0; row < grid->GetRows(); row++)
        {
            for(int column = 0; column < grid->GetColumns(); column++)
            {
                int liveNeighbors = CountLiveNeighbors(row, column);
                int cellValue = grid->GetValue(row, column);

                if(cellValue == 1)
                {
                    if(liveNeighbors > 3 || liveNeighbors < 2)
                    {
                        tempGrid->SetValue(row, column, 0);
                    }
                    else
                    {
                        tempGrid->SetValue(row, column, 1);
                    }
                }
                else if(liveNeighbors == 3)
                {
                    tempGrid->SetValue(row, column, 1);
                }
                else
                {
                    tempGrid->SetValue(row, column, 0);
                }
            }
        }
        grid = tempGrid;
    }
}

void Simulation::TogglePause()
{
    isPaused = !isPaused;
    if(isPaused)
    {
        SetWindowTitle("Game of Life is running... ");
        return;
    }
    SetWindowTitle("Game of Life has stopped... ");
}

void Simulation::ClearGrid()
{
    if(!IsPaused())
    {
        grid->Clear();
    }
}

void Simulation::CreateRandomState()
{
    if(!IsPaused())
    {
        grid->FillRandom();
    }
}

void Simulation::ToggleCell(int row, int column)
{
    if(!IsPaused())
    {
        grid->ToggleCell(row, column);
    }
}

int Simulation::GetLivingCells()
{
    int liveCells = 0;
    for(int row = 0; row < grid->GetRows(); row++)
    {
        for(int column = 0; column < grid->GetColumns(); column++)
        {
           liveCells += grid->GetValue(row, column);
        }
    }
    return liveCells;
}

