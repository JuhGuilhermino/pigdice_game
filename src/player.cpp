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
 * This file contains the "Player" class that can be used to save player data such as name and points history.
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct history{
    int dice_rolls, points; 
};

class Player {
    private:
        string player_name = "Machine";  
        int turn_score = 0;              // current turn score
        int turn_rolls = 0;              // number of times the roll action was executed on turn
        int score = 0;                   // total score in the game 
        vector <history> tunrs_history;  // play history
    
    public:
        //set name of the player
        void set_name(){
            cout << "Enter the name of the player:  ";
            cin >> player_name;
        }

        //get name of the player
        string get_name() const{
            return player_name;
        }

        //set the score of the current turn and counts the number of rools
        void set_turn_score(int points){
            turn_score += points; 
            turn_rolls += 1;    
        };

        //get the score of the current turn
        int get_turn_score()const{
            return turn_score;
        }

        //update the total score
        void set_geral_score (int points){
            score += points;
        };

        //get the total score
        int get_geral_score()const{
            return score;
        }

        //update the play history
        void update_history (){
            tunrs_history.push_back({turn_rolls, turn_score});
            turn_rolls = 0;
            turn_score = 0;
        };

        //informs the number of actions of a specific turn
        int get_history_rolls(int num_turn)const{
            return tunrs_history[num_turn].dice_rolls;
        }

        //informs the score of a specific turn
        int get_history_turn_score(int num_turn)const{
            return tunrs_history[num_turn].points;
        }
        
};