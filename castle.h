#ifndef CASTLE
#define CASTLE
#include "defenses.h"
#include "list.h"
#include <string>
struct SpecificatCast{
    int Yield;//Доходность
    int Cost;
    int repairSpeed;
    int MaxStrength;//Прочность
    SpecificatCast():MaxStrength(450){}
};

class Castle:private Cell{
    friend class Scene;
private:
    int RealStrength;
    int level;
    string Name;
//    int RealStrength;
    List<Wall*> wallTable;//Таблицы стен и башен
    List<Tower*> towerTable;
    SpecificatCast castSpec;//Не массив тк нужно хранить только информацию об
public:
//    Castle():Name("Castle"), ActualStrength(){}
    Castle():RealStrength(1000), level(1){}
    ~Castle();
    int getLevel(){return level;}
    void setLevel(int i){level=i;}
    int AddTowerC(Tower *tower);//Возращает индекс
    int AddWallC(Wall *wall);
    void  BoostLevel();
    void  DamageTheCastle();
    int getRealStrength(){return RealStrength;}
    void setRealStrength(int a){RealStrength=a;}
    List <Wall*>& getWall (){return wallTable;}
    List <Tower*>& getTower(){return towerTable;}
    void BoostLevel(SpecificatCast a);
};
#endif // CASTLE
