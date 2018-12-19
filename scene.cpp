#include "scene.h"
const int WALL   = -1;         // непроходимая ячейка
const int  BLANK  = -2;         // свободная непомеченная ячейка
//Scene::Scene():Money(maxMoney),
//{
//        map.Size_x=0;
//        map.Size_y=0;
//}
void Scene::addTower(int x, int y)
{
    Tower *tower5=new Tower;
    ForTheWay a;
//    if (map.map[x][y].type==Plain_t)
    if (Money-TowSpec[0].Cost>=0)
    {
    if (map.map[x][y].type==Plain_t)
        {
//        map.map[x][y].label=-1;
        map.map[x][y].type=Tower_t;
        if (lee(13, 4, 1, 17, a, 0)==false)
        {
//            setLabel();
            map.map[x][y].type=Plain_t;
            return;
        }
        Money-=TowSpec[0].Cost;
            tower5->setSpec(TowSpec[0]);
            map.map[x][y].label=-1;
            tower5->setLevel(1);
            tower5->Y_coordinate=y;
            tower5->X_coordinate=x;
            tower5->index=castle->getTower().GetSize();
            std::cout<<tower5->index<<std::endl;
            map.map[x][y].type=Tower_t;
            map.map[x][y].index=castle->AddTowerC(tower5);
        }
    }
//    else return;
    tower5=nullptr;
}
///Пока будет раелизовано без удаления из списа стен и без условия существования пути
/// Ошибка при промгрыше
int Scene::addWall(int x, int y)
{
    Wall *wall5=new Wall;
    ForTheWay a;
//    if (map.map[x][y].type==Plain_t)
    if (Money-WallCost>=0)
    {
    if (map.map[x][y].type==Plain_t)
        {
//            map.map[x][y].label=-1;
        map.map[x][y].type=Wall_t;
        if (lee(13, 4, 1, 17, a, 0)==false)
        {
            map.map[x][y].type=Plain_t;
//            setLabel();
            return 0;
        }
        Money-=WallCost;
            map.map[x][y].label=-1;
            wall5->Y_coordinate=y;
            wall5->X_coordinate=x;
            wall5->index=castle->getWall().GetSize();
            map.map[x][y].type=Wall_t;
//            cout<<wall5->getIndex()<<endl;
//            cout<<wall5->Y_coordinate<<endl;
            map.map[x][y].index=castle->AddWallC(wall5);
        }
    else
    {
        wall5=nullptr;
        return 0;
    }
    }
    else
    {
        wall5=nullptr;
        return 0;
    }
    wall5=nullptr;
    return 1;
}

int Scene::DamageCastle(int i)
{
        if ((lair->getEnemyTab()[i]->getX_Coord()==1)&&(lair->getEnemyTab()[i]->getY_Coord()==17))
                castle->RealStrength =castle->RealStrength-(int)(lair->getEnemyTab()[i]->getRealHealth()*lair->getEnemyTab()[i]->getDamageCoef());
        if (castle->RealStrength<=0)
        {
            castle->RealStrength=0;
            return 0;
        }
    return 1;
}

//struct SpecificatCast{
//    int Yield;//Доходность
//    int Cost;
//    int repairSpeed;
//    int MaxStrength;//Прочность
//};
///Необходимо доделать этот конструктор
Scene::Scene():Money(maxMoney), map(), TowSpec(nullptr),  EnemyNumber(0)
{
    castle=new Castle;
//    castle->castSpec=CastSpec[0];
    lair=new Lair;
    way.px=new int[20*15];
    way.py=new int[20*15];
    cout<<"==================================================="<<map.Size_x<<endl;
}

//Scene::Scene(const Map &map1, const List<Wall> wall, const List<Enemy> enemy, const List<Tower> tower):map(map1)
//{
////    cout<<"Hello"<<endl;
//}

Scene::~Scene()
{
    delete castle;
    delete lair;
    delete TowSpec;
    delete CastSpec;
}

///Буду добавлять обработку типа врага и добаление движения для разных типов

bool Scene::lee(int ay, int ax, int by, int bx, ForTheWay &a, int type)   // поиск пути из ячейки (ax, ay) в ячейку (bx, by)
{
    if (type==0)
        setLabel();
    else if (type==2) //пока не используюавиацию
        setLabel3_0();
    else
        setLabel2_0();
  int dx[4] = {1, 0, -1, 0};   // смещения, соответствующие соседям ячейки
  int dy[4] = {0, 1, 0, -1};   // справа, снизу, слева и сверху
  int d, x, y, k;
  bool stop;
//Тут будет если не равно типу равнина, враг или замок
  if (map.map[ay][ax].label == WALL || map.map[by][bx].label == WALL) return false;  // ячейка (ax, ay) или (bx, by) - стена
  // распространение волны
  d = 0;
  map.map[ay][ax].label = 0;            // стартовая ячейка помечена 0
  do {
    stop = true;// предполагаем, что все свободные клетки уже помечены
    for ( y = 0; y < map.Size_x; ++y )
      for ( x = 0;x< map.Size_y; ++x )
          if ( map.map[y][x].label == d )                         // ячейка (x, y) помечена числом d
        {
          for ( k = 0; k < 4; ++k )                    // проходим по всем непомеченным соседям
          {
             int iy=y + dy[k], ix = x + dx[k];
             if ( (iy >= 0 && iy < (map.Size_x)) && (ix >= 0) && (ix < map.Size_y) && (map.map[iy][ix].label == BLANK ))
             {
                stop = false;
    // найдены непомеченные клетки
                map.map[iy][ix].label = d + 1;
             }
          }
        }
    d++;
//    cout<<d<<endl;
  } while ( !stop && map.map[by][bx].label == BLANK );//Пока вершина не помечена или есть ячейки, которые можно пометить
  if (map.map[by][bx].label == BLANK) return false;  // путь не найден
  // восстановление пути
  if ((a.px!=nullptr)&&(a.py!=nullptr))
  {
      a.len = map.map[by][bx].label;            // длина кратчайшего пути из (ax, ay) в (bx, by) (у меня будет grid[bx, by].label)
      x = by;
      y = bx;
      d = a.len;
      while ( d > 0 )
      {
        a.px[d] = x;
        a.py[d] = y;// записываем ячейку (x, y) в путь
        d--;
        for (k = 0; k < 4; ++k)
        {
           int iy=y + dy[k], ix = x + dx[k];
           if ( (iy >= 0) && (iy < map.Size_y) && (ix >= 0) && (ix < map.Size_x)&& (map.map[ix][iy].label == d) )
          {
              x = x + dx[k];
              y = y + dy[k];           // переходим в ячейку, которая на 1 ближе к старту
              break;
          }
        }
      }
      a.px[0] = ay;
      a.py[0] = ax; // теперь px[0..len] и py[0..len] - координаты ячеек пути
  }
      return true;
}




///Размер записали уже
///Из карты занес только типы, остальное будет заполняться в ходе игры
int Scene::Record()
{
    ofstream Fd("TowerDefense.txt", ios::out);
    if(!Fd)//Перегруженный оператор (!)
    {
        cerr << "File could be opened"<<endl;
        return 0;
    }
    Fd<<map.Size_x<<endl;
    Fd<<map.Size_y<<endl;
    for(int i=0; i<map.Size_x; ++i)
    {
        for(int j=0; j<map.Size_y; ++j)
        {
            Fd<<map.map[i][j].type<<" ";
        }
        Fd<<endl;
    }
    for(int i=0; i<map.Size_x; ++i)
    {
        for(int j=0; j<map.Size_y; ++j)
        {
            Fd<<map.map[i][j].label<<" ";
        }
        Fd<<endl;
    }
    Fd<<LevelQ<<endl;
    if (TowSpec!=nullptr)
    {
        for (int i=0; i<LevelQ; ++i)
        {
            Fd<<TowSpec[i].Cost<<" "<<TowSpec[i].damageDone<<" "<<TowSpec[i].radius<<" "<<TowSpec[i].SpeedOfShoot<<endl;
        }
    }
    if (CastSpec!=nullptr)
    {
        for (int i=0; i<LevelQ; ++i)
        {
            Fd<<CastSpec[i].Cost<<" "<<CastSpec[i].MaxStrength<<" "<<CastSpec[i].repairSpeed<<" "<<CastSpec[i].Yield    <<endl;
        }
    }
    Fd<<lair->TableOfEnemies.GetSize()<<endl;
    for (int i=0; i<lair->TableOfEnemies.GetSize();++i)
    {
        Fd<<lair->TableOfEnemies[i]->getTypePer()<<" "<<lair->TableOfEnemies[i]->getType()<<endl;
    }
    return 1;
}

void Scene::SetSpec(SpecificatCast *a, SpecificatTow *b)
{
    if (LevelQ!=0)
    {
        TowSpec=new SpecificatTow[LevelQ];
        CastSpec=new SpecificatCast[LevelQ];
    }
    else return;

    for (int i=0; i< LevelQ; ++i)
    {
        TowSpec[i]=b[i];
        CastSpec[i]=a[i];
    }
}

int Scene::Reading()
{
//    cout<<"Reading"<<endl;
    ifstream Fd("TowerDefense.txt", ios::in);
    if (!Fd)
    {
        cerr<<"File could not be opened"<<endl;
        return 0;
    }
    Fd>>map.Size_x;
    cout<<map.Size_x<<endl;
    Fd>>map.Size_y;
    cout<<map.Size_y<<endl;
    map.map=new Cell*[map.Size_x];
    for (int i=0; i<map.Size_x; ++i)
    {
        map.map[i]= new Cell[map.Size_y];
    }
    for(int i=0; i<map.Size_x; ++i)
    {
        for(int j=0; j<map.Size_y; ++j)
        {
            Fd>>map.map[i][j].type;
        }
    }
    for(int i=0; i<map.Size_x; ++i)
    {
        for(int j=0; j<map.Size_y; ++j)
        {
            Fd>>map.map[i][j].label;
        }
    }
    Fd>>LevelQ;
    cout<<LevelQ<<endl;
    if (LevelQ!=0)
    {
        TowSpec=new SpecificatTow[LevelQ];
        CastSpec=new SpecificatCast[LevelQ];
        for (int i=0; i<LevelQ; ++i)
        {
            Fd>>TowSpec[i].Cost>>TowSpec[i].damageDone>>TowSpec[i].radius>>TowSpec[i].SpeedOfShoot;
        }
        for (int i=0; i<LevelQ; ++i)
             Fd>>CastSpec[i].Cost>>CastSpec[i].MaxStrength>>CastSpec[i].repairSpeed>>CastSpec[i].Yield;
    }
    int g=0;
    Fd>>g;
    lair=new Lair;
    Enemy *a;
    int h=0;
    int k=0;
    for (int i=0; i<g;++i)
    {

        Fd>>h;
        Fd>>k;
        switch(h) {
        case 0:
            a=new LightInfantry;
            a->setType(k);
            a->setTypePer(h);
            break;
        case 1:
            a=new HeavyInfantry;
            a->setType(k);
            a->setTypePer(h);
            break;
        case 2:
            a=new Aviation;
            a->setType(k);
            a->setTypePer(h);
            break;
        default:
            break;
        }
//        lair->AddEnemyT(a);//В зависимсти от типа будет вызываться нужная функция
        lair->TableOfEnemies.push_back(a);
//        cout<<lair->TableOfEnemies[i]->getType()<<endl;
    }
    return 1;
}

void Scene::AddEnemy()
{
//    Enemy *a=new LightInfantry;
//    Enemy *b=new HeavyInfantry;
//    Enemy *c=new Aviation;
//    a->setType(0);
//    a->setTypePer(0);
//    a->setRealHealth(1);
//    lair->AddEnemy1(a);
//    a=new LightInfantry;
//    a->setTypePer(0);
//    a->setType(0);
//    a->setRealHealth(2);
//    lair->AddEnemy1(a);
//    b->setTypePer(1);
//    b->setType(0);
//    b->setRealHealth(3);
//    lair->AddEnemy1(b);
//    a=new LightInfantry;
//    a->setTypePer(0);
//    a->setType(1);
//    a->setRealHealth(4);
//    lair->AddEnemy1(a);
//    c->setTypePer(2);
//    c->setType(0);
//    c->setRealHealth(5);
//    lair->AddEnemy1(c);
//    b=new HeavyInfantry;
//    b->setTypePer(1);
//    b->setType(0);
//    b->setRealHealth(6);
//    lair->AddEnemy1(b);
//    c=new Aviation;
//    c->setTypePer(2);
//    c->setType(0);
//    c->setRealHealth(7);
//    lair->AddEnemy1(c);
//    a=new LightInfantry;
//    a->setTypePer(0);
//    a->setType(1);
//    a->setRealHealth(8);
//    lair->AddEnemy1(a);
//    b=new HeavyInfantry;
//    b->setTypePer(1);
//    b->setType(0);
//    b->setRealHealth(9);
//    lair->AddEnemy1(b);
//    a=new LightInfantry;
//    a->setTypePer(0);
//    a->setType(0);
//    a->setRealHealth(10);
//    lair->AddEnemy1(a);
//    a=nullptr;
//    b=nullptr;
//    c=nullptr;
//    cout<<lair->TableOfEnemies.GetSize()<<std::endl;
//    for (int i=0; i < lair->TableOfEnemies.GetSize()-1; ++i)
//    {
//        cout<<lair->TableOfEnemies[i]->getRealHealth()<<endl;
//    }
//////    d.push_back(new Enemy);
//    //   cout<<lair->TableOfEnemies[lair->TableOfEnemies.GetSize()-1]->getRealHealth()<<endl;
}

void Scene::setLabel()
{
 for (int i=0; i<map.Size_x; ++i)
 {
     for (int j=0; j<map.Size_y;++j)
     {
         if ((map.map[i][j].type!=Plain_t)&&(map.map[i][j].type!=Enemy_t)&&(map.map[i][j].type!=Castle_t))
         {
            map.map[i][j].label=-1;
         }
         else
             map.map[i][j].label=-2;
     }
 }
}

void Scene::setLabel2_0()
{
    for (int i=0; i<map.Size_x; ++i)
    {
        for (int j=0; j<map.Size_y;++j)
        {
            if ((map.map[i][j].type!=Plain_t)&&(map.map[i][j].type!=Enemy_t)&&(map.map[i][j].type!=Castle_t)&&(map.map[i][j].type!=Wall_t))
            {
               map.map[i][j].label=-1;
            }
            else
                map.map[i][j].label=-2;
        }
    }
}

void Scene::setLabel3_0()
{
    for (int i=0; i<map.Size_x; ++i)
    {
        for (int j=0; j<map.Size_y;++j)
        {
                map.map[i][j].label=-2;
        }
    }

}

void Scene::Move()
{
//    for (int i=0; i<lair->TableOfEnemies.GetSize(); ++i)//Прохожу по всем врагам в списке и ищу кратайшие расстояния
//    for (int i=0; i<EnemyNumber; ++i)//В списке проссматриваю только тех врагов, которые вышли и логова
//    {
//        int x=lair->TableOfEnemies[i]->getX_Coord();
//        int y=lair->TableOfEnemies[i]->getY_Coord();
//        if (lee(x, y, 1, 17, way)==true)
//        {
////            cout<<"Way-----"<<way.px[1]<<" "<<way.py[1]<<endl;
//            if (way.len>=1)
//            {
//                map.map[x][y].type=Plain_t;//Враг вышел из этой клетки => клетка пустая (проблема, если 2 врага находились на одной клетке)
//                //Нужно сделать функцию, которая проходилась бы по списку врагов и проверяла их координаты
//                map.map[way.px[1]][way.py[1]].type=Enemy_t;
//                lair->TableOfEnemies[i]->Move(way.px[1],way.py[1]);
//            }
//        }
//    }
}

void Scene::AddEnemyMap()
{
    if (EnemyNumber<lair->getEnemyTab().GetSize()-1)
    {
        map.map[13][4].type=Enemy_t;
//        std::cout<<map.map[13][4].type<<std::endl;
        lair->addEnemy(EnemyNumber, 13, 4);
        ++EnemyNumber;//Количество врагов на поле стало на единицу больше
    }
}

int Scene::HeroFunc(int x, int y)//Координаты героя
{
    int R=2;
    int Y_enemy;
    int X_enemy;
    for (int i=0; i<lair->getEnemyTab().GetSize(); ++i)
    {
        if (lair->getEnemyTab()[i]->getinGame()==1)
        {
            if (lair->getEnemyTab()[i]->getExtraFeatures()!=1)
            {
            X_enemy=lair->getEnemyTab()[i]->getX_Coord();
            Y_enemy=lair->getEnemyTab()[i]->getY_Coord();
            if ((X_enemy<=(R+x))&&(X_enemy>=x)&&(Y_enemy<=y+R)&&(Y_enemy>=y-R))
            {
                if ((X_enemy!=x)&&(Y_enemy!=y))
                {
                    lair->getEnemyTab()[i]->Extra();
                     return 1;
                }
            }

        }
        }
    }
    return 0;

}

void Scene::BoostLevelTow(int i)
{
    std::cout<<castle->getTower()[i]->getLevel()<<std::endl;
    if (castle->getTower()[i]->getLevel()<5)
    {
        std::cout<<"==============================="<<std::endl;
        if (Money<TowSpec[castle->getTower()[i]->getLevel()].Cost)
            return;
            Money-=TowSpec[castle->getTower()[i]->getLevel()].Cost;
            castle->getTower()[i]->BoostLevel(TowSpec[castle->getTower()[i]->getLevel()-1]);
    }

}
void Scene::BoostLevelCast()
{
    std::cout<<castle->getLevel()<<std::endl;
    if (castle->getLevel()<5)
    {
        std::cout<<"Money="<<Money<<std::endl;
        if (Money<CastSpec[castle->getLevel()].Cost)
            return;
            std::cout<<"Cost="<<CastSpec[castle->getLevel()].Cost<<std::endl;
            Money-=CastSpec[castle->getLevel()].Cost;
            castle->BoostLevel(CastSpec[castle->getLevel()-1]);
    }

}
//SpecificatTow *TowSpec;//Таблица характеристик соотв уровню башни
//SpecificatCayst *CastSpec
//Если скорость равна 1










