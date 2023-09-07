#include <iostream>
#include <string>
#include <vector>
#include <random>
using namespace std;

enum players_e {
    HUMAN = 0,
    MACHINE
};

class Dice {
private:
    int next_player;
    int dice;       
    int dice_faces[6] = {1, 2, 3, 4, 5, 6};

public:
    Dice() : next_player(0), dice(0) {} 

    int choose_player(int numbers_players) {
        int player = rand() % numbers_players;
        return players_e(player);
    }

    int update_player(int current_player) {
        if (current_player == 1) {
            next_player = players_e(current_player - 1);
        }
        if (current_player == 0) {
            next_player = players_e(current_player + 1);
        }
        return next_player;
    }

    int roll_dice() {
        dice = rand() % 6 + 1;
        return dice;
    }
};