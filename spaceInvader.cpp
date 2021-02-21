#include "spaceInvader.h"

Bullet::Bullet(int _x) : x_bullet(_x), y_bullet(0), active(true) {}

void Bullet::move() { y_bullet++; }


Player::Player(int _health) : health(_health), x_pos(0), reprPlayer('X') {}

int Player::get_health() { return health; }

void Player::reduce_health() { health--; }

int Player::get_x_pos() { return x_pos; }

void Player::move_left() {x_pos++;}

void Player::move_right() {x_pos--;}

Bullet Player::shoot() { return Bullet(x_pos); }


Alien::Alien(int _x_pos, int _y_max) : x_pos(_x_pos), y_pos(_y_max), repr('A') {}

void Alien::move() { y_pos -= speed; }

int Alien::give_damage() {
    if(!y_pos)  return attack_damage;
    else        return 0;
}

void Alien::take_damage() { health--; }

bool Alien::dead() {
    if (!health) return true;
    else         return false;
 }

Drone::Drone(int _x_pos, int _y_max) : Alien(_x_pos, _y_max){
    speed = 1;
    health = 1;
    attack_damage = 1;
    repr = 'D';
}

void Game::newDroneWave() {
    for (int i = 0; i < this->x_max; i++) {
        alien_waves.push_back(new Drone(i, this->y_max));
    }
}

Game::Game(int x_map, int y_map) : x_max(x_map), y_max(y_map), round_count(0) {
    player = new Player(5);
    // hard coded - change later
    wave_frequency = 5;
}


Game::~Game() {
    delete player;
    for (int i = 0; i < alien_waves.size(); i++) {
            delete(alien_waves[i]);
    }
    for (int j = 0; j < active_bullets.size(); j++) {
        delete(active_bullets[j]);
    }
}

void Game::shoot_bullet() {
    active_bullets.push_back(new Bullet(player->get_x_pos()));
}

void Game::damageAliens() {
    for (int i = 0; i < active_bullets.size(); i++) {
        for (int j = 0; j < alien_waves.size(); j++) {
            if ( active_bullets[i]->x_bullet == alien_waves[j]->x_pos
                                    &&
                 active_bullets[i]->y_bullet == alien_waves[j]->y_pos ) 
                 { 
                    alien_waves[j]->take_damage();
                    active_bullets[i]->active = false;
                 }
        }
    }
}

void Game::damagePlayer() {
    for (int i = 0; i < alien_waves.size(); i++) {
        if (alien_waves[i]->y_pos <=0) {
            player->reduce_health();
            alien_waves[i]->health=0;
        }
    }
}

void Game::cleanUp() {
    for (int i = 0; i < active_bullets.size(); i++) {
        if (!active_bullets[i]->active) {
            Bullet *temp = active_bullets[i];
            active_bullets.erase(active_bullets.begin()+i);
            delete temp;
            i--;
        }
    }
    for (int j = 0; j < alien_waves.size(); j++) {
        if (alien_waves[i]->health <= 0) {
            Alien *_temp = alien_waves[j];
            alien_waves.erase(alien_waves.begin()+j);
            delete _temp;
            i--;
        }
    }
}

void Game::moveAliens() {
    for (int i = 0; i < alien_waves.size(); i++) {
        alien_waves[i]->move();
    }
}

void Game::moveBullets() {
    for (int i = 0; i < active_bullets.size(); i++) {
        active_bullets[i]->move();
    }
}


void Game::moveLeft()  { player->move_left();  }
void Game::moveRight() { player->move_right(); }


// in mainWindow
void Game::nextRound() {
    round_count++;
    if (round_count % wave_frequency == 0) { newDroneWave(); }
    // ereignis schleife für move/shoot
    moveAliens();
    moveBullets();
    damageAliens();
    damagePlayer();
    // draw to virtual console
    if (player->get_health() <= 0) {
        // Dead - end game 
    }
    cleanUp();
}