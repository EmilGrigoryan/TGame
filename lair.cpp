#include "lair.h"
#include <iostream>
Lair::~Lair()
{
    for (int i=0; i<TableOfEnemies.GetSize();++i)
    {
        delete TableOfEnemies[i];
    }
}

void Lair::addEnemy(int i, int x, int y)
{
    std::cout<<i<<std::endl;
    TableOfEnemies[i]->setinGame(1);//В игре
    TableOfEnemies[i]->setX_Coord(x);
    TableOfEnemies[i]->setY_Coord(y);
}

void Lair::AddEnemyT(Enemy *a)
{
    TableOfEnemies.push_back(a->clone());
    cout<<"--------------------------------"<<endl;
}
