#include "mywindow.h"

myWindow::myWindow() : ConsoleWindow() {
    game = new Game(64,48);
}



myWindow::~myWindow() {
    delete game;
}



void myWindow::drawCurrentState() {
    clear();
    // draw player
    setCharacter(game->player->get_x_pos(), 0, game->player->reprPlayer);
    // draw bullets
    for (unsigned int i = 0; i < game->active_bullets.size(); i++) {
        int x = game->active_bullets[i]->x_bullet;
        int y = game->active_bullets[i]->y_bullet;
        setCharacter(x,y,'I');
    }
    // draw aliens
    for (unsigned int j = 0; j < game->alien_waves.size(); j++) {
        int x2 = game->alien_waves[j]->x_pos;
        int y2 = game->alien_waves[j]->y_pos;
        setCharacter(x2, y2, game->alien_waves[j]->repr);
    }
}


void myWindow::onRefresh() {
    drawCurrentState();
    game->round_count++;
    if (game->round_count % game->wave_frequency == 0) { game->newDroneWave(); }
    // ereignis schleife für move/shoot
    if (getPressedKey() == CURSOR_LEFT)     game->moveLeft();
    if (getPressedKey() == CURSOR_RIGHT)    game->moveRight();
    if (getPressedKey() == CURSOR_UP
    || getPressedKey() == CURSOR_DOWN )     game->shoot_bullet();

    game->moveAliens();
    game->moveBullets();
    game->damageAliens();
    game->damagePlayer();

    if (game->player->get_health() <= 0) {
        writeString(0,0, "You are Dead!");
        delete game;
        game = new Game(64,48);
    }
    game->cleanUp();
}
