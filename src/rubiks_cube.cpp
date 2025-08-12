#include <iostream>
#include <sstream>
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

class Cube
{
public:
    // attr
    int sides[6][N][N];

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
        cout << "  " << int_to_string(sides[5][1][0]) << int_to_string(sides[5][1][1]) << endl;
    }

    void rot1() // rotate behind clockwise
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
    }

    void rot1i() // rotate behind counterclockwise
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
    }

    void rot2() // rotate right clockwise
    {
        int buffer[N];
        buffer[0] = sides[0][0][1];
        buffer[1] = sides[0][1][1];

        swap(buffer[0], sides[2][0][1]);
        swap(buffer[1], sides[2][1][1]);

        swap(buffer[0], sides[4][0][1]);
        swap(buffer[1], sides[4][1][1]);

        swap(buffer[0], sides[5][0][1]);
        swap(buffer[1], sides[5][1][1]);

        sides[0][0][1] = buffer[0];
        sides[0][1][1] = buffer[1];
    }

    void rot2i() // rotate right counterclockwise
    {
        int buffer[N];
        buffer[0] = sides[0][0][1];
        buffer[1] = sides[0][1][1];

        swap(buffer[0], sides[5][0][1]);
        swap(buffer[1], sides[5][1][1]);

        swap(buffer[0], sides[4][0][1]);
        swap(buffer[1], sides[4][1][1]);

        swap(buffer[0], sides[2][0][1]);
        swap(buffer[1], sides[2][1][1]);

        sides[0][0][1] = buffer[0];
        sides[0][1][1] = buffer[1];
    }

    void rot3() // rotate left clockwise
    {
        int buffer[N];
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
    }

    void rot3i() // rotate left counterclockwise
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
    }

    void rot4() // rotate front clockwise
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
    }

    void rot4i() // rotate front counterclockwise
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
    }
};

int main()
{

    Cube c;

    c.print_cube();
    c.rot4();

    cout << "\n"
         << endl;
    c.print_cube();

    c.rot4i();

    cout << "\n"
         << endl;
    c.print_cube();

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