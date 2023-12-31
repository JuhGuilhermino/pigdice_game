/**
 * @file main.cpp
 *
 * @description
 * This program implements an interactive Pig Dicegame.
 *
 * @author	Júlia Maria A Guilhermino, <juh.guilhermino03@gmail.com>
 * @author  Ludmilla Rodrigues, <ludmillarodr178@gmail.com>
 * @date	2023
 *
 */

#include "game_controller.cpp"

int main(void){
    Game_Controller game;
    // Set up simulation.
    game.initialize();
    // The Game Loop (Architecture)
    while(game.get_end_game() == false){
        game.process_events();
        game.update();
        game.render();
    }
}