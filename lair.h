#ifndef LAIR
#define LAIR
#include "list.h"
#include "enemy.h"
//#include "scene.h"
class Scene;
class Lair{
    friend class Scene;
    private:
        int MaxTime;//Спустя это время враг должен выйти из логова
        //int TimeOut[NumberOfEnemies];// Время выхода
        List<Enemy*>TableOfEnemies;
public:
        ~Lair();
        void  ReleaseTheEnemy();
        void ReleaseTheEnemyOnTime();//Выпустить врага, если настало его время
        void addEnemy(int, int , int);
        void AddEnemyT(Enemy *a);//Доработать
        List <Enemy*>& getEnemyTab(){return TableOfEnemies;}
};
#endif // LAIR
