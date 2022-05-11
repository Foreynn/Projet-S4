#include "model.h"

double recognition(double input[])
{
    int up = 0;
    int left = 0;
    int right = 0;
    int down = 0;


    if (input[4] == -0.5)
        up = 1;
    if (input[4*9] == -0.5)
        left = 1;
    if (input[5*9 - 1] == -0.5)
        right = 1;
    if (input[9*9 - 4] == -0.5)
        down = 1;


    if (up)
    {
        if (left)
        {
            if (right)
            {
                if (down)
                    return FOUR_WAY;
                return LEFT_UP_RIGHT;
            }
            if (down)
                return LEFT_UP_DOWN;
            return LEFT_UP;
        }
        if (right)
        {
            if (down)
                return UP_RIGHT_DOWN;
            return UP_RIGHT;
        }
        if (down)
            return UP_DOWN;
        return UP;
    }
    if (left)
    {
        if (right)
        {
            if (down)
                return LEFT_RIGHT_DOWN;
            return LEFT_RIGHT;
        }
        if (down)
            return LEFT_DOWN;
        return LEFT;
    }
    if (down)
    {
        if (right)
            return RIGHT_DOWN;
        return DOWN;
    }
    if (right)
        return RIGHT;
    return ZERO_WAY;
}