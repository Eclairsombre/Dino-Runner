#include "monster.h"
#include <iostream>
using namespace std;

void InitMonster(monster &m)
{
    m.MonsterRect.h = 30;
    m.MonsterRect.w = 30;
    m.MonsterRect.x = 500;
    m.MonsterRect.y = 500;

    m.x_base = m.MonsterRect.x;
    m.y_base = m.MonsterRect.y;

    m.direction = "";
}

void MonsterWalk(monster &m, string &direction)
{

    int random = rand() % 3;

    if (direction == "")
    {
        switch (random)
        {
        case 0:
            direction = "up";
            break;
        case 1:
            direction = "down";
            break;
        case 2:
            direction = "left";
            break;
        case 3:
            direction = "right";
            break;

        default:
            break;
        }
    }

    if (direction.compare("up") == 0)
    {

        m.MonsterRect.y -= 1;

        if (m.MonsterRect.y <= m.y_base - 150)
        {
            direction = "";
        }
    }
    else if (direction.compare("down") == 0)
    {

        m.MonsterRect.y += 1;
        if (m.MonsterRect.y >= m.y_base + 150)
        {
            direction = "";
        }
    }
    else if (direction.compare("left") == 0)
    {

        m.MonsterRect.x -= 1;
        if (m.MonsterRect.x <= m.x_base - 150)
        {
            direction = "";
        }
    }
    else if (direction.compare("right") == 0)
    {

        m.MonsterRect.x += 1;
        if (m.MonsterRect.x >= m.x_base + 150)
        {
            direction = "";
        }
    }
}
