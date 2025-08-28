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
int oppos_rot(int);
void translation(int sides[6][N][N], bool isClockwise, int face);

class Cube
{
public:
    // attr
    int sides[6][N][N];
    Cube* prevCube;
    int lastRot;

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

        prevCube = NULL;    // this is the first cube
        lastRot = -1;       // there was no rotation to get here
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
                rot1();
                break;
            case 1:
                rot1i();
                break;
            case 2:
                rot2();
                break;
            case 3:
                rot2i();
                break;
            case 4:
                rot3();
                break;
            case 5:
                rot3i();
                break;
            case 6:
                rot4();
                break;
            case 7:
                rot4i();
                break;
            case 8:
                rot5();
                break;
            case 9:
                rot5i();
                break;
            case 10:
                rot6();
                break;
            case 11:
                rot6i();
                break;
        }
    }

    // constructor that copies another cube than rotates it
    Cube(Cube *prev, int rot){   // creates a cube based on a previous one
        int i, j, k;

        for(i=0; i<6; i++)
            for(j=0; j<N; j++)
                for(k=0; k<N; k++)
                {
                    sides[i][j][k] = (*prev).sides[i][j][k];
                }

        single_rotation(rot);

        prevCube = prev;    // points to the cube that originated this one
        lastRot = rot;       // saves the last rotation
    }

    // methods
    // direct 2x2 print, will make it better later
    void print_cube()
    {
        cout << "  "                                                                << int_to_string(sides[0][0][0]) << int_to_string(sides[0][0][1]) << endl;
        cout << "  "                                                                << int_to_string(sides[0][1][0]) << int_to_string(sides[0][1][1]) << endl;
        cout << int_to_string(sides[1][0][0]) << int_to_string(sides[1][0][1]) << int_to_string(sides[2][0][0]) << int_to_string(sides[2][0][1]) << int_to_string(sides[3][0][0]) << int_to_string(sides[3][0][1]) << endl;
        cout << int_to_string(sides[1][1][0]) << int_to_string(sides[1][1][1]) << int_to_string(sides[2][1][0]) << int_to_string(sides[2][1][1]) << int_to_string(sides[3][1][0]) << int_to_string(sides[3][1][1]) << endl;
        cout << "  " << int_to_string(sides[4][0][0]) << int_to_string(sides[4][0][1]) << endl;
        cout << "  " << int_to_string(sides[4][1][0]) << int_to_string(sides[4][1][1]) << endl;
        cout << "  " << int_to_string(sides[5][0][0]) << int_to_string(sides[5][0][1]) << endl;
        cout << "  " << int_to_string(sides[5][1][0]) << int_to_string(sides[5][1][1]) << "\n" << endl;
    }

    // rotation methods

    void rot1() // rotate behind clockwise  0
    {
        int buffer[N];
        buffer[0] = sides[0][0][0];
        buffer[1] = sides[0][0][1];

        swap(buffer[0], sides[1][1][0]);
        swap(buffer[1], sides[1][0][0]);

        swap(buffer[0], sides[4][1][1]);
        swap(buffer[1], sides[4][1][0]);

        swap(buffer[0], sides[3][0][1]);
        swap(buffer[1], sides[3][1][1]);

        sides[0][0][0] = buffer[0];
        sides[0][0][1] = buffer[1];

        // translation

        translation(sides, true, 5);
    }

    void rot1i() // rotate behind counterclockwise  1
    {
        int buffer[N];
        buffer[0] = sides[0][0][0];
        buffer[1] = sides[0][0][1];

        swap(buffer[0], sides[3][0][1]);
        swap(buffer[1], sides[3][1][1]);

        swap(buffer[0], sides[4][1][1]);
        swap(buffer[1], sides[4][1][0]);

        swap(buffer[0], sides[1][1][0]);
        swap(buffer[1], sides[1][0][0]);

        sides[0][0][0] = buffer[0];
        sides[0][0][1] = buffer[1];

        // translation

        translation(sides, false, 5);
    }

    void rot2() // rotate right clockwise  2
    {
        int buffer[N];
        buffer[0] = sides[0][0][1];
        buffer[1] = sides[0][1][1];

        swap(buffer[0], sides[5][1][0]);
        swap(buffer[1], sides[5][0][0]);

        swap(buffer[0], sides[4][0][1]);
        swap(buffer[1], sides[4][1][1]);

        swap(buffer[0], sides[2][0][1]);
        swap(buffer[1], sides[2][1][1]);

        sides[0][0][1] = buffer[0];
        sides[0][1][1] = buffer[1];

        // translation

        translation(sides, true, 3);
    }

    void rot2i() // rotate right counterclockwise  3
    {
        int buffer[N];
        buffer[0] = sides[0][0][1];
        buffer[1] = sides[0][1][1];

        swap(buffer[0], sides[2][0][1]);
        swap(buffer[1], sides[2][1][1]);

        swap(buffer[0], sides[4][0][1]);
        swap(buffer[1], sides[4][1][1]);

        swap(buffer[0], sides[5][1][0]);
        swap(buffer[1], sides[5][0][0]);

        sides[0][0][1] = buffer[0];
        sides[0][1][1] = buffer[1];

        // translation

        translation(sides, false, 3);
    }

    void rot3() // rotate left clockwise  4
    {
        int buffer[N];

        buffer[0] = sides[0][0][0];
        buffer[1] = sides[0][1][0];

        swap(buffer[0], sides[2][0][0]);
        swap(buffer[1], sides[2][1][0]);

        swap(buffer[0], sides[4][0][0]);
        swap(buffer[1], sides[4][1][0]);

        swap(buffer[0], sides[5][1][1]);
        swap(buffer[1], sides[5][0][1]);

        sides[0][0][0] = buffer[0];
        sides[0][1][0] = buffer[1];

        // translation

        translation(sides, true, 1);
    }

    void rot3i() // rotate left clockwise  5
    {
        int buffer[N];
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

    void rot4() // rotate front clockwise  6
    {
        int buffer[N];
        buffer[0] = sides[0][1][0];
        buffer[1] = sides[0][1][1];

        swap(buffer[0], sides[3][0][0]);
        swap(buffer[1], sides[3][1][0]);

        swap(buffer[0], sides[4][0][0]);
        swap(buffer[1], sides[4][0][1]);

        swap(buffer[0], sides[1][0][1]);
        swap(buffer[1], sides[1][1][1]);

        sides[0][1][0] = buffer[0];
        sides[0][1][1] = buffer[1];

        // translation

        translation(sides, true, 2);
    }

    void rot4i() // rotate front counterclockwise  7
    {
        int buffer[N];
        buffer[0] = sides[0][1][0];
        buffer[1] = sides[0][1][1];

        swap(buffer[0], sides[1][0][1]);
        swap(buffer[1], sides[1][1][1]);

        swap(buffer[0], sides[4][0][0]);
        swap(buffer[1], sides[4][0][1]);

        swap(buffer[0], sides[3][0][0]);
        swap(buffer[1], sides[3][1][0]);

        sides[0][1][0] = buffer[0];
        sides[0][1][1] = buffer[1];

        // translation

        translation(sides, false, 2);
    }

    void rot5() // rotate top clockwise  8
    {
        // rotation
        int buffer[N];
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

    void rot5i() // rotate top counterclockwise  9
    {
        // rotation
        int buffer[N];
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
        translation(sides, true, 0);
    }

    void rot6() // rotate bottom clockwise  10
    {
        // rotation
        int buffer[N];
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
        int buffer[N];
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

        int randomNumber = random(10, 20);

        cout << "[";
        for (int i = 0; i < randomNumber; i++)
        {
            int move = random(0, 11); // generate a random number between 0 and 11
            
            single_rotation(move);

            cout << move << (i == randomNumber-1? "" : ", ");
            // for printing each step
            //cout << "\n" << endl;
            //print_cube();
        }
        cout << "]" << endl;
    }

    bool is_solved()
    {
        int i, j, k;

        for(i=0; i<5; i++) // 0-4 because if 5 sides are correct, the last one has to be correct too
        {
            if(sides[i][0][0] != sides[i][0][1] || 
               sides[i][0][0] != sides[i][1][0] || 
               sides[i][0][0] != sides[i][1][1] || 
               sides[i][0][1] != sides[i][1][0] || 
               sides[i][0][1] != sides[i][1][1] || 
               sides[i][1][0] != sides[i][1][1])
                return false;
        }
        
        return true;
    }

    void copy(Cube original)
    {
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
};


void BFS(list<Cube>* processing, list<Cube>* pastStates)
{
    int i;
    (*pastStates).push_back((*processing).front());   // save the cubes on memory, as I use their address
    (*processing).pop_front(); 
    // I need to analyze the state when it is already on pastStates, because that is the final
    // destination of the state, so its address won't change

    int prevRot = oppos_rot((*pastStates).back().lastRot);
    for(i=0; i<12; i++)
    {
        if(i != prevRot) // avoids making a copy of the previous state
        {
            Cube newCube(&((*pastStates).back()), i);

            (*processing).push_back(newCube);
        }
    }

    return;
}


void AI_loop(Cube initial) 
{
    // add initial state on structure
    list<Cube> pastStates;
    list<Cube> processing;
    stack<int> rotations;
    Cube currState;
    Cube currCube;
    processing.push_back(initial);

    // while structure is not empty
    while(!processing.empty())
    {
        currState = processing.front();
        // if (solved state)
        if(currState.is_solved())
        {
            cout << "Solved!" << endl;
            currState.print_cube();
            
            for(currCube.copy(currState); currCube.prevCube != NULL; currCube.copy(*currCube.prevCube))
            {
                rotations.push(currCube.lastRot);
            }

            cout << "[";
            while(!rotations.empty())
            {
                cout << rotations.top() << ((rotations.size() != 1)? ", " : "");
                rotations.pop();
            }
            cout << "]";

            
            return;
        }

        // analysing function()
        BFS(&processing, &pastStates);
        // breadth first search
        // depth first search
        // A*
    }

    //return; no solution possible
}



int main() {
    
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

int oppos_rot(int rot)
{
    if(rot == -1)
        return -1;

    if(rot%2 == 0)
        return rot+1;
    
    return rot-1;
}

void translation(int sides[6][N][N], bool isClockwise, int face)
{
    int buffer;

    buffer = sides[face][0][0];

    swap(buffer, isClockwise? sides[face][1][0] : sides[face][0][0]);
    swap(buffer, sides[face][1][1]);
    swap(buffer, isClockwise? sides[face][1][0] : sides[face][0][1]);

    sides[face][0][0] = buffer;
}