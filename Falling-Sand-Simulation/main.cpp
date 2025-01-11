#include <raylib.h>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

const int winWidth = 400;
const int winHeight = 400;
const int targetFPS = 100;
const double deltaTime = 0.01;

struct position
{
    int xpos;
    int ypos;

    position(int xpos, int ypos)
    {
        this->xpos = xpos;
        this->ypos = ypos;
    }
};

void updatePosition(vector<Rectangle> &recs, vector<vector<int>> &grid)
{
    for (int i = 0; i < recs.size(); i++)
    {
        if (recs[i].y + 1 < winHeight)
        {

            // Sida sida tala janxa khuru khuru
            if (grid[recs[i].x][recs[i].y + 1] == 0)
            {
                grid[recs[i].x][recs[i].y] = 0;
                grid[recs[i].x][recs[i].y + 1] = 1;
                recs[i].y += 1;
            }

            // If tesko left ma khali xa right ma xaina
            else if ((grid[recs[i].x - 1][recs[i].y + 1] == 0) && (grid[recs[i].x + 1][recs[i].y + 1] != 0))
            {
                grid[recs[i].x][recs[i].y] = 0;
                grid[recs[i].x - 1][recs[i].y + 1] = 1;
                recs[i].x -= 1;
                recs[i].y += 1;
            }

            // If tesko right ma khali xa left ma xaina

            else if ((grid[recs[i].x - 1][recs[i].y + 1] != 0) && (grid[recs[i].x + 1][recs[i].y + 1] == 0))
            {
                grid[recs[i].x][recs[i].y] = 0;
                grid[recs[i].x + 1][recs[i].y + 1] = 1;
                recs[i].x += 1;
                recs[i].y += 1;
            }

            // If tesko left / Right both ma khali xa -> Prioritize Left falling
            else if ((grid[recs[i].x - 1][recs[i].y + 1] == 0) && (grid[recs[i].x + 1][recs[i].y + 1] == 0))
            {
                grid[recs[i].x][recs[i].y] = 0;
                grid[recs[i].x - 1][recs[i].y + 1] = 1;
                recs[i].x -= 1;
                recs[i].y += 1;
            }
        }
    }
}

int main()
{
    InitWindow(winWidth, winHeight, "Sand");
    SetTargetFPS(targetFPS);

    vector<vector<int>> grid;
    for (int i = 0; i < winWidth; i++)
    {
        vector<int> temp;
        for (int j = 0; j < winHeight; j++)
        {
            temp.push_back(0);
        }
        grid.push_back(temp);
    }

    vector<Rectangle> recs;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        for (int i = 0; i < recs.size(); i++)
        {
            DrawRectangleRec(recs[i], WHITE);
        }
        updatePosition(recs, grid);

        if (IsMouseButtonDown(0))
        {
            Rectangle rect = {GetMousePosition().x, GetMousePosition().y, 1, 1};
            recs.push_back(rect);
            grid[rect.x][rect.y] = 1;
        }

        ClearBackground(BLACK);
        EndDrawing();
    }
}
