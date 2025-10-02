#include "../include/cube.h"
#include <cmath>


const char REDO = '1';
const uint8_t NONE = 0x0F;


unsigned int bases6to2(long long);


int main(int argc, char* argv[])
{
    /*
        std::fstream file("knowledge.bin", std::ios::binary | std::ios::out);
        if (!file.is_open()) {
            std::cerr << "Error: Unable to open file!" << std::endl;
            return 1;
        }

        unsigned int id;

        // adding the with cost 15
        for(id = LOW_CUBE; id < HIGH_CUBE; id++)
            file.write(reinterpret_cast<const char*>(&NONE), 1);

        file.close();
    
    return 0;
    */

    // used to rewrite the costs to each state
    /*
    create a cube

    loop
        solve the cube
        get the cube id,do the shift verification
        rewrite the amount of moves needed to solve on knowledge[id] ////IF lower than the current value
        next cube possibility
    */

    int part = 0;

    Cube c;
    std::stack<Cube> cubes;
    std::stack<int> rots;   rots.push(5);
    uint8_t currValue;
    int currID;
    long long processed = 0;  // for test  

    if(part == 0)
        cubes.push(c);
    else
    {
        // load save state
        std::fstream load("saveState1.bin", std::ios::in | std::ios::binary);
        if (!load) {
            std::cerr << "Error opening file\n";
            return 1;
        }

        int i;
        std::stack<Cube> transitionCube;
        std::stack<int> transitionRot;
        uint8_t amountToLoadCubes;
        uint8_t amountToLoadRots;
        Cube tempCube;
        int tempRot;
        // size then contents
        load.read(reinterpret_cast<char*>(&amountToLoadCubes), 1);
        for(i=0; i<amountToLoadCubes; i++)
        {
            load.read(reinterpret_cast<char*>(&tempCube), 40);
            transitionCube.push(tempCube);
        }
        while(!transitionCube.empty())
        {
            cubes.push(transitionCube.top());
            transitionCube.pop();
        }

        load.read(reinterpret_cast<char*>(&amountToLoadRots), 1);
        for(i=0; i<amountToLoadRots; i++)
        {
            load.read(reinterpret_cast<char*>(&tempRot), 4);
            transitionRot.push(tempRot);
        }
        while(!transitionRot.empty())
        {
            rots.push(transitionRot.top());
            transitionRot.pop();
        }

        load.close();
    }

    while(processed < 10000 && !rots.empty())      // I chose to break in groups of 5.000.000.000, 
    {                                                   // so I just need to run it ~(7.2) 8 times :(
        currValue = AI_loop(cubes.top(), RUN_DFS,false);
        currID = cube2id(cubes.top()) - LOW_CUBE;

        
        std::fstream replace("knowledge.bin", std::ios::in | std::ios::out | std::ios::binary);
        if (!replace) {
            std::cerr << "Error opening file\n";
            return 1;
        }

        uint8_t compare;

        // Jump to the IDth byte
        replace.seekg(currID, std::ios::beg);
        replace.read(reinterpret_cast<char*>(&compare), 1);

        if(currValue < compare)
        {
            replace.seekp(currID, std::ios::beg);
            replace.write(reinterpret_cast<const char*>(&currValue), 1);
        }


        replace.close();

        // next cube

        int fullCircle = -1;
        // verifies if 3 rotations have been done in a row, because the fourth returns it to a previous state
        if(rots.size() > 2)
        {
            int temp_rots[2];

            temp_rots[0] = rots.top();
            rots.pop();
            temp_rots[1] = rots.top();
            rots.pop();

            if(temp_rots[0] == temp_rots[1] && temp_rots[0] == rots.top())
                fullCircle = temp_rots[0];
            
            rots.push(temp_rots[1]);
            rots.push(temp_rots[0]);
        }

        int undoLastRot = oppos_rot(cubes.top().lastRot); // avoids undoing the last rotation

        /*
        if (depth <= limit)
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
        */
        bool success = false;

        if(cubes.size() <= 14)
        {
            while(rots.top() < 6)
            {
                processed++;
                if(rots.top() != undoLastRot && rots.top() != fullCircle)
                {
                    Cube newC(NULL, &cubes.top(), rots.top());
                    cubes.push(newC);

                    rots.top()++;
                    rots.push(0);
                    
                    success = true;
                    break;
                }
                rots.top()++;
            }
        }

        // if no possibility was found, go back to previous state
        if(!success)
        {
            rots.pop();
            cubes.pop();
        }
    }

    // save state

    std::fstream save("saveState1.bin", std::ios::out | std::ios::binary);
    if (!save) {
        std::cerr << "Error opening file\n";
        return 1;
    }

    int i;
    uint8_t amountToSaveCubes = cubes.size();
    uint8_t amountToSaveRots = rots.size();
    // size then contents
    save.write(reinterpret_cast<const char*>(&amountToSaveCubes), 1);
    for(i=0; i<amountToSaveCubes; i++)
    {
        save.write(reinterpret_cast<const char*>(&cubes.top()), 40);
        cubes.pop();
    }

    save.write(reinterpret_cast<const char*>(&amountToSaveRots), 1);
    for(i=0; i<amountToSaveRots; i++)
    {
        save.write(reinterpret_cast<const char*>(&rots.top()), 1);
        rots.pop();
    }

    save.close();
    
    /* // test, reads a specific byte
    std::fstream file2("knowledge.bin", std::ios::binary | std::ios::in);
    if (!file2.is_open()) {
        std::cerr << "Error: Unable to open file2!" << std::endl;
        return 1;
    }

    uint8_t n = 0;

    // Skip first 1000000000 elements
    file2.seekg(1000000000, std::ios::beg);  // offset = 1.000.000.000 from the beginning

    file2.read(reinterpret_cast<char*>(&n), sizeof(n));

    std::cout << (int) n << std::endl;
    */

    return 0;
}

unsigned int bases6to2(long long n)
{
    unsigned int res = 0;
    int exp = 0;

    while(n > 0)
    {
        res += (n%10) * (pow(6, exp++));
        n /= 10;
    }

    return res;
}