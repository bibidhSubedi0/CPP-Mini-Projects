#include <iostream>
#include <vector>
#include <string>
#include <map>

using std::cin, std::cout, std::endl, std::vector, std::string, std::map;

class table
{
public:
    vector<string> values;
    table()
    {
        for (int i = 0; i < 9; i++)
        {

            values.push_back(".");
        }
    }

    void drawTable()
    {
        cout << "\n";
        for (int i = 0; i < values.size(); i++)
        {
            cout << values[i] << " ";
            if ((i + 1) % 3 == 0)
            {
                cout << "\n";
            }
        }
    }
};

class players
{
public:
    string type;

    players(string type)
    {
        this->type = type;
    }
};

void makeMove(table t, players p, int pos)
{
    t.values[pos] = p.type;
}

bool checkDraw(table t)
{
    for (int i = 0; i < 9; i++)
    {
        if (t.values[i] == ".")
        {

            return false;
        }
    }
    return true;
}

bool checkGameOver(table t, players popen)
{
    for (int i = 0; i < 3; ++i)
    {
        // Check rows
        if (t.values[i * 3] == popen.type && t.values[i * 3] == t.values[i * 3 + 1] && t.values[i * 3 + 1] == t.values[i * 3 + 2])
            return true;
        // Check columns
        if (t.values[i] == popen.type && t.values[i] == t.values[i + 3] && t.values[i + 3] == t.values[i + 6])
            return true;
    }
    // Check diagonals
    if (t.values[0] == popen.type && t.values[0] == t.values[4] && t.values[4] == t.values[8])
        return true;
    if (t.values[2] == popen.type && t.values[2] == t.values[4] && t.values[4] == t.values[6])
        return true;

    return false;
}

int miniMax(table &t1, bool isMaximizer, int depth, players p1, players p2)
{
    map<string, int> lookup = {{"X", 1}, {"T", 0}, {"O", -1}};
    string winner = "null";
    if (checkGameOver(t1, p1))
        winner = "X";
    if (checkGameOver(t1, p2))
        winner = "Y";
    if (checkDraw(t1))
        winner = "T";

    if (winner != "null")
    {
        return lookup[winner];
    }

    if (isMaximizer)
    {
        int bestscore = -2;
        for (int i = 0; i < 9; i++)
        {
            if (t1.values[i] == ".") // Spot is avialable
            {
                t1.values[i] = p1.type;
                int score = miniMax(t1, !isMaximizer, depth + 1, p1, p2);
                t1.values[i] = ".";
                if (score > bestscore)
                {
                    bestscore = score;
                }
            }
        }
        return bestscore;
    }
    else
    {
        int bestscore = 2;
        for (int i = 0; i < 9; i++)
        {

            if (t1.values[i] == ".") // Spot is avialable
            {
                t1.values[i] = p2.type;
                int score = miniMax(t1, !isMaximizer, depth + 1, p1, p2);
                t1.values[i] = ".";

                if (score < bestscore)
                    bestscore = score;
            }
        }
        return bestscore;
    }
}

void p1Turn(table &t1, players p)
{
    int pos;
    string toPut = "X";
    do
    {
        cout << "X" << "'s turn : ";
        cin >> pos;
    } while (t1.values[pos] != ".");
    t1.values[pos] = toPut;
}

void p2Turn(table &t1, players p1, players p2) // bot
{
    // Can second player win if he does not play the center in his first move? Spoiler No.
    // int ctr = 0;
    // for (int i = 0; i < 9; i++)
    // {
    //     if (t1.values[i] != ".")
    //         ctr++;
    // }
    // if (ctr == 1)
    // {
    //     t1.values[8] = p2.type;
    //     return;
    // }

    int optimalPos;
    int bestScore = INT8_MAX;
    for (int i = 0; i < 9; i++)
    {
        if (t1.values[i] == ".")
        {
            t1.values[i] = p2.type;
            int Score = miniMax(t1, 1, 0, p1, p2);

            if (Score < bestScore)
            {
                optimalPos = i;
                bestScore = Score;
            }
            t1.values[i] = ".";
        }
    }

    t1.values[optimalPos] = p2.type;
    return;
}

int main()
{
    table t1;
    players px("X");
    players po("O");
    t1.drawTable();
    bool turn = 1; // 1=> maximizers turn || x's turn 0=> minimizersTurn || o's turn
    while (1 || !checkGameOver(t1, po) || !checkDraw(t1))
    {
        if (turn == 1)
        {
            p1Turn(t1, px);
        }
        else
        {
            p2Turn(t1, px, po);
        }

        t1.drawTable();
        if (checkGameOver(t1, px))
        {
            cout << px.type << " Is winner";
            break;
        }
        if (checkGameOver(t1, po))
        {
            cout << po.type << " Is winner";
            break;
        }
        if (checkDraw(t1))
        {
            cout << "Draw";
            break;
        }
        turn = !turn;
    }
}