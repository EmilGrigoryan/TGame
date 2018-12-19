#ifndef ENEMY
#define ENEMY
#include <SFML/Graphics.hpp>
using namespace sf;
#include <iostream>
///*
///Через каждый шаг враг будет восстанавивать (если ему не наносят урон в это время)
///Враг может двигаться только по горизонтали и вертикали
//#include "list.h"
using namespace std;
#include <string>

//Для увелиения на некоторое число здоровья и скорост(на 1)
//struct Auras{
//    int speed;
//    int Health;
//    Auras(): speed(0), Health(0){}
//    Auras(int s, int m, int reg):speed(s), Health(m){}
//};

//Базовый для врага
class Enemy
{
    private:
        int type_Her;//для проверки является ли героем данный враг (1-ГЕРОЙ)
        string Name;
        int MaxHealth;
        int RealHealth;
        int Speed;
        float RegenerationRate;
        double DamageCoef;
        int X_coordinate;
        int Y_coordinate;
        int Type;//Какого типа враг
        int ExtraFeatures;
        int inGame;//Если  на поле, то 1
        int HeroRadius;
//        Auras aur;
    public:
        Enemy();
        Enemy(Enemy &right);
//        Auras getAur();
        Sprite s_enemy;
        Image enemy_image;
        Texture enemy;
        void setinGame(int i){inGame=i;}
        int getinGame(){return inGame;}
        int getExtraFeatures(){return ExtraFeatures;}
        void setExtraFeatures(int i){ExtraFeatures=i;}
        void setAurSpeed(int S);
        void setAurHealth(int health);
        double getRegenerationRate();
        void setRegenerationRate(double a);
        double getDamageCoef();
        void setDamageCoef(double a);
        void setMaxHealth(int a);
        int getMaxHealth();
        int getRealHealth();
        void setRealHealth(int health);
        int getX_Coord();
        void setX_Coord(int a);
        void setY_Coord(int b);
        int getY_Coord();
        int getType();
        void setType(int a);
        int getTypePer();
        void setTypePer(int a);
        string getName();
        void setName(string name);
        int getSpeed();
        void setSpeed(int S);
        int Damage(int k);
        void Extra();
        virtual  Enemy & operator = (const Enemy &a);
        virtual Enemy *clone(){}
//        virtual Enemy *clone() {return new Enemy(*this);}
        virtual  void Move(int x, int y);
};

//По минимальному расстоянию будем определять направление движения врага 0-влево, 1-вправо, 2-вниз, 3-вверх
//Пехота
class LightInfantry: public Enemy{
    public:
    virtual void Move(int x, int y);
    Enemy *clone() {return new LightInfantry(*this); std::cout<<"BBBBBBBBBBBBBBB"<<std::endl;}//Для использоания необходимо реализовать копир конструктор
    LightInfantry(LightInfantry &right){}
    LightInfantry():Enemy(){}
};

//Тяжелая пехота
class HeavyInfantry: public Enemy{
    public:
     HeavyInfantry & operator = (const HeavyInfantry &a)  {Enemy::operator =(a);}
     virtual Enemy *clone() {return new HeavyInfantry(*this);}
     void DestroyWall();//Разрушить стену
     virtual void Move(int x, int y);
};

//Авиация
class Aviation: public Enemy{
    public:
     Aviation & operator = (const Aviation &a)  {Enemy::operator =(a);}
     virtual Enemy *clone() {return new Aviation(*this);}
     virtual  void Move(int x, int y);
};

#endif // ENEMY
