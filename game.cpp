#include "game.h"
///Реализовать функцию нанесения урона замку
Game::Game():window(sf::VideoMode(600, 450), "TowerDefense")
{
    scene=new Scene;
    scene->Reading();
    scene->castle->setRealStrength(scene->CastSpec[0].MaxStrength);
         ///Стены
                map_image.loadFromFile("images/Wall.jpeg");//загружаем файл для карты
                map.loadFromImage(map_image);//заряжаем текстуру картинкой
                s_map.setTexture(map);//заливаем текстуру спрайтом
         ///Вода
                map1_image.loadFromFile("images/water.png");//загружаем файл для карты
                map1.loadFromImage(map1_image);//заряжаем текстуру картинкой
                s_map1.setTexture(map1);//заливаем текстуру спрайтом
         ///Горы
                map2_image.loadFromFile("images/tilingrocksunlit.png");//Горы
                map2.loadFromImage(map2_image);//заряжаем текстуру картинкой
                s_map2.setTexture(map2);//заливаем текстуру спрайтом
         ///Равнина
                map3_image.loadFromFile("images/forIm.jpg");//загружаем файл для карты
                map3.loadFromImage(map3_image);//заряжаем текстуру картинкой
                s_map3.setTexture(map3);//заливаем текстуру спрайтом
          ///Лес
                map4_image.loadFromFile("images/FFMQ_Forest.png");//загружаем файл для карты
                map4.loadFromImage(map4_image);//заряжаем текстуру картинкой
                s_map4.setTexture(map4);//заливаем текстуру спрайтом
          ///Персонаж
                hero_image.loadFromFile("images/water.png");//загружаем файл для карты
                hero.loadFromImage(hero_image);//заряжаем текстуру картинкой
                s_hero.setTexture(hero);//заливаем текстуру спрайтом
           ///Башня
                tower_image.loadFromFile("images/tower.jpg");//загружаем файл для карты
                tower.loadFromImage(tower_image);//заряжаем текстуру картинкой
                s_tower.setTexture(tower);//заливаем текстуру спрайтом
           ///Персонаж, который двигается скачкообразно
                person_image.loadFromFile("images/person.png");//загружаем файл для карты
                person_image.createMaskFromColor(Color(255, 255, 255));
                person.loadFromImage(person_image);//заряжаем текстуру картинкой
                s_person.setTexture(person);//заливаем текстуру спрайтом
            ///Замок
                castle_image.loadFromFile("images/castle.png");//загружаем файл для карты
                castle_image.createMaskFromColor(Color(255, 255, 255));
                castle.loadFromImage(castle_image);//заряжаем текстуру картинкой
                s_castle.setTexture(castle);//заливаем текстуру спрайтом
                setText();
            ///Плюс
                plus_image.loadFromFile("images/plus.png");//загружаем файл для карты
//                plus_image.createMaskFromColor(Color(255, 255, 255));
                plus.loadFromImage(plus_image);//заряжаем текстуру картинкой
                s_plus.setTexture(plus);
            ///Мост
                most_image.loadFromFile("images/most.jpg");//загружаем файл для карты
                //plus_image.createMaskFromColor(Color(255, 255, 255));
                most.loadFromImage(most_image);//заряжаем текстуру картинкой
                s_most.setTexture(most);


}





int Game::Start()
{
//    scene->lee(13, 4, 1, 17, scene->way);
//    menu();
     Font font;//шрифт
     font.loadFromFile("CyrilicOld.TTF");
     text.setFont(font);
     text.setColor(Color::White);
     text.setCharacterSize(25);
     text.setString("Money:");//задает строку тексту
     text.setPosition(240 , 0 );//задаем позицию текста, центр камеры
     text1.setFont(font);
     text1.setColor(Color::White);
     text1.setStyle(sf::Text::Bold | sf::Text::Underlined);
     text1.setCharacterSize(20);
     text1.setString("Add:");//задает строку тексту
     text1.setPosition(0 , 0 );//задаем позицию текста, центр камеры
     hp.setFont(font);
     hp.setColor(Color::White);
     hp.setPosition(480 , 0 );
     hp.setCharacterSize(20);
     hp.setString("Hp:");
     level.setFont(font);
     level.setColor(Color::White);
     level.setPosition(380 , 0 );
     level.setCharacterSize(20);
     level.setString("Level:");
     scene->AddEnemyMap();
    float time;
    float time2;
    float time3;
    bool isMove = false;//переменная для щелчка мыши по спрайту
        Clock clock;
        Clock clock2;
        Clock clock3; //Для врагов
        while (window.isOpen())//Пока окно открыто
        {
            time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах
            clock.restart(); //перезагружает время
            DamageEnemy(time2, clock2);
            AddEnemy(time3, clock3);
            time = time/800; //скорость игры
            Move(time);
            Vector2i pixelPos = Mouse::getPosition(window);//забираем коорд курсора
            Event event;//Событие
            while (window.pollEvent(event))
            {
                if (event.type == Event::MouseButtonPressed)//если нажата клавиша мыши
                    if (event.key.code == Mouse::Left)//а именно левая
                    {
                       //Когда мы не находимся ни к каком режиме
                        isMove = true;
                        if ((pixelPos.y/30==0)&&(pixelPos.x/30)==2)
                            AddWall(time, clock, time2, clock2, time3, clock3);
                        else if ((pixelPos.y/30==0)&&(pixelPos.x/30)==3)
                        {
                            AddTower(time, clock, time2, clock2, time3, clock3);
                        }
                        else if ((scene->map.map[pixelPos.y/30][pixelPos.x/30].type==Tower_t))
                        {
                            std::cout<<"Work"<<std::endl;
                            //Повысить уровень
                            scene->BoostLevelTow(scene->map.map[pixelPos.y/30][pixelPos.x/30].index);
                        }
                        else if ((pixelPos.y/30==0)&&(pixelPos.x/30)==19)
                        {
                            scene->BoostLevelCast();
                        }
                    }
                if (event.type == sf::Event::Closed)
                    window.close();
            }
    //    if (Keyboard::isKeyPressed(Keyboard::какая-то клаиша)){какоу-то действие} herosprite.move(0.1, 0)-идем вправо (0.1-скорость)
            window.clear();//Очистка текущего окна
            ShowMap();
            playerScoreString.str("");
            playerScoreString << scene->getMoney();		//занесли в нее число очков, то есть формируем строку
            text.setString("Money:" + playerScoreString.str());
            window.draw(text);
            window.draw(text1);
            playerScoreString.str("");
            playerScoreString << scene->castle->getRealStrength();
            hp.setString("Hp:" + playerScoreString.str());
            window.draw(hp);
            playerScoreString.str("");
             playerScoreString << scene->castle->getLevel();
            level.setString("Level:" + playerScoreString.str());
            window.draw(level);
//            window.draw(scene->lair->getEnemyTab()[0]->s_enemy);
            window.display();//Окно обновляется
        }
//        std::cout<<"Money="<<scene->getMoney()<<std::endl;
//        std::cout<<"Cost="<<scene->castle->getTower()[0]->getCost()<<std::endl;
//        scene->castle->getTower()[0]->DamageEnemy(scene->lair->getEnemyTab());r
          for (int i=0; i<scene->getSize_x(); ++i)
          {
              for (int j=0; j<scene->getSize_y(); ++j)
              {
                  std::cout<< scene->map.map[i][j].type<<"  ";
          }
              std::cout<<"\n";
        }
        return 0;
}

int Game::ShowMap()
{
                for (int i = 0; i < scene->getSize_x(); i++)
                for (int j = 0; j < scene->getSize_y(); j++)
                {
                    //если встретили символ пробел, то рисуем 1й квадратик

                    switch(scene->map.map[i][j].type)
                    {
                    case 0:
                        if (((i==9)||(i==8))&&((j==7)||(j==8)||(j==9)||(j==10)||(j==11)||(j==12)))
                        {
                            s_most.setPosition(j * 30, i * 30);
                            window.draw(s_most);
                        }
                        else
                        {
                            s_map3.setPosition(j * 30, i * 30);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат
                            window.draw(s_map3);
                        }
                        break;
                    case 10:
                        s_plus.setPosition(j * 30, i * 30);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат

                        window.draw(s_plus);
                        break;
                    case 6:
                        s_map2.setPosition(j * 30, i * 30);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат

                        window.draw(s_map2);
                        break;
                    case 7:
                        s_map4.setPosition(j * 30, i * 30);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат

                        window.draw(s_map4);
                        break;
                    case 8:
                        s_map1.setPosition(j * 30, i * 30);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат

                        window.draw(s_map1);
                        break;
                    case 1:
                        s_map3.setPosition(j * 30, i * 30);
                        window.draw(s_map3);
//                        s_castle.setPosition(j * 30, i * 30);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат

//                        window.draw(s_castle);
                        break;
                    case 4:
                        s_map.setPosition(j * 30, i * 30);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат

                        window.draw(s_map);
                        break;
                    case 5:
                        if (((i==9)||(i==8))&&((j==7)||(j==8)||(j==9)||(j==10)||(j==11)||(j==12)))
                        {
                            s_most.setPosition(j * 30, i * 30);
                            window.draw(s_most);
                        }
                        else
                        {
                            s_map3.setPosition(j * 30, i * 30);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат
                            window.draw(s_map3);
                        }
                            s_person.setPosition(j * 30, i * 30);
                            window.draw(s_person);
                        break;
                    case 11:
                        s_map.setPosition(j * 30, i * 30);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат

                        window.draw(s_map);
                        break;
                    case 3:
                     s_tower.setPosition(j * 30, i * 30);
                        window.draw(s_tower);
                        break;
                    default:
                        break;
                    }
                }
}

void Game::NewWindow()
{
    bool isMove = false;//переменная для щелчка мыши по спрайту
      RenderWindow window1(sf::VideoMode(200, 100), "Tower Defense");//Создаем окно и инициалиируем размером и названием
     Clock clock;
     while (window1.isOpen())//Пока окно открыто
     {
         float time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах
         clock.restart(); //перезагружает время
         time = time/800; //скорость игры
//         Vector2i pixelPos = Mouse::getPosition(window1);//забираем коорд курсора
         Event event;//Событие
         while (window1.pollEvent(event))
         {
//             cout<<"NORM10"<<endl;
             if (event.type == Event::MouseButtonPressed)//если нажата клавиша мыши
                 if (event.key.code == Mouse::Left)//а именно левая
                 {
//                     window1.close();
                     isMove = true;//можем двигать спрайт
                  }
             if (event.type == sf::Event::Closed)
             {
//                 cout<<"NORM5"<<endl;
                 window1.close();
                 window.close();
             }
//             if (window.pollEvent(event))
//             {
//                 window1.close();
//             }

         }
 //    if (Keyboard::isKeyPressed(Keyboard::какая-то клаиша)){какоу-то действие} herosprite.move(0.1, 0)-идем вправо (0.1-скорость)
         window1.clear();//Очистка текущего окна
         playerScoreString.str("");
         playerScoreString << 0;
         hp.setString("Hp:" + playerScoreString.str());
         window.draw(hp);
         window1.draw(text);
         window1.display();//Окно обновляется
     }
     cout<<"NORM"<<endl;
}
///В этой функции в режиме добавления стен, делаем то же самое, что и в основном
/// цикле, но при нажатии на правую кнопку мыши ставятся стены
void Game::AddWall(float &time,Clock &clock, float &time2, Clock &clock2, float &time3, Clock &clock3)
{
    bool isMove = true;
    while (isMove&&window.isOpen())
    {
        time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time/800;
        Move(time);
        AddEnemy(time3, clock3);
        Vector2i pixelPos = Mouse::getPosition(window);
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::MouseButtonPressed)//если нажата клавиша мыши
                if (event.key.code == Mouse::Left)//а именно левая
                {
                    if ((pixelPos.y/30==0)&&((pixelPos.x/30==2)||(pixelPos.x/30)==3))
                        isMove=false;
                    else if ((scene->map.map[pixelPos.y/30][pixelPos.x/30].type==Tower_t))
                    {
                        std::cout<<"Work"<<std::endl;
                        //Повысить уровень
                        scene->BoostLevelTow(scene->map.map[pixelPos.y/30][pixelPos.x/30].index);
                    }
                    else if ((pixelPos.y/30==0)&&(pixelPos.x/30)==19)
                    {
                        scene->BoostLevelCast();
                    }
                    else
                        scene->addWall(pixelPos.y/30, pixelPos.x/30);
                }
            else if (event.key.code == Mouse::Right)
                {
                     isMove=false;
                }
            if (event.type == sf::Event::Closed)
                window.close();
        }
         DamageEnemy(time2, clock2);
        window.clear();
        ShowMap();
            // объявили переменную
                playerScoreString.str("");
                playerScoreString << scene->getMoney();		//занесли в нее число очков, то есть формируем строку
                text.setString("Money:" + playerScoreString.str());
        window.draw(text);
        window.draw(text1);
        playerScoreString.str("");
        playerScoreString << scene->castle->getRealStrength();
        hp.setString("Hp:" + playerScoreString.str());
        window.draw(hp);
        playerScoreString.str("");
         playerScoreString << scene->castle->getLevel();
        level.setString("Level:" + playerScoreString.str());
        window.draw(level);
        window.display();
    }
}

void Game::AddTower(float &time, Clock &clock, float &time2, Clock &clock2, float &time3, Clock &clock3)
{
    bool isMove = true;
    while (isMove&&window.isOpen())//Пока окно открыто
    {
        time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах
        clock.restart(); //перезагружает время
        time = time/800; //скорость игры
        Move(time);
        AddEnemy(time3, clock3);
        Vector2i pixelPos = Mouse::getPosition(window);//забираем коорд курсора
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::MouseButtonPressed)//если нажата клавиша мыши
                if (event.key.code == Mouse::Left)//а именно левая
                {
                    if ((pixelPos.y/30==0)&&((pixelPos.x/30==2)||(pixelPos.x/30)==3))
                        isMove=false;
                    else if ((scene->map.map[pixelPos.y/30][pixelPos.x/30].type==Tower_t))
                    {
                        std::cout<<"Work"<<std::endl;
                        //Повысить уровень башни
                        scene->BoostLevelTow(scene->map.map[pixelPos.y/30][pixelPos.x/30].index);
                    }
                    else if ((pixelPos.y/30==0)&&(pixelPos.x/30)==19)
                    {
                        scene->BoostLevelCast();
                    }
                    else
                    {
                        scene->addTower(pixelPos.y/30, pixelPos.x/30);
                    }
                }
            else if (event.key.code == Mouse::Right)
                {
                     isMove=false;
                }
            if (event.type == sf::Event::Closed)
                window.close();
        }
        DamageEnemy(time2, clock2);
        window.clear();//Очистка текущего окна
        ShowMap();
        playerScoreString.str("");
        playerScoreString << scene->getMoney();		//занесли в нее число очков, то есть формируем строку
        text.setString("Money:" + playerScoreString.str());
        window.draw(text);
        window.draw(text1);
        playerScoreString.str("");
        playerScoreString << scene->castle->getRealStrength();
        hp.setString("Hp:" + playerScoreString.str());
        window.draw(hp);
        playerScoreString.str("");
         playerScoreString << scene->castle->getLevel();
        level.setString("Level:" + playerScoreString.str());
        window.draw(level);
        window.display();//Окно обновляется
//            Show(&window);
    }
}
///Все время останавливается на 1 17 (надо предусмотреть удаление, если дошел до нужной точки) (при удаллении ставил на
/// (0.0) тк там всегда будет стена
/// Двигаются по кратчайшему расстоянию, но ломают все стены
//Нужно добавить движение для тяжелой пехоты
void Game::Move(float &time)
{
    for (int i=0; i<scene->EnemyNumber; ++i)//В списке проссматриваю только тех врагов, которые вышли и логова
    {
        int x=scene->lair->getEnemyTab()[i]->getX_Coord();
        int y=scene->lair->getEnemyTab()[i]->getY_Coord();
        if ((x==1)&&(y==17))
        {
            DamageCastle(i);
        }
//        std::cout<<scene->EnemyNumber<<std::endl;
        if (EnemyWin()==0)//Всего 9 врагов выходят из логова
            NewWindow();
        Hero(i);
        if (scene->lee(x, y, 1, 17, scene->way, scene->lair->getEnemyTab()[i]->getTypePer())==true)
        {
//            std::cout<<"X Y "<<scene->lair->getEnemyTab()[0]->getX_Coord()<<" "<<scene->lair->getEnemyTab()[0]->getY_Coord()<<endl;
            scene->map.map[x][y].type=Plain_t;//Поставил координаты персонажа Plain_t, но никуда не двинул
            if (scene->way.len>=1)
            {
                if (scene->lair->getEnemyTab()[i]->getTypePer()!=2)
                {
                if(scene->lair->getEnemyTab()[i]->s_enemy.getPosition().y/30>0)
                {
                    //Определение направления движения
                    if (scene->lair->getEnemyTab()[i]->getSpeed()==1)
                    {
                       EnemyMove(i, time);
                    }
                    else if(scene->lair->getEnemyTab()[i]->getSpeed()==2)
                    {
                        EnemyMove(i, time);
                        int x=scene->lair->getEnemyTab()[i]->getX_Coord();
                        int y=scene->lair->getEnemyTab()[i]->getY_Coord();
                        if (scene->lee(x, y, 1, 17, scene->way, scene->lair->getEnemyTab()[i]->getTypePer())==true)
                        {
                             EnemyMove(i, time);
                        }
                    }
                    //Определение направления движения
                scene->lair->getEnemyTab()[i]->setX_Coord((int)(scene->lair->getEnemyTab()[i]->s_enemy.getPosition().y)/30+1);
                scene->lair->getEnemyTab()[i]->setY_Coord((int)(scene->lair->getEnemyTab()[i]->s_enemy.getPosition().x)/30);
                     scene->map.map[(int)(scene->lair->getEnemyTab()[i]->s_enemy.getPosition().y)/30+1][(int)(scene->lair->getEnemyTab()[i]->s_enemy.getPosition().x)/30].type=Enemy_t;
               }
                }
            }
        }
    }
}
///Нанести урон стене в коичестве оставшегося здоровья на коэффицент урона, если прочность стены стала нулевой, то разрушить ее
/// и враг может встать на ее место
///Создам еще один таймер для нанесения урона стене, буду наносить урон стене каждые 3 секунды
//void Game::Move(float &time)
//{
//    for (int i=0; i<scene->EnemyNumber; ++i)//В списке проссматриваю только тех врагов, которые вышли и логова
//    {
//        int x=scene->lair->getEnemyTab()[i]->getX_Coord();
//        int y=scene->lair->getEnemyTab()[i]->getY_Coord();
//        if ((x==1)&&(y==17))
//        {
//            DamageCastle(i);
//        }
////        std::cout<<scene->EnemyNumber<<std::endl;
//        if (EnemyWin()==0)//Всего 9 врагов выходят из логова
//            NewWindow();
//        Hero(i);
//        if (scene->lair->getEnemyTab()[i]->Type==1)
//        {
//            scene->lee(x, y, 1, 17, scene->way, 1);//без стен
//            if (scene->map.map[scene->way.px[1]][scene->way.py[1]].type==Wall_t)
//            {
//                int dem= scene->castle->getWall()[scene->map.map[scene->way.px[1]][scene->way.py[1]].index]->getRealStrength();
//                int q=scene->way.len;
//                int u=scene->lair->getEnemyTab()[i]->getRealHealth();
//                int k=scene->lair->getEnemyTab()[i]->getDamageCoef();
//                scene->lee(x, y, 1, 17, scene->way, 0);
//                if (q+(dem/(u*k)+1)<scene->way.len)
//            }
////            int q=
//        }
//        if (scene->lee(x, y, 1, 17, scene->way, 1)==true)
//        {
//            if (scene->map.map[scene->way.px[1]][scene->way.py[1]].type==Wall_t)
//            {
//                scene->castle->getWall()[scene->map.map[scene->way.px[1]][scene->way.py[1]].index]->Damage(8);
//                scene->lee(x, y, 1, 17, scene->way, 0);
//            }

////            std::cout<<"X Y "<<scene->lair->getEnemyTab()[0]->getX_Coord()<<" "<<scene->lair->getEnemyTab()[0]->getY_Coord()<<endl;
//            scene->map.map[x][y].type=Plain_t;//Поставил координаты персонажа Plain_t, но никуда не двинул
//            if (scene->way.len>=1)
//            {
//                if(scene->lair->getEnemyTab()[i]->s_enemy.getPosition().y/30>0)
//                {
//                    //Определение направления движения
//                    if (scene->lair->getEnemyTab()[i]->getSpeed()==1)
//                    {
//                       EnemyMove(i, time);
//                    }
//                    else if(scene->lair->getEnemyTab()[i]->getSpeed()==2)
//                    {
//                        EnemyMove(i, time);
//                        int x=scene->lair->getEnemyTab()[i]->getX_Coord();
//                        int y=scene->lair->getEnemyTab()[i]->getY_Coord();
//                        if (scene->lee(x, y, 1, 17, scene->way, 1)==true)
//                        {
//                             EnemyMove(i, time);
//                        }
//                    }
//                    //Определение направления движения
//                scene->lair->getEnemyTab()[i]->setX_Coord((int)(scene->lair->getEnemyTab()[i]->s_enemy.getPosition().y)/30+1);
//                scene->lair->getEnemyTab()[i]->setY_Coord((int)(scene->lair->getEnemyTab()[i]->s_enemy.getPosition().x)/30);
//                     scene->map.map[(int)(scene->lair->getEnemyTab()[i]->s_enemy.getPosition().y)/30+1][(int)(scene->lair->getEnemyTab()[i]->s_enemy.getPosition().x)/30].type=Enemy_t;
//                }
//            }
//        }
//    }
//}



void Game::EnemyMove(int i, float &time)
{
    if ((scene->way.px[1]-scene->way.px[0]>0)&&((scene->way.py[1]-scene->way.py[0]==0)))
         scene->lair->getEnemyTab()[i]->s_enemy.move(0, 0.05*time);
    if ((scene->way.px[1]-scene->way.px[0]<0)&&((scene->way.py[1]-scene->way.py[0]==0)))
         scene->lair->getEnemyTab()[i]->s_enemy.move(0, -0.05*time);
    if ((scene->way.px[1]-scene->way.px[0]==0)&&((scene->way.py[1]-scene->way.py[0]>0)))
         scene->lair->getEnemyTab()[i]->s_enemy.move(0.05*time, 0);
    if ((scene->way.px[1]-scene->way.px[0]==0)&&((scene->way.py[1]-scene->way.py[0]<0)))
        scene->lair->getEnemyTab()[i]->s_enemy.move(-0.05*time, 0);
}

void Game::Hero(int i)
{
    if (scene->lair->getEnemyTab()[i]->getType()==1)
    {
        int x=scene->lair->getEnemyTab()[i]->getX_Coord();
        int y=scene->lair->getEnemyTab()[i]->getY_Coord();
        scene->HeroFunc(x, y);
    }
}

void Game::DamageCastle(int i)
{
    if (scene->DamageCastle(i)==0)
    {
//        playerScoreString.str("");
//        playerScoreString << scene->castle->getRealStrength();
        text.setPosition(40, 30);
        text.setString("Game over!");
//        window.draw(hp);
        NewWindow();
        std::cout<<"You loser"<<std::endl;
        //Нужно будет обрабатывать события
    }
    scene->lair->getEnemyTab()[i]->setinGame(0);
    scene->lair->getEnemyTab()[i]->setX_Coord(0);
    scene->lair->getEnemyTab()[i]->setY_Coord(0);
}

void Game::DamageEnemy(float &time, Clock &clock)
{
    time=clock.getElapsedTime().asSeconds();
    for (int i=0; i<scene->castle->getTower().GetSize();++i)
    if(time>1)
    {
//        std::cout<<scene->lair->getEnemyTab()[0]->getRealHealth()<<std::endl;
        scene->castle->getTower()[i]->DamageEnemy(scene->lair->getEnemyTab(), &((scene)->map));

        clock.restart();
    }
}

void Game::AddEnemy(float &time, Clock &clock)
{
    time=clock.getElapsedTime().asSeconds();
    if (time>2)
    {
        scene->AddEnemyMap();
        clock.restart();
    }
}

void Game::setText()
{
    for (int i=0; i<scene->lair->getEnemyTab().GetSize(); ++i)
    {
//        if (scene->lair->getEnemyTab()[i]->getType()==0)
//        {
//            scene->lair->getEnemyTab()[i]->enemy_image.loadFromFile("images/person.png");
//            scene->lair->getEnemyTab()[i]->enemy.loadFromImage(scene->lair->getEnemyTab()[0]->enemy_image);
//            scene->lair->getEnemyTab()[i]->s_enemy.setTexture(scene->lair->getEnemyTab()[0]->enemy);
//            scene->lair->getEnemyTab()[i]->s_enemy.setPosition(4*30, 13*30-30);
//        }
//        else if(scene->lair->getEnemyTab()[i]->getType()==1)
//        {
//            scene->lair->getEnemyTab()[i]->enemy_image.loadFromFile("images/TANK.jpg");
//            scene->lair->getEnemyTab()[i]->enemy.loadFromImage(scene->lair->getEnemyTab()[0]->enemy_image);
//            scene->lair->getEnemyTab()[i]->s_enemy.setTexture(scene->lair->getEnemyTab()[0]->enemy);
//            scene->lair->getEnemyTab()[i]->s_enemy.setPosition(4*30, 13*30-30);
//        }
        scene->lair->getEnemyTab()[i]->enemy_image.loadFromFile("images/person.png");
        scene->lair->getEnemyTab()[i]->enemy.loadFromImage(scene->lair->getEnemyTab()[0]->enemy_image);
        scene->lair->getEnemyTab()[i]->s_enemy.setTexture(scene->lair->getEnemyTab()[0]->enemy);
        scene->lair->getEnemyTab()[i]->s_enemy.setPosition(4*30, 13*30-30);
    }
}



void Game::menu() {
//    RenderWindow window1(sf::VideoMode(600, 450), "TowerDefense");
//    Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
//    menuTexture1.loadFromFile("images/111.png");
//    menuTexture2.loadFromFile("images/222.png");
//    menuTexture3.loadFromFile("images/333.png");
//    aboutTexture.loadFromFile("images/TD.jpg");
//    menuBackground.loadFromFile("images/TD.jpg");
//    Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), about(aboutTexture), menuBg(menuBackground);
//    bool isMenu = 1;
//    int menuNum = 0;
//    menu1.setPosition(100, 30);
//    menu2.setPosition(100, 90);
//    menu3.setPosition(100, 150);
//    menuBg.setPosition(0, 0);

//    //////////////////////////////МЕНЮ///////////////////
//    while (isMenu)
//    {
//        menu1.setColor(Color::White);
//        menu2.setColor(Color::White);
//        menu3.setColor(Color::White);
//        menuNum = 0;
//        window1.clear(Color(129, 181, 221));
//        if (IntRect(100, 30, 300, 50).contains(Mouse::getPosition(window1))) { menu1.setColor(Color::Black); menuNum = 1; }
//        if (IntRect(100, 90, 300, 50).contains(Mouse::getPosition(window1))) { menu2.setColor(Color::Black); menuNum = 2; }
//        if (IntRect(100, 150, 300, 50).contains(Mouse::getPosition(window1))) { menu3.setColor(Color::Black); menuNum = 3; }



//        if (Mouse::isButtonPressed(Mouse::Left))
//        {
//            if (menuNum == 1) isMenu = false;//если нажали первую кнопку, то выходим из меню
//            if (menuNum == 2) { window1.draw(about); window1.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
//            if (menuNum == 3)  { window1.close(); isMenu = false; }

//        }


//        window1.draw(menuBg);
//        window1.draw(menu1);
//        window1.draw(menu2);
//        window1.draw(menu3);

//        window1.display();
//    }
//    ////////////////////////////////////////////////////
//    scene->AddEnemyMap();
        Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
        menuTexture1.loadFromFile("images/111.png");
        menuTexture2.loadFromFile("images/222.png");
        menuTexture3.loadFromFile("images/333.png");
        aboutTexture.loadFromFile("images/TD.jpg");
        menuBackground.loadFromFile("images/TD.jpg");
        Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), about(aboutTexture), menuBg(menuBackground);
        bool isMenu = 1;
        int menuNum = 0;
        menu1.setPosition(100, 30);
        menu2.setPosition(100, 90);
        menu3.setPosition(100, 150);
        menuBg.setPosition(0, 0);
    bool isMove = false;//переменная для щелчка мыши по спрайту


                while (isMenu)
                {

                    menu1.setColor(Color::White);
                    menu2.setColor(Color::White);
                    menu3.setColor(Color::White);
                    menuNum = 0;
                    window.clear(Color(129, 181, 221));
                    if (IntRect(100, 30, 300, 50).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Black); menuNum = 1; }
                    if (IntRect(100, 90, 300, 50).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Black); menuNum = 2; }
                    if (IntRect(100, 150, 300, 50).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Black); menuNum = 3; }

                    if (Mouse::isButtonPressed(Mouse::Left))
                    {
                        if (menuNum == 1) isMenu = false;//если нажали первую кнопку, то выходим из меню
                        if (menuNum == 2) { window.draw(about); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
                        if (menuNum == 3)  { window.close(); isMenu = false; }

                    }
//            Move(time);
            Vector2i pixelPos = Mouse::getPosition(window);//забираем коорд курсора
            Event event;//Событие
            while (window.pollEvent(event))
            {
                if (event.type == Event::MouseButtonPressed)//если нажата клавиша мыши
                    if (event.key.code == Mouse::Left)//а именно левая
                    {
                        isMove = true;
                    }
                if (event.type == sf::Event::Closed)
                    window.close();
            }
                    window.draw(menuBg);
                    window.draw(menu1);
                    window.draw(menu2);
                    window.draw(menu3);

            window.display();//Окно обновляется

                }
}

void Game::Text()
{
    Font font;//шрифт
     font.loadFromFile("CyrilicOld.TTF");
     text.setFont(font);
     text.setColor(Color::White);
     text.setStyle(sf::Text::Bold | sf::Text::Underlined);
     text.setCharacterSize(25);
     text.setString("Money:");//задает строку тексту
     text.setPosition(250 , 0 );//задаем позицию текста, центр камеры
     text1.setFont(font);
     text1.setColor(Color::White);
     text1.setStyle(sf::Text::Bold | sf::Text::Underlined);
     text1.setCharacterSize(20);
     text1.setString("Add:");//задает строку тексту
     text1.setPosition(0 , 0 );//задаем позицию текста, центр камеры
}

int Game::EnemyWin()
{
    if ((scene->EnemyNumber==9)&&(scene->castle->getRealStrength()>0))//Всего 9 врагов выходят из логова
    {
        for (int i=0; i<scene->lair->getEnemyTab().GetSize(); ++i)
        {
            if(scene->lair->getEnemyTab()[i]->getinGame()!=0)
                return 1;
        }
        text.setPosition(40, 30);
        text.setString("You Win!");
        return 0;
    }
    return 1;
}

