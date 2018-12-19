#ifndef SCENE
#define SCENE
#include <iostream>
#include <fstream>
#include <cstdlib>
#define SIZE 10
//#define NumberOfDefenses 128
using namespace std;
//#include "list.h"
#include "castle.h"
#include "lair.h"
#include <unistd.h>//библитека для использования Sleep, но нужна будет только в main
class Lair;
///Классы, работающие с динамиеской памятью:
///Map
enum{
    Plain_t,
    Castle_t,
    Lair_t,
    Tower_t,
    Wall_t,
    Enemy_t,
    Mountains_t,
    Forest_t,
    Water_t
};
struct ForTheWay{
    int *px;
    int *py;
    int len;
    ForTheWay():px(nullptr), py(nullptr), len(0){}
};


class Map{
public:
    int Size_x;
    int Size_y;
    Cell **map;
    Map():Size_x(0), Size_y(0), map(nullptr){}//Пустой конструктор
    Map(int x, int y):Size_x(x), Size_y(y)
    {
        map=new Cell*[Size_x];
        for (int i=0; i<Size_x; ++i)
        {
            map[i]=new Cell[Size_y];
        }
    }
    ~Map()
    {
        for (int i=0; i<Size_x; ++i)
        {
            delete [] map[i];
        }
        delete [] map;
    }
    Map(const Map &term) :Size_x(term.Size_x), Size_y(term.Size_y)//Иницализация экземпляром класса
    {
        //terminal = new Terminal[SZ];
        map=new Cell*[Size_x];
        for (int i = 0; i< Size_x; ++i)
        {
            map[i]=new Cell[Size_y];
            for(int j=0; j<term.Size_y; ++j)
            {
                map[i][j]=term.map[i][j];
            }
        }
    }
    Map(const Map && term):Size_x(term.Size_x), Size_y(term.Size_y){map=term.map;}
};


//План:
//Цикл:
//Обработка всех врагов с аурами
//Обработка башен
//Шаг (будут находиться кратчайщие расстояния, обрабатываться враги и таймеры)
///
/// \brief The Scene class
///Конструктор: Пустой, инициализирующий размерами поля, начальными состоянияи для таблиц врагов и защитных сооружений
///и типами клеток  двумерном массиве
///
/// Сделаны конструкторы для Map (2 инициализирующих и пустой) и Cell
/// Тут также будут реалиованы функции добавления и удаления защитных сооружений
class Scene
{
    friend class Game;
  private:
    const int maxMoney=500;
    Castle *castle;
    Lair *lair;
    int Money;
    friend class Map;//Карта
    SpecificatTow *TowSpec;//Таблица характеристик соотв уровню башни
    SpecificatCast *CastSpec;//Таблица характеристик соотв уровню замка
    Map map;
    int LevelQ;
    ForTheWay way;
    int EnemyNumber;
    const int WallCost=10;
public:
    Scene();
//    Scene(const Map &map1, const List<Wall> wall, const List<Enemy> enemy, const List<Tower> tower);
    Scene(const Map &map):map(map), TowSpec(nullptr), CastSpec(nullptr){}
    ~Scene();
    int getSize_x(){return map.Size_x;}
    int getSize_y(){return map.Size_y;}
    int getSize(){return map.Size_y*map.Size_x;}
    int getType(int x, int y){return map.map[x][y].type;}
    void setType(int x, int y, int t);
    void setXSize(int s){map.Size_x=s;}
    void setYSize(int s){map.Size_y=s;}
    void setMoney(int m){Money=m;}
    int getMoney(){return Money;}
    Map getMap(){return map;}
    void addTower(int x, int y);
    int addWall(int x, int y);
    int DamageCastle(int i);
//    void removeTower(int x, int y);
//    void removeWall(int x, int y);
    bool lee(int ax, int ay, int bx, int by, ForTheWay &a, int type);//Для легкой пехоты (в структуре хрантся координаты)
//    bool leeH(int ax, int ay, int bx, int by, ForTheWay &a);//Для тяжелой пехоты
    void DamageEnemy();
    int Record();
    void SetSpec(SpecificatCast *a, SpecificatTow *b);
    void SetLevel(int i){LevelQ=i;}
    int Reading();
    void AddEnemy();
    void AddLair(){lair=new Lair;}
    Lair *getLair(){return lair;}
    void AddCastle(){castle=new Castle;}
    Castle *getCastle(){return castle;}
    void setLabel();
    void setLabel2_0();
    void setLabel3_0();
    void Move();
    void AddEnemyMap();
    int HeroFunc(int x, int y);
    void  BoostLevelTow(int i);
    void BoostLevelCast();
};
#endif
///Перставил setLabel в начало, в функция добавления снен и башен сначала выставляю не label, а type
