/**
 * Classe que represeta um único jogador
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
        string player_name = "Machine"; //nome do jogador
        int turn_score = 0; //pontuação da rodada atual
        int score = 0;
        vector <history> tunrs_history;
    
    public:
        //obtém o nome do jogador
        void set_name(){
            cout << "Informe o nome do jogador:  ";
            cin >> player_name;
        }

        //informa o nome do jogador
        string get_name() const{
            return player_name;
        }

        //adiciona o total de rolls e pontos obitidos na rodada
        void set_turn_score(int points){
            turn_score += points;
        };

        //obtém a pontuação da rodada atual
        int get_turn_score() const{
            return turn_score;
        }

        //adiciona o numero de pontos da rodada no total de pontos do jogo
        void update_score (){
            score += turn_score;
            turn_score = 0; //zera a pontuação da rodada atual
        };

        //obtém a pontuação total do jogador
        int get_score() const{
            return score;
        }
};