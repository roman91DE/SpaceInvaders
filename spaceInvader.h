#ifndef SPACEINVADER_H
#define SPACEINVADER_H

#endif // SPACEINVADER_H

#include <vector>

struct Bullet{
    int x_bullet, y_bullet;
    bool active;
    Bullet(int _x);
    void move();
};

class Player{
    private:
        int health;
        int x_pos;
        char reprPlayer;
    public: 
        Player(int _health);
        int get_health();
        void reduce_health();
        void move_left();
        void move_right();
        int get_x_pos();
        Bullet shoot();
};



class Alien{
    protected:
        int x_pos;
        int y_pos;
        int speed;
        int attack_damage;
        int health;
        char repr;
    public:
        Alien(int _x_pos, int _y_max);
        void move();
        bool dead();
        int give_damage();
        void take_damage();
    friend class Game;
};


class Drone: public Alien{
    public:
        char repr;
        Drone(int _x_pos, int _y_max);
};


class Game {
    private:
        Player *player;
        int x_max;
        int y_max;
        std::vector<Alien*> alien_waves;
        std::vector<Bullet*> active_bullets;
        int round_count;
        int wave_frequency;
    public:
        Game(int x_map, int y_map);
        ~Game();
        void moveLeft();
        void moveRight();
        void shoot_bullet();
        void damageAliens();
        void damagePlayer();
        void newDroneWave();
        void moveAliens();
        void moveBullets();
        void nextRound();
        void cleanUp();
        
};