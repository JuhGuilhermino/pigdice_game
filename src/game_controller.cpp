/**
 * @file main.cpp
 *
 * @description
 * This program implements an interactive Pig Dicegame.
 *
 * @author	Júlia Maria A Guilhermino, <juh.guilhermino03@gmail.com>
 * @author  Ludmilla Rodrigues, <ludmillarodr178@gmail.com>
 * @date	September 2023
 * ====================================================================
 * 
 * This file contains all the operation of the game, and the flow of actions.
 */

#include <iostream>
#include <string>
#include <vector>
#include "player.cpp"
#include "dice.cpp"
using namespace std;

class Game_Controller {
    private:
        // states that represent the progress of the game
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

        // states that represent the actions of the game
        enum game_actions_e {
            HOLD=0, //< Stop the turn
            ROOL, //< Rool the dice
            QUIT //< Quit the game
        };

        /// string representation for the dice's faces (Unicode).
        string dice_faces[6] = { "\u2680", "\u2681", "\u2682", "\u2683", "\u2684", "\u2685" };

        //
        bool end_game=false;      // control of the game loop
        int game_state;           // control of the game states
        char game_action;         // control of current player action
        int number_of_players;    // number of human players
        vector <Player> players;  // stores all players
        int current_player_index; // index the current player
        int starting_player_index;// index the the first player of the turn
        int number_of_turns;      // count the current turn
        bool ask_quit_game;       // control of the player wants to quit of the game
        int point;                // number the current player's dice
        int num_ia_actions = 0;   // control of the machine actions
        
        Dice dice;                // create an object of the Dice class

    public:
        // returns the loop control
        bool get_end_game(){
            return end_game;
        };

        // changes the state to returns true when the user wants to quit the game or the game ends
        void game_over(){
            end_game = true;
            return;
        }; 

        //=== Common methods for the Game Loop design pattern.
        void initialize(void){
            //creates a Player object representing the machine/IA
            Player machine;

            //first vector index is always the machine  
            players.push_back(machine); 

            //asks the number of human players
            cout << "Informs the number of human players between 1 and 4:  ";
            cin >> number_of_players;

            //check input
            while (number_of_players > 4){
                cout << "Invalid number. Please try again." << endl;
                cout << "Informs the number of human players between 1 and 4:  ";
                cin >> number_of_players;
            }

            //creates a Player object for each human player
            for (int i = 0; i < number_of_players; i++) {
                Player new_player;

                //asks the player's name 
                new_player.set_name();

                //add him to players vector
                players.push_back(new_player);
            }            

            //draw the first player
            starting_player_index = dice.choose_player(players.size());

            //Go to START state
            game_state = game_state_e::STARTING;
        };


        /// Process user input events, depending on the current game state.
        void process_events(void){
            if ( game_state == game_state_e::STARTING || game_state == game_state_e::ROLLING || game_state == game_state_e::HOLDING ){
                // do nothing, no interaction in these states.

            } else if ( game_state == game_state_e::WELCOME ){
                //confirms the start of the turn
                cout << "Press 's' +  <Enter> to start the match." << endl;
                char answer;
                cin >> answer;

                //check input
                while (answer != 's') {
                    cout << "Press 's' +  <Enter> to start the match." << endl;
                    cin >> answer;
                }
                cout << "========================================================================================" << endl;

            } else if ( game_state == game_state_e::PLAYING ){
                if (current_player_index == 0) {
                    //current player is the Machine/IA
                    num_ia_actions ++;
                    if (num_ia_actions <= 3) {
                        game_action = game_actions_e::ROOL;
                    } else {
                        game_action = game_actions_e(dice.draw_ia_actions()); 
                    }

                } else if (current_player_index != 0) {
                    //current player is a human
                    cout << "Commands syntax:" << endl;
                    cout << " 'h' + <Enter> -> HOLD (add turn total and pass turn over)." << endl;
                    cout << " 'r' + <Enter> -> ROLL the dice." << endl;
                    cout << " 'q' + <Enter> -> QUIT the match (no winner)." << endl;
                    cout << "Enter command >> ";
                    char answer;
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
                // do nothing in this state

            } else if ( game_state == game_state_e::QUITTING ){
                //confirm if the player wants to finish the game
                cout << "Are you sure you want to exit the game?" << endl;
                cout << " 'y' + <Enter> -> YES" << endl;
                cout << " 'n' + <Enter> -> NO" << endl;
                cout << "Enter your choice >> ";
                char answer;
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
                // go to WELCOME state
                game_state = game_state_e::WELCOME; 

            } else if ( game_state == game_state_e::WELCOME ){
                // starts the counting of turns
                number_of_turns = 1; 

                // update the current player
                current_player_index = starting_player_index; 

                // Go to PLAY state.
                game_state = game_state_e::PLAYING; 

            } else if ( game_state == game_state_e::PLAYING ){
                //process the user's command based on the input.
                if (game_action == game_actions_e::HOLD) { game_state = game_state_e::HOLDING; }
                if (game_action == game_actions_e::ROOL) { game_state = game_state_e::ROLLING; }
                if (game_action == game_actions_e::QUIT) { game_state = game_state_e::QUITTING; }

            } else if ( game_state == game_state_e::ROLLING ){
                //draw the number of the dice
                point = dice.roll_dice(); 

                if (point == 1) {
                    //lose points of the turn
                    players[current_player_index].set_turn_score(0);

                    //update score
                    players[current_player_index].set_geral_score(0); 

                    //update history of the game
                    players[current_player_index].update_history();

                    //end ther turn fot current player
                    game_action = game_actions_e::HOLD;

                    //Go to UPDATE state
                    game_state = game_state_e::UPDATING_SCORE; 


                } else {
                    //update score of the player in current turn
                    players[current_player_index].set_turn_score(point); 

                    //check if the player won the game
                    if (players[current_player_index].get_geral_score() + players[current_player_index].get_turn_score() >= 100) {
                        //update geral score
                        players[current_player_index].set_geral_score(players[current_player_index].get_turn_score());

                        //finish the game
                        game_over(); 
                        game_state = game_state_e::ENDING; 
                    }else {
                        // has no winner
                        // Go to UPDATE state
                        game_state = game_state_e::UPDATING_SCORE; 
                    }
                }
                
            } else if ( game_state == game_state_e::HOLDING ){
                 //update score
                players[current_player_index].set_geral_score(players[current_player_index].get_turn_score());

                //Go to UPDATE state
                game_state = game_state_e::UPDATING_SCORE; 
        
            } else if ( game_state == game_state_e::UPDATING_SCORE ){
                if (game_action == game_actions_e::HOLD) {
                    //update history turns
                    players[current_player_index].update_history();

                    //upgrade to next player
                    current_player_index ++; 
                    if (current_player_index > number_of_players){
                        //the next player is the machine
                        current_player_index = 0;    
                        num_ia_actions = 0; 
                    }

                    //upgrade to next turn
                    if (current_player_index == starting_player_index) {
                        number_of_turns ++;
                    }
                }

                //Go to PLAY state
                game_state = game_state_e::PLAYING;

            } else if ( game_state == game_state_e::QUITTING ){
                if (ask_quit_game ==  true) {
                    //Go to END state
                    game_state = game_state_e::ENDING; 

                } else if (ask_quit_game ==  false) {
                    //Go to PLAY state
                    game_state = game_state_e::PLAYING; 
                }
            } else {
                //finish the game
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

                //displays the name of the players
                for (int i = 0; i <= number_of_players; i++) {
                    cout << players[i].get_name();
                    if (i == number_of_players){
                        cout << "." << endl;
                    } else {
                        cout << ", ";
                    }
                }

                //displays the fist player to play
                cout << ">>> The player who will start the game is:  " << players[starting_player_index].get_name() << endl << endl;           
    
            } else if ( game_state == game_state_e::PLAYING ){
                //displays the current player
                cout << ">>> " << number_of_turns << "º TURN: the current player is:  " << players[current_player_index].get_name() << endl <<endl;
                
            } else if ( game_state == game_state_e::ROLLING){
                cout << ">>> Requested action: 'ROOL'" << endl;
                
            } else if ( game_state == game_state_e::HOLDING ){
                cout << ">>> Requested action: 'HOLD'" << endl;
                
            } else if ( game_state == game_state_e::UPDATING_SCORE ){
                // the player choose to end his turn
                // displays the game score 
                if (game_action == game_actions_e::HOLD && point != 1){
                    cout << endl << "|    GERAL SCORE" << endl;
                    for (int i = 0; i <= number_of_players; i++) {
                        cout << "|    " << players[i].get_geral_score() << " -> " << players[i].get_name() << endl;
                    }
                    cout << "-------------------------------------------------------" << endl << endl;
                }
                
                // the player lost his turn
                // displays a special message and the game score 
                if (game_action == game_actions_e::HOLD && point == 1) {
                    cout << "    Dice value is " << dice_faces[point-1] <<" (" << point <<")" << endl;
                    cout << "    Oh no! You lost your points this turn!" << endl;
                    cout << endl << "|    GERAL SCORE" << endl;
                    for (int i = 0; i <= number_of_players; i++) {
                        cout << "|    " << players[i].get_geral_score()  << " -> " << players[i].get_name() << endl;
                    }
                    cout << "-------------------------------------------------------" << endl << endl;
                }
                
                // the player continues on the turn
                // displays the player’s partial points
                if (game_action == game_actions_e::ROOL && point !=1) {
                    cout << "    Dice value is " << dice_faces[point-1] <<" (" << point <<")" << endl;
                    cout << "    The turn total is: " << players[current_player_index].get_geral_score() + players[current_player_index].get_turn_score() << endl;
                    cout << "-------------------------------------------------------" << endl << endl;
                }

            } else if ( game_state == game_state_e::ENDING ){
                // the current player won the game
                if (game_action == game_actions_e::ROOL) {
                    cout << "-------------------------------------------------------" << endl << endl;
                    cout << endl << ">> Congratulations! The winner is " << players[current_player_index].get_name() << " with " << players[current_player_index].get_geral_score() << " !" << endl << endl;
                }

                // the current player closed the
                if (game_action == game_actions_e::QUIT) {
                    cout << "-------------------------------------------------------" << endl << endl;
                    cout << endl << ">> Goodbye..." << endl << endl;
                }

                //displays history of the game
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