#include <iostream>
#include <sstream>
#include <chrono>
#include <random>
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

    // rotation methods

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

        // translation

        buffer[0] = sides[5][1][1];

        swap(buffer[0], sides[5][1][0]);
        swap(buffer[0], sides[5][0][0]);
        swap(buffer[0], sides[5][0][1]);

        sides[5][1][0] = buffer[0];
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

        // translation

        buffer[0] = sides[5][1][1];

        swap(buffer[0], sides[5][0][1]);
        swap(buffer[0], sides[5][0][0]);
        swap(buffer[0], sides[5][1][0]);

        sides[5][1][0] = buffer[0];
    }

    void rot2() // rotate right clockwise
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

        buffer[0] = sides[3][0][0];

        swap(buffer[0], sides[3][0][1]);
        swap(buffer[0], sides[3][1][1]);
        swap(buffer[0], sides[3][1][0]);

        sides[3][0][0] = buffer[0];
    }

    void rot2i() // rotate right counterclockwise
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

        buffer[0] = sides[3][0][0];

        swap(buffer[0], sides[3][1][0]);
        swap(buffer[0], sides[3][1][1]);
        swap(buffer[0], sides[3][0][1]);

        sides[3][0][0] = buffer[0];
    }

    void rot3() // rotate left clockwise
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

        buffer[0] = sides[1][0][0];

        swap(buffer[0], sides[1][0][1]);
        swap(buffer[0], sides[1][1][1]);
        swap(buffer[0], sides[1][1][0]);

        sides[1][0][0] = buffer[0];
    }

    void rot3i() // rotate left clockwise
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

        buffer[0] = sides[1][0][0];

        swap(buffer[0], sides[1][1][0]);
        swap(buffer[0], sides[1][1][1]);
        swap(buffer[0], sides[1][0][1]);

        sides[1][0][0] = buffer[0];
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

        // translation

        buffer[0] = sides[2][0][0];

        swap(buffer[0], sides[2][0][1]);
        swap(buffer[0], sides[2][1][1]);
        swap(buffer[0], sides[2][1][0]);

        sides[1][0][0] = buffer[0];
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

        // translation

        buffer[0] = sides[2][0][0];

        swap(buffer[0], sides[2][1][0]);
        swap(buffer[0], sides[2][1][1]);
        swap(buffer[0], sides[2][0][1]);

        sides[1][0][0] = buffer[0];
    }

    void rot5() // rotate top clockwise
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
        buffer[0] = sides[0][0][0];

        swap(buffer[0], sides[0][0][1]);
        swap(buffer[0], sides[0][1][1]);
        swap(buffer[0], sides[0][1][0]);

        sides[0][0][0] = buffer[0];
    }

    void rot5i() // rotate top counterclockwise
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
        buffer[0] = sides[0][0][0];

        swap(buffer[0], sides[0][1][0]);
        swap(buffer[0], sides[0][1][1]);
        swap(buffer[0], sides[0][0][1]);

        sides[0][0][0] = buffer[0];
    }

    void rot6() // rotate bottom clockwise
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
        buffer[0] = sides[4][0][0];

        swap(buffer[0], sides[4][0][1]);
        swap(buffer[0], sides[4][1][1]);
        swap(buffer[0], sides[4][1][0]);

        sides[4][0][0] = buffer[0];
    }

    void rot6i() // rotate bottom counterclockwise
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
        buffer[0] = sides[4][0][0];

        swap(buffer[0], sides[4][1][0]);
        swap(buffer[0], sides[4][1][1]);
        swap(buffer[0], sides[4][0][1]);

        sides[4][0][0] = buffer[0];
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

        for (int i = 0; i < randomNumber; i++)
        {
            int move = random(0, 11); // generate a random number between 0 and 11
            switch (move)
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

            cout << "\n"
                 << endl;
            print_cube();
        }
    }
};

int main()
{

    Cube c;

    c.shuffle();

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