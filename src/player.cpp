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
        string player_name = "Machine";  // nome do jogador
        int turn_score = 0;              // pontuação do turno atual
        int turn_rolls = 0;              // quantidade de jogadas no truno
        int score = 0;                   // pontuação geral
        vector <history> tunrs_history;  // historico de pontos e numero de jogadas por tundo
        int last_dice;                   // numero que saiu na jogada anterior
        int current_dice;                // numero que saiu na jogada atual
    
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

        //obtém a pontuação da rodada atual e conta o numero de jogadas
        void set_turn_score(int points){
            turn_score += points; 
            turn_rolls += 1;    
        };

        //informa os pontos do turno
        int get_turn_score() const{
            return turn_score;
        }

        //adiciona o numero de pontos da rodada no total de pontos do jogo e atualiza histórico
        void update_score (){
            score += turn_score;
            tunrs_history.push_back({turn_rolls, turn_score});
            turn_score = 0; //zera a pontuação da rodada atual
            turn_rolls = 0;
        };

        //informa a pontuação total do jogador
        int get_score() const{
            return score;
        };

        //verificar se o jogador tirou dois npuemros consecutivos
        bool check_dices(int points) {
            last_dice = current_dice;
            current_dice = points;
            if (last_dice == current_dice) {
                return true;
            }  
        };
};