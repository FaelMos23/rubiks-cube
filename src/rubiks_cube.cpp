#include "../include/cube.h"

int main(int argc, char* argv[])
{
    Cube c; // empty constructor
    uint8_t method = RUN_DFS;   // standard
    bool showStates = argc > 2 && (argv[2][0] == 's' || argv[2][0] == 'S' ) ? true : false;

    if(argc > 1)
    {
        switch(argv[1][0])
        {
        case 'B':
            c.shuffle_BFS();
            method = RUN_BFS;
            break;
        case 'A':
            c.shuffle();
            method = RUN_Astar;
            break;
        case 'd':
            c.demo();
            method = RUN_Astar;
            break;
        case 'D':
            c.shuffle();
            method = RUN_DFS;
            break;
        default:
            std::cout << "Doing default: DFS showing states" << std::endl;
            c.shuffle();
            method = RUN_DFS;
            break;
        }

        AI_loop(c, method, showStates);
    }
    else
    {   // default functioning

        c.shuffle();

        c.print_cube();

        AI_loop(c, RUN_DFS, true);

    }

    return 0;
}