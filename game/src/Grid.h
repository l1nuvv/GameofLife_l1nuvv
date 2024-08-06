#pragma once
#include <vector>

#define minCellSize 4

class Grid
{
    int rows;
    int columns;
    int cellSize;
    std::vector<std::vector<int>> cells;
public:
    Grid(int width, int height, int cellSize)
    : rows(height / minCellSize), columns(width / minCellSize), cellSize(cellSize), cells(rows, std::vector(columns, 0)){}
    void Draw();
    void SetValue(int row, int column, int value);
    int GetValue(int row, int column);
    bool IsWithInBounds(int row, int column);
    int GetRows() { return rows;}
    int GetColumns() { return columns; }
    void FillRandom();
    void Clear();
    void ToggleCell(int row, int column);
    void ZoomIn();
    void ZoomOut();
};
