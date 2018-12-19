#include "enemy.h"
#include <iostream>
using namespace std;
///ExtraFaetures может меняться только один раз за игру
Enemy::Enemy():MaxHealth(250), Speed(1), RegenerationRate(0.1), ExtraFeatures(0), inGame(0), HeroRadius(2)//gj
{
      RegenerationRate=0.1;
      DamageCoef=0.5;
      X_coordinate=-1;
      Y_coordinate=-1;
      type_Her=0;
      Type=0;
      RealHealth=MaxHealth;
}

Enemy::Enemy(Enemy &right)
{
    X_coordinate=right.X_coordinate;
    Y_coordinate=right.Y_coordinate;
    Speed=right.Speed;
    RegenerationRate=right.RegenerationRate;
    DamageCoef=right.DamageCoef;
//    aur=right.aur;
}

//Auras Enemy::getAur()
//{
//    return aur;
//}

//void Enemy::setAurSpeed(int S)
//{
//    aur.speed=S;
//}

//void Enemy::setAurHealth(int health)
//{
//    aur.Health=health;
//}
////void Enemy::setAur(Auras a)
////{
////    return aur;
////}
double Enemy::getRegenerationRate()
{
    return RegenerationRate;
}

void Enemy::setRegenerationRate(double a)
{
    RegenerationRate=a;
}

double Enemy::getDamageCoef()
{
    return DamageCoef;
}

void Enemy::setDamageCoef(double a)
{
    DamageCoef=a;
}

void Enemy::setMaxHealth(int a)
{
    MaxHealth=a;
}

int Enemy::getMaxHealth()
{
    return MaxHealth;
}

int Enemy::getRealHealth()
{
    return RealHealth;
}

void Enemy::setRealHealth(int health)
{
    RealHealth=health;
}

 int Enemy::getType()
 {
     return type_Her;
 }

 void Enemy::setType(int a)
{
     type_Her = a;
}

 int Enemy::getTypePer()
{
     return Type;
}

 void Enemy::setTypePer(int a)
{
     Type = a;
 }

 string Enemy::getName()
 {
     return Name;
 }

 void Enemy::setName(string name)
 {
     Name=name;
 }

 int Enemy::getSpeed()
 {
     return Speed;
 }

 void Enemy::setSpeed(int S)
 {
     Speed=S;
 }

 int Enemy::Damage(int k)//Урон наносится врагу
 {
        RealHealth-=k;
        if (RealHealth<0)
        {
            RealHealth=0;
            X_coordinate=0;
            Y_coordinate=0;
            return 0;
        }
        return 1;
 }
///Вызывается, когда герой действует на него
 void Enemy::Extra()
 {
     RealHealth+=50;
     Speed=2;
     std::cout<<"---------------------------------"<<this->DamageCoef<<std::endl;
     this->DamageCoef=this->DamageCoef+0.2;
     this->ExtraFeatures=1;
     std::cout<<this->DamageCoef<<std::endl;
 }

int Enemy::getX_Coord()
{
    return X_coordinate;
}

void Enemy::setX_Coord(int a)
{
    X_coordinate=a;
}
void Enemy::setY_Coord(int b)
{
    Y_coordinate=b;
}

int Enemy::getY_Coord()
{
    return Y_coordinate;
}

Enemy & Enemy:: operator = (const Enemy & right)
{
    if (this == &right)
        return *this;
    X_coordinate=right.X_coordinate;
    Y_coordinate=right.Y_coordinate;
    Speed=right.Speed;
    RegenerationRate=right.RegenerationRate;
    DamageCoef=right.DamageCoef;
//    aur=right.aur;
    type_Her=right.type_Her;
    RealHealth=right.type_Her;
    return *this;
 }



void Enemy::Move(int x, int y)
{
    X_coordinate=x;
    Y_coordinate=y;
}


void LightInfantry::Move(int x, int y)
{
    setX_Coord(x);
    setY_Coord(y);
}

void HeavyInfantry::Move(int x, int y)
{
    setX_Coord(x);
    setY_Coord(y);
}
void Aviation::Move(int x, int y)
{
     setX_Coord(x);
     setY_Coord(y);
}

