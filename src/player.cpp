/**
 * Classe que represeta um único jogador
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct history{
    int num_rolls, points; 
};

class Player {
    //atributos
    private:
        string player_name; //nome do jogador
        int turn_score; //pontuação da rodada atual
        //lista com os num de vezes que rolou o dado e pontos feitos a cada turno {{num_rolls, points},...}
        int score;
    
    //métodos
    public:
        //pega o nome do usário
        Player(){
            score = 0;
        }
        void set_name(){
            cout << "informe o nome do jogador:  ";
            cin >> player_name;
        }

        //obtém o nome do jogador
        string get_name() const{
            return player_name;
        }

        //adiciona o total de rolls e pontos obitidos na rodada
        void set_turn_score(int points){
            turn_score = points;
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