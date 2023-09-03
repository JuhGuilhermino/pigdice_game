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
        //lista com os num de vezes que rolou o dado e pontos feitos a cada turno {{num_rolls, points},...}
        int score;
    
    //métodos
    public:
        //pega o nome do usário
        void take_name(){
            cout << "informe o nome do jogador:  ";
            cin >> player_name;
        }

        //adiciona o total de rolls e pontos obitidos na rodada
        void get_turn_points (){
            
        };

        //adiciona o numero de pontos da rodada no total de pontos do jogo
        void update_score (){

        };
};