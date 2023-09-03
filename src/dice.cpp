/** OQUE FAZER AQUI?
 * escolhe aleatóriamente jogador que vai começar o jogo;
 * //resgistra quem está na jogada
 * sorteia o numero do dado
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum players_e {
    HUMAN = 0,
    MACHINE
};

class Dice {
    private:
        int current_player;
        int dice; //num sorteado no dado
        int dice_faces[6] = {1, 2, 3, 4, 5, 6};

    public:
        //método que escolhe aleatóriamente jogador que vai começar o jogo;
        int choose_player() {

            return;
        };

        //resgistra quem está na jogada
        int update_current_player() {

            return;
        }

        //rolar o dado
        int roll_dice(){

            return;
        }
};