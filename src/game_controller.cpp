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
            STARTING=0,        //< Beginning the game.
            WELCOME,          //< Opening messasges.
            PLAYING,          //< Where the game action takes place.
            ROLLING,          //< We roll the dice to get a face number.
            HOLDING,          //< User asked to hold and pass turn to the next player. 
            UPDATING_SCORE,   //< Update the score board and show command issued in the turn.
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

        bool end_game=false;      // 
        int game_state;           // controle dos estados
        char game_action;         // controla as ações do jogadores
        int number_of_players;    // número de jogadores
        vector <Player> players;  // vetor com todos os objetos jogadores
        int current_player_index; // indice do jogador atual
        int starting_player_index;// indice do jogador que inicia os turnos
        Dice dice;                // cria uma instacia da classe Dice
        int number_of_turns;      // marca o número do turno
        bool ask_quit_game;       // 
        int point;                //número que saiu no dado na jogada atual
        

    public:
        bool get_end_game(){
            return end_game;
        };

        // Returns true when the user wants to quit the game.
        void game_over(){
            end_game = true;
            return;
        }; 

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
            if ( game_state == game_state_e::STARTING || game_state == game_state_e::ROLLING || game_state == game_state_e::HOLDING ){
                // Do nothing, no interaction in these states.
            } else if ( game_state == game_state_e::WELCOME ){
                char answer;
                //Dar inicio ao jogo
                cout << "Press 's' +  <Enter> to start the match." << endl;
                cin >> answer;
                while (answer != 's') {
                    cout << "Press 's' +  <Enter> to start the match." << endl;
                    cin >> answer;
                }
                cout << "========================================================================================" << endl;
            } else if ( game_state == game_state_e::PLAYING ){
                if (current_player_index == 0) {
                    //current player is the machine
                    int num_actions = 0;
                    num_actions ++;
                    if (num_actions == 1) {
                        //the fist action of the always ever rool
                        game_action = game_actions_e::ROOL;
                    } else {
                        //draw the action
                        game_action = game_actions_e(dice.draw_ia_actions()); 
                    }
                } else if (current_player_index != 0) {
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

                    //defines the action of the player
                    if (answer == 'h') { game_action = game_actions_e::HOLD; }
                    if (answer == 'r') { game_action = game_actions_e::ROOL; }
                    if (answer == 'q') { game_action = game_actions_e::QUIT; } 

                    cout <<endl;
                }

            } else if ( game_state == game_state_e::UPDATING_SCORE){

            } else if ( game_state == game_state_e::QUITTING ){
                char answer;

                if (number_of_players == 1) {
                    cout << "Are you sure you want to exit the game?" << endl;
                } else {
                    cout << "Are you want to close the game?" << endl;
                }
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
                if (answer == 'y') { ask_quit_game = true; }
                if (answer == 'n') { ask_quit_game = false; }
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
                if (game_action == game_actions_e::HOLD) { game_state = game_state_e::HOLDING; }
                if (game_action == game_actions_e::ROOL) { game_state = game_state_e::ROLLING; }
                if (game_action == game_actions_e::QUIT) { game_state = game_state_e::QUITTING; }

            } else if ( game_state == game_state_e::ROLLING ){
                point = dice.roll_dice(); 
                if (point == 1) {
                    //lose points of the turn
                    game_action = game_actions_e::HOLD; //end ther turn fot current player
                    game_state = game_state_e::UPDATING_SCORE; //Go to UPDATE state
                } else {
                    players[current_player_index].set_turn_score(point); //update score of the player in current turn
                    //check if the player won the game
                    if (players[current_player_index].get_geral_score() >= 100) {
                        game_over(); //finish the game
                        game_state = game_state_e::ENDING; //Go to END state
                    }else {
                        // has no winner
                        game_state = game_state_e::UPDATING_SCORE; //Go to UPDATE state
                    }
                }
        
            } else if ( game_state == game_state_e::HOLDING ){
                game_state = game_state_e::UPDATING_SCORE; //Go to UPDATE state
        
            } else if ( game_state == game_state_e::UPDATING_SCORE ){
                if (game_action == game_actions_e::HOLD) {
                    //update score
                    players[current_player_index].set_geral_score(point); 

                    //update history turns
                    players[current_player_index].update_history();

                    //upgrade to next player
                    current_player_index ++; 
                    if (current_player_index > number_of_players){
                        current_player_index = 0; //the next player is the machine
                    }
                    //upgrade to next turn
                    if (current_player_index == starting_player_index) {
                        number_of_turns ++;
                    }
                }
                game_state = game_state_e::PLAYING; //Go to PLAY state  
            } else if ( game_state == game_state_e::QUITTING ){
                if (ask_quit_game ==  true) {
                    game_state = game_state_e::ENDING; //Go to END state
                }
                if (ask_quit_game ==  false) {
                    game_state = game_state_e::PLAYING; //Go to PLAY state
                }
            } else {
                // Do nothing in these states.
                //  + ENDING
                game_over();
                game_state = 100;
            }
        };

        /// Renders the game to the user.
        void render(void) const{
            if ( game_state == game_state_e::STARTING ){
                // Do nothing in this state.
            } else if ( game_state == game_state_e::WELCOME){
                // Welcome msg and rules.
                cout << "=======================================================================================" << endl;
                cout << "                     ---> Welcome to the Pig Dice game (v 1.1) <---                    " << endl;
                cout << "                              -copyright DIMAp/UFRN 2023-                              " << endl;
                cout << "The object of the jeopardy dice game Pig is to be the first player to reach 100 points." << endl;
                cout << "Each player's turn consists of repeatedly rolling a die. After each roll, the player is" << endl;
                cout << "faced with two choices: roll again, or hold (decline to roll again)." << endl;
                cout << "• If the player rolls a 1, the player scores nothing and it becomes the opponent's turn." << endl;
                cout << "• If the player rolls a number other than 1, the number is added to the player's turn" << endl;                  
                cout << "  total and the player's turn continues." << endl; 
                cout << "• If the player holds, the turn total, the sum of the rolls during the turn, is added to" << endl;
                cout << "  the player's score, and it becomes the opponent's turn." << endl <<endl;
                cout << ">>> The players of the game are: ";
                for (int i = 0; i <= number_of_players; i++) {
                    cout << players[i].get_name();
                    if (i == number_of_players){
                        cout << "." << endl;
                    } else {
                        cout << ", ";
                    }
                }
                cout << ">>> The player who will start the game is:  " << players[starting_player_index].get_name() << endl << endl;           
    
            } else if ( game_state == game_state_e::PLAYING ){
                //Exibe de quem é a vez
                cout << ">>> " << number_of_turns << "º TURN: the current player is:  " << players[current_player_index].get_name() << endl <<endl;
                
            } else if ( game_state == game_state_e::ROLLING){
                cout << ">>> Requested action: 'ROOL'" << endl;
                
            } else if ( game_state == game_state_e::HOLDING ){
                cout << ">>> Requested action: 'HOLD'" << endl;
                
            } else if ( game_state == game_state_e::UPDATING_SCORE ){
                if (game_action == game_actions_e::HOLD){
                    cout << endl << "|    GERAL SCORE" << endl;
                    for (int i = 0; i <= number_of_players; i++) {
                        cout << "|    " << players[i].get_geral_score() << " -> " << players[i].get_name() << endl;
                    }
                    cout << "-------------------------------------------------------" << endl << endl;
                }
                if (game_action == game_actions_e::HOLD && point == 1) {
                    cout << "    Dice value is " << dice_faces[point-1] <<" (" << point <<")" << endl;
                    cout << "    Oh no! You lost your points this turn!" << endl;
                    cout << endl << "|    GERAL SCORE" << endl;
                    for (int i = 0; i <= number_of_players; i++) {
                        cout << "|    " << players[i].get_geral_score() << " -> " << players[i].get_name() << endl;
                    }
                    cout << "-------------------------------------------------------" << endl << endl;
                }
                if (game_action == game_actions_e::ROOL) {
                    cout << "    Dice value is " << dice_faces[point-1] <<" (" << point <<")" << endl;
                    cout << "    The turn total is: " << players[current_player_index].get_geral_score() + players[current_player_index].get_turn_score() << endl;
                    cout << "-------------------------------------------------------" << endl << endl;
                }

            } else if ( game_state == game_state_e::ENDING ){
                if (game_action == game_actions_e::ROOL) {
                    cout << "-------------------------------------------------------" << endl << endl;
                    cout << endl << ">> Contratulations! The winner is " << players[current_player_index].get_name() << "!" << endl << endl;

                }
                if (game_action == game_actions_e::QUIT) {
                    cout << "-------------------------------------------------------" << endl << endl;
                    cout << endl << ">> Goodbye..." << endl << endl;
                }

                    cout << "            >> HISTORY OF THE GAME ACTIONS<<           " << endl;
                for (int i = 0; i <= number_of_players; i++) {
                    cout << ">>> " <<  players[i].get_name() << endl;
                    for (int j = 0; j < number_of_turns; j++) {
                        cout << "    " << players[i].get_history_rolls(j) << " dice rolls produced " << players[i].get_history_turn_score(j) << endl;
                    }
                }
            
                cout << endl << endl;
            } else if ( game_state == game_state_e::QUITTING ){
                cout << ">>> Requested action: 'QUIT'" << endl;
            }
        };
};