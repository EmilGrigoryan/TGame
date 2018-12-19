sfdgdsfg
#include "castle.h"
#include <iostream>
using namespace std;
Castle::~Castle()
{
    for(int i=0; i< wallTable.GetSize();++i)
    {
        delete wallTable[i];
    }
    for (int i=0; i<towerTable.GetSize(); ++i)
    {
        delete towerTable[i];
    }
}

int Castle::AddTowerC(Tower *tower)
{
//    towerTable.push_back(tower->clone());
    towerTable.push_back(tower);
    return towerTable.GetSize()-1;
}

int Castle::AddWallC(Wall *wall)
{
    wallTable.push_back(wall->clone());
//    cout<<"WORK"<<endl;
    return wallTable.GetSize()-1;
}


void Castle::BoostLevel(SpecificatCast a)
{
    castSpec=a;
    level++;
    std::cout<<castSpec.Cost<<std::endl;
    RealStrength=RealStrength+100;
}
