/**
 * @file main.cpp
 *
 * @description
 * This program implements an interactive Pig Dicegame.
 *
 * @author	Júlia Maria A Guilhermino, <juh.guilhermino03@gmail.com>
 * @author Ludmilla Rodrigues, <>
 * @date	2023
 *
 */

#include "game_controller.cpp"

int main(void){
    Game_Controller game;
    // Set up simulation.
    game.initialize();
    // The Game Loop (Architecture)
    while(game.game_over() == false){
        game.process_events();
        game.update();
        game.render();
    }
}