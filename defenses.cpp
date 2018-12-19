#include "defenses.h"
#include "scene.h"
///*Реалиованы нанесение урона, ремонт, перегруженные операторы, копирующие конструкторы
///
///
///


////Все проверки будут происходить в тестирующей программе (те нужно ли убирать стену или сколько денег
/// нужно отнять при ремонте)
void Wall::Damage(int loss)//loss-здорвье врага, умноженное на коэффицент урона
{
    RealStrength-=loss;
}

void Wall::Repairl()
{
    RealStrength=MaxStrength;
}
//class M
///Наносим урон врагу, но надо проверить стался ли он в живых, этим будет заниматься функция из класса врага
void Tower::BoostLevel(SpecificatTow a)
{
    towSpec=a;
    level++;
    std::cout<<towSpec.Cost<<std::endl;
}

int Tower::DamageEnemy(List<Enemy*>& enemy, Map* map)//Пока пусть просто по значению
{
    //Пройтись по списку, если враги находятся в радиусе поражения, то нанести ему урон
    int R=towSpec.radius;
    for(int i=0; i<enemy.GetSize(); ++i)
    {
        int X_enemy=enemy[i]->getX_Coord();
        int Y_enemy=enemy[i]->getY_Coord();
        if ((X_enemy<=(R+this->X_coordinate))&&(X_enemy>=(this->X_coordinate-R))&&(Y_enemy<=this->Y_coordinate+R)&&(Y_enemy>=this->Y_coordinate-R))
        {
            if (enemy[i]->Damage(this->towSpec.damageDone)==0)
            {
                enemy[i]->setinGame(0);
                map->map[X_enemy][Y_enemy].type=Plain_t;
                return 0;
            }
            return 1;
        }
    }
}

Wall & Wall::operator = (const Wall &right)
{
    if (this == &right)
        return *this;
    X_coordinate=right.X_coordinate;
    Y_coordinate=right.Y_coordinate;
    return *this;
}

Tower & Tower::operator =(const Tower &right)
{
    if (this == &right)
        return *this;
    X_coordinate=right.X_coordinate;
    Y_coordinate=right.Y_coordinate;
    towSpec=right.towSpec;
    return *this;

}

Tower::Tower(Tower &tower)
{
    X_coordinate=tower.X_coordinate;
    Y_coordinate=tower.Y_coordinate;
    towSpec=tower.towSpec;
}

Wall::Wall(Wall &wall)
{
    X_coordinate=wall.X_coordinate;
    Y_coordinate=wall.Y_coordinate;
}





























