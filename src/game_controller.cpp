/**
 * Controle do jogo
 * 
*/

#include <iostream>
#include <string>
#include <vector>
#include "player.cpp"
#include "dice.cpp"
using namespace std;

class Game_Controller {
    private:
        //representam as ações do jogo
        enum game_actions {
            HOLD=0,
            ROOL,
            QUIT
        };

        /// String representation for the dice's faces (Unicode).
        string dice_faces[6] = { "\u2680", "\u2681", "\u2682", "\u2683", "\u2684", "\u2685" };

        //para controlar a progressão do jogo e das ações
        enum game_state_e {
            STARTING=0,       //< Beginning the game.
            WELCOME,          //< Opening messasges.
            PLAYING,          //< Where the game action takes place.
            ROLLING,          //< We roll the dice to get a face number.
            HOLDING,          //< User asked to hold and pass turn to the next player.
            UPDATING_SCORE,   //< Update the score board and show command issued in the turn.
            QUITTING,         //< User might want to quit (before game finishes), need to confirm.
            ENDING,           //< Closing the game (final message).
        };

        //criando as instacias da classe Player que representam os jogadores
        Player p_human; 
        Player p_machine;

        //variaveis que controlam o estado do jogo
        bool asked_to_quite;
        bool end_game = false;
        int game_state;


    public:
        //=== Common methods for the Game Loop design pattern.
        void initialize(void){
            //sortear qual jogador vai começar primeiro
            //perguntar o nome do jogador
            //definit status do jogo
        };

        /// Renders the game to the user.
        void render(void) const{
            if ( game_state == game_state_e::STARTING ){
                // Do nothing in this state.
            } else if ( game_state == game_state_e::WELCOME){
                // Welcome msg and rules.
            } else if ( game_state == game_state_e::PLAYING ){

            } else if ( game_state == game_state_e::ROLLING){

            } else if ( game_state == game_state_e::HOLDING ){

            } else if ( game_state == game_state_e::UPDATING_SCORE ){

            } else if ( game_state == game_state_e::ENDING ){

            } else if ( game_state == game_state_e::QUITTING ){

            }
        };
        
        /// Update the game based on the current game state.
        void update(void){
            if (game_state == game_state_e::STARTING ){
                // Registrar no Dice de quem começa

                //Go to WELCOME state
                game_state = game_state_e::WELCOME;
            } else if ( game_state == game_state_e::WELCOME ){
                // Go to PLAY state.
                game_state = game_state_e::PLAYING;
            } else if ( game_state == game_state_e::PLAYING ){

            } else if ( game_state == game_state_e::ROLLING ){

            } else if ( game_state == game_state_e::HOLDING ){

            } else if ( game_state == game_state_e::UPDATING_SCORE ){

            } else if ( game_state == game_state_e::QUITTING ){

            } else {
                // Do nothing in these states.
                //  + ENDING
            }
        };

        /// Process user input events, depending on the current game state.
        void process_events(void){
            if ( game_state == game_state_e::STARTING or game_state == game_state_e::ROLLING or game_state == game_state_e::HOLDING ){
                // Do nothing, no interaction in these states.
            }
            else if ( game_state == game_state_e::WELCOME ){

            }
            else if ( game_state == game_state_e::PLAYING ){

            }
            else if ( game_state == game_state_e::UPDATING_SCORE ){

            }
            else if ( game_state == game_state_e::QUITTING ){

            }
        };
        /// Returns true when the user wants to quit the game.
        bool game_over(void){
            end_game = true;
            return end_game;
        }; 

};