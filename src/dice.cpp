/** OQUE FAZER AQUI?
 * escolhe aleatóriamente jogador que vai começar o jogo;
 * //resgistra quem está na jogada
 * sorteia o numero do dado
*/

#include <iostream>
#include <string>
#include <vector>
#include <experimental/random>
using namespace std;

enum players_e {
    HUMAN = 0,
    MACHINE
};

class Dice {
    private:
        int next_player;
        int dice; //num sorteado no dado
        int dice_faces[6] = {1, 2, 3, 4, 5, 6};

    public:
        //método que escolhe aleatóriamente jogador que vai começar o jogo;
        int choose_player() {
            int player = experimental::randint(0,1);
            return players_e(player);
        };

        //resgistra quem está na jogada
        int update_player(int current_player) {
            if (current_player == 1){
                next_player = players_e(current_player-1);
            } 
            if (current_player == 0){
                next_player = players_e(current_player+1);
            }
            
            return next_player;
        }

        //rolar o dado
        int roll_dice(){
            int dice = experimental::randint(1,6);
            return dice;
        }
};