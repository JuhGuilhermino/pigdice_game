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
        //para controlar a progressão do jogo e das ações
        enum game_state_e {
            STARTING=0,       //< Beginning the game.
            WELCOME,          //< Opening messasges.
            PLAYING,          //< Where the game action takes place.
            ROLLING,          //< We roll the dice to get a face number.
            HOLDING,          //< User asked to hold and pass turn to the next player. 
            UPDATING_SCORE,   //< Update the score board and show command issued in the turn.
            JOKER,            //<
            QUITTING,         //< User might want to quit (before game finishes), need to confirm.
            ENDING,           //< Closing the game (final message).
        };

        //representam as ações do jogo
        enum game_actions_e {
            HOLD=0, //< Stop the turn
            ROOL, //< Rool the dice
            QUIT //< Quit the game
        };

        /// String representation for the dice's faces (Unicode).
        string dice_faces[6] = { "\u2680", "\u2681", "\u2682", "\u2683", "\u2684", "\u2685" };

        bool end_game = false; 
        int game_state;           // controle das ações dos jogadores
        int game_action;         // controle dos estados
        int number_of_players;    // número de jogadores
        vector  <Player> players; // vetor com todos os objetos jogadores
        int current_player_index; // indice do jogador atual
        int starting_player_index;// indice do jogador que inicia os turnos
        Dice dice;                // cria uma instacia da classe Dice
        int number_of_turns;      // marca o número do turno
        bool ask_quit_game;
        

    public:
        //=== Common methods for the Game Loop design pattern.
        void initialize(void){
            //cria uma instancia da classe Player que represneta a IA
            Player machine;
            players.push_back(machine); //1º indice do vetor sempre é a máquina

            //solicitar o número de jogadores
            cout << "Informs the number of human players between 1 and 4:  ";
            cin >> number_of_players;

            //verifica se o jogo suporta o numero de jogadores informados
            while (number_of_players > 4){
                    cout << "Invalid number. Please try again." << endl;
                    cout << "Informs the number of human players between 1 and 4:  ";
                    cin >> number_of_players;
            }

            //cria uma instacia de Player para cada jogador e solicitar o nome dos jogadores humanos
            for (int i = 0; i < number_of_players; i++) {
                Player new_player;
                new_player.set_name();
                players.push_back(new_player);
            }            

            //define o jogador inicial aleatóriamente
            starting_player_index = dice.choose_player(players.size());

            //atualiza o estado para iniciar o jogo
            game_state = game_state_e::STARTING;
        };


        /// Process user input events, depending on the current game state.
        void process_events(void){
            if ( game_state == game_state_e::STARTING or game_state == game_state_e::ROLLING or game_state == game_state_e::HOLDING ){
                // Do nothing, no interaction in these states.
            } else if ( game_state == game_state_e::WELCOME ){
                //Dar inicio ao jogo
                cout << "Press <Enter> to start the match." << endl;
                cin.ignore(); //espera o usuario pressionar enter

            } else if ( game_state == game_state_e::PLAYING ){
                
                if (current_player_index == 0) {
                    //current player is the machine 
                    //draw the action
                    game_action = game_actions_e(dice.draw_ia_actions()); 

                } else {
                    char answer;

                    //current player is a human
                    cout << "Commands syntax:" << endl;
                    cout << " 'h' + <Enter> -> HOLD (add turn total and pass turn over)." << endl;
                    cout << " 'r' + <Enter> -> ROLL the dice." << endl;
                    cout << " 'q' + <Enter> -> quit the match (no winner)." << endl;
                    cout << "Enter command >> ";
                    cin >> answer;

                    //check input
                    while (answer != 'r' && answer != 'h' && answer != 'q'){
                        cout << "Invalid command. Please try again." << endl;
                        cout << "Enter command >> ";
                        cin >> answer;
                    }

                    //defines the action of the current player
                    if (answer == 'r') { game_action = game_actions_e::ROOL;}
                    if (answer == 'h') { game_action = game_actions_e::HOLD;}
                    if (answer == 'q') { game_action = game_actions_e::QUIT;}
                }
            } else if ( game_state == game_state_e::UPDATING_SCORE){

            } else if ( game_state == game_state_e::JOKER ){
                cout << "Do you want to use you JOKER?" << endl;
                cout << " 'y' + <Enter> -> YES" << endl;
                cout << " 'n' + <Enter> -> NO" << endl;
                cout << "Enter your choice >> ";
                
                cout << "Invalid command. Please try again." << endl;
                cout << "Enter your choice >> ";

            } else if ( game_state == game_state_e::QUITTING ){
                char answer;

                cout << "Are you sure you want to exit the game?" << endl;
                cout << " 'y' + <Enter> -> YES" << endl;
                cout << " 'n' + <Enter> -> NO" << endl;
                cout << "Enter your choice >> ";
                cin >> answer;

                //check input
                while (answer != 'y' && answer != 'n'){
                    cout << "Invalid command. Please try again." << endl;
                    cout << "Enter your choice >> ";
                    cin >> answer;
                }

                //defines the action
                if (answer == 'y') { ask_quit_game == true; }
                if (answer == 'n') { ask_quit_game == false; }
            }
        };

        /// Update the game based on the current game state.
        void update(void){
            if (game_state == game_state_e::STARTING ){
                game_state = game_state_e::WELCOME; //Go to WELCOME state

            } else if ( game_state == game_state_e::WELCOME ){
                number_of_turns = 1; // Starts the counting of turns
                current_player_index = starting_player_index; // Update the current player
                game_state = game_state_e::PLAYING; // Go to PLAY state.

            } else if ( game_state == game_state_e::PLAYING ){
                //process the user's command based on the input.
                if (game_action == game_actions_e::HOLD) { game_state == game_state_e::HOLDING;}
                if (game_action == game_actions_e::QUIT) { game_state == game_state_e::QUITTING;}
                if (game_action == game_actions_e::ROOL) { game_state == game_state_e::ROLLING;}
                
            } else if ( game_state == game_state_e::ROLLING ){
                int point = dice.roll_dice(); 

                //update score of the player in current turn
                players[current_player_index].set_turn_score(point);

                //update geral score player of the player in game
                players[current_player_index].update_score();

                //check if the player won the game
                if (players[current_player_index].get_score() >= 100) {
                    game_over(); //finish the game
                    game_state == game_state_e::ENDING; //Go to END state
                } else if (point == 1) {
                    game_action = game_actions_e::HOLD; //end ther turn fot current player
                    game_state == game_state_e::UPDATING_SCORE
                    ; //Go to UPDATE state
                }else {
                    // has no winner
                    game_state == game_state_e::UPDATING_SCORE
                    ; //Go to UPDATE state
                }
        
            } else if ( game_state == game_state_e::HOLDING ){
                game_state == game_state_e::UPDATING_SCORE; //Go to UPDATE state
        
            } else if ( game_state == game_state_e::UPDATING_SCORE ){
                if (game_action == game_actions_e::HOLD) {
                    //upgrade to next player
                    current_player_index ++; 
                    if (current_player_index > number_of_players-1){
                        current_player_index = 0; //the next player is the machine
                    }
                    //upgrade to next turn
                    if (current_player_index == starting_player_index) {
                        number_of_turns ++;
                    }
                }
                game_state == game_state_e::PLAYING; //Go to PLAY state 

            } else if ( game_state == game_state_e::QUITTING ){
                if (ask_quit_game ==  true) {
                    game_over(); //finish the game
                    game_state == game_state_e::ENDING; //Go to END state
                }
                if (ask_quit_game ==  false) {
                    game_state == game_state_e::PLAYING; //Go to PLAY state
                }   
            } else {
                // Do nothing in these states.
                //  + ENDING
            }
        };

        /// Renders the game to the user.
        void render(void) const{
            if ( game_state == game_state_e::STARTING ){
                // Do nothing in this state.
            } else if ( game_state == game_state_e::WELCOME){
                // Welcome msg and rules.
                cout << "WELCOME" << endl;

            } else if ( game_state == game_state_e::PLAYING ){
                //Exibe de quem é a vez
                cout << ">>> " << number_of_turns << "º TURN" << endl;
                cout << ">>> The current player is:" << players[current_player_index].get_name() << endl;
                
            } else if ( game_state == game_state_e::ROLLING){
                cout << ">>> Requested action: 'ROOL" << endl;
                
            } else if ( game_state == game_state_e::HOLDING ){
                cout << ">>> Requested action: 'HOLD" << endl;
                
            } else if ( game_state == game_state_e::UPDATING_SCORE ){
                cout << "PLACAR" << endl;

            } else if ( game_state == game_state_e::ENDING ){
                if (game_action == game_actions_e::ROOL) {
                    cout << ">> Contratulations! The winner is " << players[current_player_index].get_name() << "!" << endl;
                }
                if (game_action == game_actions_e::QUIT) {
                    cout << ">> Goodbye..." << endl;
                }
                cout << "GAME HISTORY" << endl;
            
            } else if ( game_state == game_state_e::QUITTING ){
                cout << ">>> Requested action: 'QUIT" << endl;
            }
        };

        /// Returns true when the user wants to quit the game.
        bool game_over(void){
            end_game = true;
            return end_game;
        }; 

};