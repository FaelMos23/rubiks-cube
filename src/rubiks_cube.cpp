#include <iostream>
#include <sstream>
#include <chrono>
#include <random>
#include <list>
#include <stack>
#define N 2
using namespace std;

const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string RED = "\033[31m";
const string WHITE = "\033[37m";
const string BLUE = "\033[34m";
const string ORANGE = "\033[38;5;208m";
const string RESET = "\033[0m";

string int_to_string(int);
// void oppos_parallel_rots(int, int*, int*);
int oppos_rot(int);
void translation(uint8_t sides[6][N][N], bool isClockwise, int face);
string int_to_rot_name(int);

class Cube;

class CubeInfo
{
public:
    CubeInfo *prevCube;
    uint8_t lastRot;

    // constructors
    CubeInfo()
    {
        prevCube = NULL; // this is the first cube
        lastRot = -1;    // there was no rotation to get here
    }

    CubeInfo(Cube *prev);

    void copyInfo(CubeInfo original)
    {
        prevCube = original.prevCube;
        lastRot = original.lastRot;
    }

    void copyFromCube(Cube original);
};

class Cube
{
public:
    // attr
    uint8_t sides[6][N][N];
    CubeInfo *prevCube;
    uint8_t lastRot;

    // constructors
    Cube()
    { // starts a cube with the values on the right place
        int i, j, k;

        for (i = 0; i < 6; i++)
            for (j = 0; j < N; j++)
                for (k = 0; k < N; k++)
                {
                    sides[i][j][k] = i;
                }

        prevCube = NULL; // this is the first cube
        lastRot = -1;    // there was no rotation to get here
    }

    // makes a copied cube
    Cube(Cube const &original)
    { // starts a cube with the values on the right place
        int i, j, k;

        for (i = 0; i < 6; i++)
            for (j = 0; j < N; j++)
                for (k = 0; k < N; k++)
                {
                    sides[i][j][k] = original.sides[i][j][k];
                }

        prevCube = original.prevCube;
        lastRot = original.lastRot;
    }

    // method needed for constructor below, also used on shuffle
    void single_rotation(int rot)
    {
        switch (rot)
        {
        case 0:
            f();
            break;
        case 1:
            f_l();
            break;
        case 2:
            r();
            break;
        case 3:
            r_l();
            break;
        case 4:
            t();
            break;
        case 5:
            t_l();
            break;
        default:
            break;
        }
    }

    // constructor that copies another cube then rotates it
    // Cube(CubeInfo *prev, int rot)
    //{ // creates a cube based on a previous one
    //  int i, j, k;
    //
    //   for (i = 0; i < 6; i++)
    //       for (j = 0; j < N; j++)
    //           for (k = 0; k < N; k++)
    //           {
    //                sides[i][j][k] = (*prev).sides[i][j][k];
    //          }
    //
    //   single_rotation(rot);
    //
    //    prevCube = prev; // points to the cube that originated this one
    //    lastRot = rot;   // saves the last rotation
    //}

    Cube(CubeInfo *past, Cube *processing, int rot)
    {
        int i, j, k;

        for (i = 0; i < 6; i++)
            for (j = 0; j < N; j++)
                for (k = 0; k < N; k++)
                {
                    sides[i][j][k] = (*processing).sides[i][j][k];
                }

        single_rotation(rot);

        prevCube = past;
        lastRot = rot;
    }

    // methods
    // direct 2x2 print, will make it better later
    void print_cube()
    {
        cout << "  " << int_to_string(sides[0][0][0]) << int_to_string(sides[0][0][1]) << endl;
        cout << "  " << int_to_string(sides[0][1][0]) << int_to_string(sides[0][1][1]) << endl;
        cout << int_to_string(sides[1][0][0]) << int_to_string(sides[1][0][1]) << int_to_string(sides[2][0][0]) << int_to_string(sides[2][0][1]) << int_to_string(sides[3][0][0]) << int_to_string(sides[3][0][1]) << endl;
        cout << int_to_string(sides[1][1][0]) << int_to_string(sides[1][1][1]) << int_to_string(sides[2][1][0]) << int_to_string(sides[2][1][1]) << int_to_string(sides[3][1][0]) << int_to_string(sides[3][1][1]) << endl;
        cout << "  " << int_to_string(sides[4][0][0]) << int_to_string(sides[4][0][1]) << endl;
        cout << "  " << int_to_string(sides[4][1][0]) << int_to_string(sides[4][1][1]) << endl;
        cout << "  " << int_to_string(sides[5][0][0]) << int_to_string(sides[5][0][1]) << endl;
        cout << "  " << int_to_string(sides[5][1][0]) << int_to_string(sides[5][1][1]) << "\n"
             << endl;
    }

    // rotation methods

    void f() // rotate front clockwise  6
    {
        uint8_t buffer[N];
        // bottom layer of TOP
        buffer[0] = sides[0][1][0];
        buffer[1] = sides[0][1][1];

        // left layer of RIGHT
        swap(buffer[0], sides[3][0][0]);
        swap(buffer[1], sides[3][1][0]);

        // top layer of BOTTOM
        swap(buffer[0], sides[4][0][1]);
        swap(buffer[1], sides[4][0][0]);

        // right layer of LEFT
        swap(buffer[0], sides[1][1][1]);
        swap(buffer[1], sides[1][0][1]);

        sides[0][1][0] = buffer[0];
        sides[0][1][1] = buffer[1];

        // translation

        translation(sides, true, 2);
    }

    void f_l() // rotate front counterclockwise  7
    {
        uint8_t buffer[N];
        // bottom layer of TOP
        buffer[0] = sides[0][1][0];
        buffer[1] = sides[0][1][1];

        // right layer of LEFT
        swap(buffer[0], sides[1][1][1]);
        swap(buffer[1], sides[1][0][1]);

        // top layer of BOTTOM
        swap(buffer[0], sides[4][0][1]);
        swap(buffer[1], sides[4][0][0]);

        // left layer of RIGHT
        swap(buffer[0], sides[3][0][0]);
        swap(buffer[1], sides[3][1][0]);

        sides[0][1][0] = buffer[0];
        sides[0][1][1] = buffer[1];

        // translation

        translation(sides, false, 2);
    }

    void r() // rotate right clockwise  2
    {
        uint8_t buffer[N];
        // right layer of TOP
        buffer[0] = sides[0][0][1];
        buffer[1] = sides[0][1][1];

        // right layer of BEHIND
        swap(buffer[0], sides[5][0][1]);
        swap(buffer[1], sides[5][1][1]);

        // right layer of BOTTOM
        swap(buffer[0], sides[4][0][1]);
        swap(buffer[1], sides[4][1][1]);

        // right layer of FRONT
        swap(buffer[0], sides[2][0][1]);
        swap(buffer[1], sides[2][1][1]);

        sides[0][0][1] = buffer[0];
        sides[0][1][1] = buffer[1];

        // translation

        translation(sides, true, 3);
    }

    void r_l() // rotate right counterclockwise  3
    {
        uint8_t buffer[N];
        // right layer of TOP
        buffer[0] = sides[0][0][1];
        buffer[1] = sides[0][1][1];

        // right layer of FRONT
        swap(buffer[0], sides[2][0][1]);
        swap(buffer[1], sides[2][1][1]);

        // right layer of BOTTOM
        swap(buffer[0], sides[4][0][1]);
        swap(buffer[1], sides[4][1][1]);

        // right layer of BEHIND
        swap(buffer[0], sides[5][0][1]);
        swap(buffer[1], sides[5][1][1]);

        sides[0][0][1] = buffer[0];
        sides[0][1][1] = buffer[1];

        // translation

        translation(sides, false, 3);
    }

    void t() // rotate top clockwise  8
    {
        // rotation
        uint8_t buffer[N];
        buffer[0] = sides[1][0][0];
        buffer[1] = sides[1][0][1];

        swap(buffer[0], sides[5][1][1]);
        swap(buffer[1], sides[5][1][0]);

        swap(buffer[0], sides[3][0][0]);
        swap(buffer[1], sides[3][0][1]);

        swap(buffer[0], sides[2][0][0]);
        swap(buffer[1], sides[2][0][1]);

        sides[1][0][0] = buffer[0];
        sides[1][0][1] = buffer[1];

        // translation clockwise
        translation(sides, true, 0);
    }

    void t_l() // rotate top counterclockwise  9
    {
        // rotation
        uint8_t buffer[N];
        buffer[0] = sides[1][0][0];
        buffer[1] = sides[1][0][1];

        swap(buffer[0], sides[2][0][0]);
        swap(buffer[1], sides[2][0][1]);

        swap(buffer[0], sides[3][0][0]);
        swap(buffer[1], sides[3][0][1]);

        swap(buffer[0], sides[5][1][1]);
        swap(buffer[1], sides[5][1][0]);

        sides[1][0][0] = buffer[0];
        sides[1][0][1] = buffer[1];

        // translation counterclockwise
        translation(sides, false, 0);
    }

    /*
    void rot1() // rotate behind clockwise  0
    {
        uint8_t buffer[N];
        // top layer of TOP
        buffer[0] = sides[0][0][0];
        buffer[1] = sides[0][0][1];

        // left layer of LEFT
        swap(buffer[0], sides[1][1][0]);
        swap(buffer[1], sides[1][0][0]);

        // bottom layer of BOTTOM
        swap(buffer[0], sides[4][1][1]);
        swap(buffer[1], sides[4][1][0]);

        // right layer of RIGHT
        swap(buffer[0], sides[3][0][1]);
        swap(buffer[1], sides[3][1][1]);

        sides[0][0][0] = buffer[0];
        sides[0][0][1] = buffer[1];

        // translation

        translation(sides, true, 5);
    }

    void rot1i() // rotate behind counterclockwise  1
    {
        uint8_t buffer[N];
        // top layer of TOP
        buffer[0] = sides[0][0][0];
        buffer[1] = sides[0][0][1];

        // right layer of RIGHT
        swap(buffer[0], sides[3][0][1]);
        swap(buffer[1], sides[3][1][1]);

        // bottom layer of BOTTOM
        swap(buffer[0], sides[4][1][1]);
        swap(buffer[1], sides[4][1][0]);

        // left layer of LEFT
        swap(buffer[0], sides[1][1][0]);
        swap(buffer[1], sides[1][0][0]);

        sides[0][0][0] = buffer[0];
        sides[0][0][1] = buffer[1];

        // translation

        translation(sides, false, 5);
    }

    2 is being used, now r and 2i = r_l

    void rot3() // rotate left clockwise  4
    {
        uint8_t buffer[N];

        buffer[0] = sides[0][0][0];
        buffer[1] = sides[0][1][0];

        swap(buffer[0], sides[2][0][0]);
        swap(buffer[1], sides[2][1][0]);

        swap(buffer[0], sides[4][0][0]);
        swap(buffer[1], sides[4][1][0]);

        swap(buffer[0], sides[5][0][0]);
        swap(buffer[1], sides[5][1][0]);

        sides[0][0][0] = buffer[0];
        sides[0][1][0] = buffer[1];

        // translation

        translation(sides, true, 1);
    }

    void rot3i() // rotate left counterclockwise  5
    {
        uint8_t buffer[N];
        buffer[0] = sides[0][0][0];
        buffer[1] = sides[0][1][0];

        swap(buffer[0], sides[5][0][0]);
        swap(buffer[1], sides[5][1][0]);

        swap(buffer[0], sides[4][0][0]);
        swap(buffer[1], sides[4][1][0]);

        swap(buffer[0], sides[2][0][0]);
        swap(buffer[1], sides[2][1][0]);

        sides[0][0][0] = buffer[0];
        sides[0][1][0] = buffer[1];

        // translation

        translation(sides, false, 1);
    }

    4 is being used, now t and 4i = t_l

    5 is being used, now f and 5= f_l

    void rot6() // rotate bottom clockwise  10
    {
        // rotation
        uint8_t buffer[N];
        buffer[0] = sides[1][1][0];
        buffer[1] = sides[1][1][1];

        swap(buffer[0], sides[2][1][0]);
        swap(buffer[1], sides[2][1][1]);

        swap(buffer[0], sides[3][1][0]);
        swap(buffer[1], sides[3][1][1]);

        swap(buffer[0], sides[5][0][1]);
        swap(buffer[1], sides[5][0][0]);

        sides[1][1][0] = buffer[0];
        sides[1][1][1] = buffer[1];

        // translation clockwise
        translation(sides, true, 4);
    }

    void rot6i() // rotate bottom counterclockwise  11
    {
        // rotation
        uint8_t buffer[N];
        buffer[0] = sides[1][1][0];
        buffer[1] = sides[1][1][1];

        swap(buffer[0], sides[5][0][1]);
        swap(buffer[1], sides[5][0][0]);

        swap(buffer[0], sides[3][1][0]);
        swap(buffer[1], sides[3][1][1]);

        swap(buffer[0], sides[2][1][0]);
        swap(buffer[1], sides[2][1][1]);

        sides[1][1][0] = buffer[0];
        sides[1][1][1] = buffer[1];

        // translation counterclockwise
        translation(sides, false, 4);
    }
    */

    int random(int min, int max)
    {
        // Use the current time as the seed
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

        // Create a random number generator
        std::mt19937 generator(seed); // Mersenne Twister engine

        // Create a distribution in the range [min, max]
        std::uniform_int_distribution<int> distribution(min, max);

        return distribution(generator);
    }

    void shuffle()
    {
        // int randomNumber = rand() % 11 + 10; // generate a random number between 10 and 20

        int randomNumber = random(10, 20); // change this to change the amount of initial rotations

        cout << "[";
        for (int i = 0; i < randomNumber; i++)
        {
            int move = random(0, 5); // generate a random number between 0 and 11

            single_rotation(move);

            cout << int_to_rot_name(move) << (i == randomNumber - 1 ? "" : ", ");
            // for printing each step
            // cout << "\n" << endl;
            // print_cube();
        }
        cout << "]" << endl;
    }

    bool is_solved()
    {
        int i, j, k;

        for (i = 0; i < 5; i++) // 0-4 because if 5 sides are correct, the last one has to be correct too
        {
            if (sides[i][0][0] != sides[i][0][1] ||
                sides[i][0][0] != sides[i][1][0] ||
                sides[i][0][0] != sides[i][1][1])
                return false;
            /*||
            sides[i][0][1] != sides[i][1][0] ||
            sides[i][0][1] != sides[i][1][1] ||
            sides[i][1][0] != sides[i][1][1]*/
            // these comparisons are not needed, because if [(A == B) & (A == C)] then (B == C)
        }

        return true;
    }
};

// these are part of CubeInfo but because of circular dependency it is being defined here, after Cube
CubeInfo::CubeInfo(Cube *prev)
{
    prevCube = prev->prevCube;
    lastRot = prev->lastRot;
}

void CubeInfo::copyFromCube(Cube original)
{
    prevCube = original.prevCube;
    lastRot = original.lastRot;
}

void BFS(list<Cube> *processing, list<CubeInfo> *pastStates)
{
    int i;

    CubeInfo newInfo(&((*processing).front()));

    (*pastStates).push_back(newInfo);
    // used to read every entry and its contents
    // cout << &(*pastStates).back() << ": prevCube- " << (*pastStates).back().prevCube << ", lastRot- " << int_to_rot_name((*pastStates).back().lastRot) << endl;

    // save the cubes on memory, as I use their address
    // I need to analyze the state when it is already on pastStates, because that is the final
    // destination of the state, so its address won't change

    int undoLastRot = oppos_rot((*processing).front().lastRot);
    // int parallelRot;
    //  TODO: UNDO oppos parallel, because there are no parallel anymore
    // oppos_parallel_rots((*processing).front().lastRot, &undoLastRot, &parallelRot);

    for (i = 0; i < 6; i++)
    {
        if (i != undoLastRot /*&& i != parallelRot*/) // avoids making a copy of the previous state and to have the same state buts to the side
        {
            Cube newCube(&((*pastStates).back()), &((*processing).front()), i);

            (*processing).push_back(newCube);
        }
    }

    (*processing).pop_front();

    return;
}

// depth limited first search
bool DLS(list<Cube> *processing, int limit)
{
    // get top of stack
    Cube current = processing->front();

    if (current.is_solved())
        return true;

    if (limit == 0) // is at limit, doesn't expand more
        return false;

    int undoLastRot = oppos_rot(current.lastRot);

    // verifies if 3 rotations have been done in a row, because the fourth returns it
    int i, rots[3] = {-1, -1, -1};

    list<Cube>::iterator it = processing->begin();

    for (i = 0; i < 3; i++)
    {
        rots[i] = it->lastRot;
        if (it == processing->end())
            break;
        it++;
    }

    int completeRotation = (rots[0] == rots[1] && rots[0] == rots[2]) ? rots[0] : -1;

    // tries all rotations
    for (int rot = 0; rot < 6; rot++)
    {
        // if not undoing last rot and not doing the same rot 3 times in a row
        if (rot != undoLastRot && rot != completeRotation)
        {
            // creates child
            Cube newCube(NULL, &(processing->front()), rot);
            processing->push_front(newCube); // stack in pile

            if (DLS(processing, limit - 1))
            {
                return true; // solution found in this branch
            }

            // if not found, returns to this state and keeps trying other rotations
            processing->pop_front();
        }
    }

    return false; // no solution found in this branch
}

bool IDDFS(Cube initial, int maxDepth)
{
    // goes through all depths until maxDepth seraching for a optimal solution
    for (int depth = 0; depth <= maxDepth; depth++)
    {
        list<Cube> processing;

        processing.push_back(initial);

        // tries to find a solution at this depth
        if (DLS(&processing, depth))
        {
            cout << "Solved at depth " << depth << endl;
            return true;
        }
    }
    return false;
}

/* void DFS(list<Cube> *processing, stack<int> *nextRots)
{
    // get top of stack
    Cube current = processing->front();

    int undoLastRot = oppos_rot(current.lastRot); // avoids undoing the last rotation

    // verifies if 3 rotations have been done in a row, because the fourth returns it
    int i, rots[3] = {-1, -1, -1};
    list<Cube>::iterator it = processing->begin();
    for (i = 0; i < 3; i++)
    {
        rots[i] = it->lastRot;

        if (it == processing->end())
            break;

        it++;
    }

    int completeRotation = (rots[0] == rots[1] && rots[0] == rots[2]) ? rots[0] : -1; // avoids the cube from doing the same move 3 times in a row

    // check depth
    int depth = (*processing).size() - 1;

    // generate children if not at limit
    if (depth <= 14)
    {
        while (nextRots->top() < 6)
        {
            if (nextRots->top() != undoLastRot && nextRots->top() != completeRotation)
            {
                // past is not necessary because the stack saves the last states
                Cube newCube(NULL, &(processing->front()), nextRots->top());
                processing->push_front(newCube); // LIFO

                // prepares the next layer and prepares the current layer if it returns to it
                nextRots->top()++;
                nextRots->push(0);

                return;
            }
            nextRots->top()++;
        }
    }

    nextRots->pop();
    processing->pop_front();

    return; // se não achou solução neste limite
} */

void AI_loop(Cube initial)
{
    // add initial state on structure
    list<CubeInfo> pastStates;
    list<Cube> processing;
    stack<int> nextRots;
    stack<int> rotations;
    CubeInfo currCube;
    processing.push_back(initial);
    int n = 1, i = 1, total = 1;
    int choose = 1; // CHOOSING DFS
    nextRots.push(0);

    // while structure is not empty
    while (!processing.empty())
    {

        if (pastStates.size() >= total)
        {
            cout << "rot " << i++ << ". To be processed:" << processing.size() << endl;
            if (n == 1)
                n *= 6;
            else
                n *= 5;
            total += n;
        }

        // if (solved state)
        if ((processing.front()).is_solved())
        {
            cout << "Solved! " << endl;

            switch (choose)
            {
            case 0: // BFS
                for (currCube.copyFromCube(processing.front()); currCube.prevCube != NULL; currCube.copyInfo(*currCube.prevCube))
                {
                    rotations.push(currCube.lastRot);
                }

                cout << "[";
                while (!rotations.empty())
                {
                    cout << int_to_rot_name(rotations.top()) << ((rotations.size() != 1) ? ", " : "");
                    rotations.pop();
                }
                cout << "]";
                break;

            case 1: // DFS
                processing.pop_back();
                cout << "[";
                while (processing.size() != 0)
                {
                    cout << int_to_rot_name(processing.back().lastRot) << ((processing.size() != 1) ? ", " : "");
                    processing.pop_back();
                }
                cout << "]";
                break;
            }

            return;
        }

        // analysing function()
        // BFS(&processing, &pastStates);
        // breadth first search
        // DFS(&processing, &nextRots);
        // depth first search
        if (IDDFS(processing.front(), 14))
        {
            return; // stops while here otherwise it would keep going
        }
        // iterative deepening depth first search
        // A*
    }

    // return; no solution possible
}

int main()
{

    Cube c; // empty constructor

    c.print_cube();

    c.shuffle();

    c.print_cube();

    AI_loop(c);

    return 0;
}

string int_to_string(int x)
{
    stringstream ss;
    switch (x)
    {
    case 0:
        ss << GREEN << "0" << RESET;
        return ss.str();
    case 1:
        ss << YELLOW << "1" << RESET;
        return ss.str();
    case 2:
        ss << RED << "2" << RESET;
        return ss.str();
    case 3:
        ss << WHITE << "3" << RESET;
        return ss.str();
    case 4:
        ss << BLUE << "4" << RESET;
        return ss.str();
    case 5:
        ss << ORANGE << "5" << RESET;
        return ss.str();
    default:
        return "?";
    }
}

/*
void oppos_parallel_rots(int prevRot, int* oppos, int* parallel)
{
    switch(prevRot)
    {
        case 0:
            *oppos = 1;
            *parallel = 7;
            return;
        case 1:
            *oppos = 0;
            *parallel = 6;
            return;
        case 2:
            *oppos = 3;
            *parallel = 5;
            return;
        case 3:
            *oppos = 2;
            *parallel = 4;
            return;
        case 4:
            *oppos = 5;
            *parallel = 3;
            return;
        case 5:
            *oppos = 4;
            *parallel = 2;
            return;
        case 6:
            *oppos = 7;
            *parallel = 1;
            return;
        case 7:
            *oppos = 6;
            *parallel = 0;
            return;
        case 8:
            *oppos = 9;
            *parallel = 11;
            return;
        case 9:
            *oppos = 8;
            *parallel = 10;
            return;
        case 10:
            *oppos = 11;
            *parallel = 9;
            return;
        case 11:
            *oppos = 10;
            *parallel = 8;
            return;
        default:
            *oppos = -1;
            *parallel = -1;
            return;
    }
}
*/

int oppos_rot(int rot)
{
    if (rot == -1)
        return -1;

    if (rot % 2 == 0)
        return rot + 1;

    return rot - 1;
}

void translation(uint8_t sides[6][N][N], bool isClockwise, int face)
{
    uint8_t buffer;

    buffer = sides[face][0][0];

    swap(buffer, isClockwise ? sides[face][0][1] : sides[face][1][0]);
    swap(buffer, sides[face][1][1]);
    swap(buffer, isClockwise ? sides[face][1][0] : sides[face][0][1]);

    sides[face][0][0] = buffer;
}

string int_to_rot_name(int n)
{
    /*
    switch (n)
    {
    case 0:
        return "B";
    case 1:
        return "B\'";
    case 2:
        return "R";
    case 3:
        return "R\'";
    case 4:
        return "L";
    case 5:
        return "L\'";
    case 6:
        return "F";
    case 7:
        return "F\'";
    case 8:
        return "T";
    case 9:
        return "T'";
    case 10:
        return "U";
    case 11:
        return "U'";
    default:
        return "?";
    }
    */
    switch (n)
    {
    case 0:
        return "F";
    case 1:
        return "F\'";
    case 2:
        return "R";
    case 3:
        return "R\'";
    case 4:
        return "T";
    case 5:
        return "T\'";
    default:
        return "?";
    }
}