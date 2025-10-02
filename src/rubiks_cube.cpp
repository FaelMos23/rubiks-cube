#include "../include/cube.h"

int main()
{

    Cube c; // empty constructor

    //c.print_cube();

    c.shuffle();
    //c.worst_case();

    AI_loop(c, RUN_Astar);

    return 0;
}