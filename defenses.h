#ifndef DEFENSES
#define DEFENSES
#include "list.h"
#include "enemy.h"
class Map;
class Cell
{
//    friend class Scene;
public:
    int type;//0 - равнина
    int index;//в списке
    int X_coordinate;
    int Y_coordinate;
    int label;
//    Cell & operator () (int x, int y, int type, int index);
    Cell():type(0), index(-1), X_coordinate(-1), Y_coordinate(-1), label(-2){}
};

//Буду при увеличении уроня копировать из массива в структуру
struct SpecificatTow{
    int radius;
    int SpeedOfShoot;
    int Cost;
    int damageDone;
    SpecificatTow():radius(2), SpeedOfShoot(1), Cost(10), damageDone(10){}
};
///Необходимо перегрузить оператор = для корректного добаления в список (оба класса)
class Wall:private Cell
{
    friend class Scene;
private:
   const int MaxStrength=70;
    int RealStrength;
public:
    Wall():RealStrength(MaxStrength){}
    void Damage(int loss);
    void Repairl();//Отремонтировать стену
    int getX(){return X_coordinate;}
    int getY(){return Y_coordinate;}
    int getIndex(){return index;}
    void setIndex(int i){index=i;}
    Wall & operator=(const Wall& a);
    Wall(Wall &a);
    Wall *clone() {return new Wall(*this);}
    int getRealStrength(){return RealStrength;}
    void setRealStrength(int i){RealStrength=i;}
//    void AddWall();
//    void RemoveWall();
};


class Tower: private Cell{
    friend class Scene;
private:
    int level;
    SpecificatTow towSpec;
public:
    Tower():level(1){}
     int getLevel(){return level;}
    void setLevel(int i){level=i;}
    void setSpec(SpecificatTow &a){towSpec=a;}
    int getRadius(){return towSpec.radius;}
    int getSpeed(){return towSpec.SpeedOfShoot;}
    int getdamageDone(){return towSpec.damageDone;}
    int getCost(){return towSpec.Cost;}
   void  BoostLevel(SpecificatTow a);
   int DamageEnemy(List<Enemy*>& enemy, Map *map);
   int getX(){return X_coordinate;}
   int getY(){return Y_coordinate;}
   Tower & operator = ( const Tower& a);
   Tower(Tower &tower);
   Tower *clone() {return new Tower(*this);}

//   void AddTower();
//   void RemoveTower();
};


#endif // DEFENSES
