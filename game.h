#ifndef GAME
#define GAME
#include <SFML/Graphics.hpp>
//#include <Text.hpp>
using namespace sf;
#include "scene.h"
#include <sstream>
class Game
{
private:
    RenderWindow window;
    Scene *scene;
    Sprite s_map;
    Sprite s_map1;
    Sprite s_map2;
    Sprite s_map3;
    Sprite s_map4;
    Image map_image;
    Texture map;
    Image map1_image;
    Texture map1;
    Image map2_image;
    Texture map2;
    Image map3_image;
    Texture map3;
    Image map4_image;
    Texture map4;
    Sprite s_hero;
    Image hero_image;
    Texture hero;
    Sprite s_tower;
    Image tower_image;
    Texture tower;
    Sprite s_person;
    Image person_image;
    Texture person;
    Sprite s_castle;
    Image castle_image;
    Texture plus;
    Sprite s_plus;
    Image plus_image;
    Texture castle;
    sf::Text text;
    sf::Text text1;
    sf::Text hp;
    sf::Text level;
    Texture most;
    Sprite s_most;
    Image most_image;
    std::ostringstream playerScoreString;
public:
    Game();
    int Start();
    int ShowMap();
    void NewWindow();
    void AddWall(float &time, Clock &clock, float &time2, Clock &clock2, float &time3, Clock &clock3);
    void AddTower(float &time, Clock &clock, float &time2, Clock &clock2, float &time3, Clock &clock3);
    void Move(float &time);
    void EnemyMove(int i, float &time);
    void Hero(int i);
    void DamageCastle(int i);
    void DamageEnemy(float &time, Clock &clock);
    void AddEnemy(float &time, Clock &clock);
    void setText();
    void menu();
    void Text();
    int EnemyWin();
};

#endif // GAME
