#include <iostream>
#include <raylib.h>
#include <vector>
using std::cout, std::cin, std::endl, std::vector;

const int width = 600;
const int height = 600;
int totalRocks = 10;
int totalPapers = 10;
int totalScissor = 10;

class Rocks
{
public:
    Vector2 position;
    Vector2 velocity;
    Image rock;
    Texture2D rockText;

    Rocks()
    {
        velocity = {(float)GetRandomValue(-3,3),(float)GetRandomValue(-3,3)};
    }

    void setValueRocks()
    {
        rock = LoadImage("r.png");
        rockText = LoadTextureFromImage(rock);
    }

    void displayRocks()
    {
        DrawTexture(rockText, position.x, position.y, WHITE);
    }
    void checkCollosionWithWall()
    {
        int size = 20;
        if (((position.x + size) >= width && velocity.x > 0) || ((position.x - size) <= 0 && velocity.x < 0))
        {
            velocity.x = -velocity.x;
        }
        if (((position.y + size) >= height && velocity.y > 0) || ((position.y - size) <= 0 && velocity.y < 0))
        {
            velocity.y = -velocity.y;
        }
    }

    void updatePosition()
    {
        position.x += velocity.x;
        position.y += velocity.y;
        checkCollosionWithWall();
    }
};

class Papers
{
public:
    Vector2 position;
    Image paper;
    Texture2D paperText;
    Vector2 velocity;

    Papers()
    {
        velocity = {(float)GetRandomValue(-3,3),(float)GetRandomValue(-3,3)};
    }

    void setValuepapers()
    {
        paper = LoadImage("p.png");
        paperText = LoadTextureFromImage(paper);
    }

    void displaypapers()
    {
        DrawTexture(paperText, position.x, position.y, WHITE);
    }
    void checkCollosionWithWall()
    {
        int size = 20;
        if (((position.x + size) >= width && velocity.x > 0) || ((position.x - size) <= 0 && velocity.x < 0))
        {
            velocity.x = -velocity.x;
        }
        if (((position.y + size) >= height && velocity.y > 0) || ((position.y - size) <= 0 && velocity.y < 0))
        {
            velocity.y = -velocity.y;
        }
    }
    void updatePosition()
    {
        position.x += velocity.x;
        position.y += velocity.y;
        checkCollosionWithWall();
    }
};

class Scissors
{
public:
    Vector2 position;
    Image Scissor;
    Texture2D ScissorText;
    Vector2 velocity;

    Scissors()
    {
        velocity = {(float)GetRandomValue(-3,3),(float)GetRandomValue(-3,3)};
    }

    void setValueScissors()
    {
        Scissor = LoadImage("s.png");
        ScissorText = LoadTextureFromImage(Scissor);
    }

    void displayScissors()
    {
        DrawTexture(ScissorText, position.x, position.y, WHITE);
    }
    void checkCollosionWithWall()
    {
        int size = 20;
        if (((position.x + size) >= width && velocity.x > 0) || ((position.x - size) <= 0 && velocity.x < 0))
        {
            velocity.x = -velocity.x;
        }
        if (((position.y + size) >= height && velocity.y > 0) || ((position.y - size) <= 0 && velocity.y < 0))
        {
            velocity.y = -velocity.y;
        }
    }
    void updatePosition()
    {
        position.x += velocity.x;
        position.y += velocity.y;
        checkCollosionWithWall();
    }
};

void checkCollisionRockPaper(vector<Rocks> &rcarrier, vector<Papers> &pcarrier)
{
    float size = 20;
    for (int rs = 0; rs < rcarrier.size(); rs++)
    {
        for (int ps = 0; ps < pcarrier.size(); ps++)
        {
            Rectangle r1 = {rcarrier[rs].position.x, rcarrier[rs].position.y, size, size};
            Rectangle r2 = {pcarrier[ps].position.x, pcarrier[ps].position.y, size, size};
            if (CheckCollisionRecs(r1, r2))
            {
                Papers newP;
                newP.position = pcarrier[ps].position;
                newP.setValuepapers();
                pcarrier.push_back(newP);
                rcarrier.erase(rcarrier.begin() + rs);
                break;
            }
        }
    }
}

void checkCollisionRockScissor(vector<Rocks> &rcarrier, vector<Scissors> &scarrier)
{
    float size = 20;
    for (int ss = 0; ss < scarrier.size(); ss++)
    {
        for (int rs = 0; rs < rcarrier.size(); rs++)
        {
            Rectangle r1 = {rcarrier[rs].position.x, rcarrier[rs].position.y, size, size};
            Rectangle r2 = {scarrier[ss].position.x, scarrier[ss].position.y, size, size};
            if (CheckCollisionRecs(r1, r2))
            {
                Rocks newR;
                newR.position=rcarrier[rs].position;
                newR.setValueRocks();
                rcarrier.push_back(newR);
                scarrier.erase(scarrier.begin() + ss);
                break;
            }
        }
    }

}


void checkCollisionPaperScissors(vector<Papers> &pcarrier, vector<Scissors> &scarrier)
{
    float size = 20;
    for (int rs = 0; rs < pcarrier.size(); rs++)
    {
        for (int ss = 0; ss < scarrier.size(); ss++)
        {
            Rectangle r1 = {pcarrier[rs].position.x, pcarrier[rs].position.y, size, size};
            Rectangle r2 = {scarrier[ss].position.x, scarrier[ss].position.y, size, size};
            if (CheckCollisionRecs(r1, r2))
            {

                Scissors newR;
                newR.position = pcarrier[rs].position;
                newR.setValueScissors();
                scarrier.push_back(newR);
                pcarrier.erase(pcarrier.begin() + rs);
                break;
            }
        }
    }
}

int main()
{
    InitWindow(width, height, "Scissor Paper Rock");
    SetTargetFPS(60);

    vector<Rocks> r;
    vector<Papers> p;
    vector<Scissors> s;

    for (int i = 0; i < totalRocks; i++)
    {
        float randValuex = GetRandomValue(25, width - 25);
        float randValueY = GetRandomValue(25, height - 25);
        Vector2 postion = {randValuex, randValueY};

        Rocks ri;
        ri.position = postion;
        ri.setValueRocks();
        r.push_back(ri);
    }

    for (int i = 0; i < totalPapers; i++)
    {
        float randValuex = GetRandomValue(25, width - 25);
        float randValueY = GetRandomValue(25, height - 25);
        Vector2 postion = {randValuex, randValueY};
        Papers pi;
        pi.position = postion;
        pi.setValuepapers();
        p.push_back(pi);
    }

    for (int i = 0; i < totalScissor; i++)
    {
        float randValuex = GetRandomValue(25, width - 25);
        float randValueY = GetRandomValue(25, height - 25);
        Vector2 postion = {randValuex, randValueY};
        Scissors si;
        si.position = postion;
        si.setValueScissors();
        s.push_back(si);
    }

    while (!WindowShouldClose())
    {
        BeginDrawing();

        for (int i = 0; i < r.size(); i++)
        {
            r[i].displayRocks();
            r[i].updatePosition();
        }
        for (int i = 0; i < p.size(); i++)
        {
            p[i].displaypapers();
            p[i].updatePosition();
        }
        for (int i = 0; i < s.size(); i++)
        {
            s[i].displayScissors();
            s[i].updatePosition();
        }

        checkCollisionRockPaper(r, p);
        checkCollisionRockScissor(r, s);
        checkCollisionPaperScissors(p,s);


        ClearBackground(BLACK);
        EndDrawing();
    }
}