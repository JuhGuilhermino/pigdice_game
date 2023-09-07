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
            STARTING=0,       //< Beginning the game.
            WELCOME,          //< Opening messasges.
            PLAYING,          //< Where the game action takes place.
            ROLLING,          //< We roll the dice to get a face number.
            HOLDING,          //< User asked to hold and pass turn to the next player. 
            UPDATING_SCORE,   //< Update the score board and show command issued in the turn.
            JOKER,            //<
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

        bool end_game = false; 
        int game_state;           // controle das ações dos jogadores
        int game_actions;         // controle dos estados
        int number_of_players;    // número de jogadores
        vector<Player> players;   // vetor com todos os objetos jogadores
        int current_player_index; // indice do jogador atual
        Dice dice;                // cria uma instacia da classe Dice
        

    public:
        //=== Common methods for the Game Loop design pattern.
        void initialize(void){
            //cria uma instancia da classe Player que represneta a IA
            Player machine;
            players.push_back(machine); //1º indice do vetor sempre é a máquina

            //solicitar o número de jogadores
            cout << "Informe o número de jogadores entre 1 e 4 que vão competir com a máquina: ";
            cin >> number_of_players;

            //verifica se o jogo suporta o numero de jogadores informados
            while (number_of_players > 4){
                    cout << "ERRO: número de jogadores não suportado" << endl;
                    cout << "Informe o número de jogadores entre 1 e 4 que vão competir com a máquina: " << endl;
                    cin >> number_of_players;
            }

            //cria uma instacia de Player para cada jogador e solicitar o nome dos jogadores humanos
            for (int i = 0; i < number_of_players; i++) {
                Player new_player;
                new_player.set_name();
                players.push_back(new_player);
            }            

            //define o jogador inicial aleatóriamente
            current_player_index = dice.choose_player(players.size());

            //atualiza o estado para iniciar o jogo
            game_state = game_state_e::STARTING;
        };


        /// Process user input events, depending on the current game state.
        void process_events(void){
            if ( game_state == game_state_e::STARTING or game_state == game_state_e::ROLLING or game_state == game_state_e::HOLDING ){
                // Do nothing, no interaction in these states.
            } else if ( game_state == game_state_e::WELCOME ){
                //Dar inicio ao jogo
                cout << "Press <Enter> to start the match." << endl;
                cin.ignore(); //espera o usuario pressionar enter
            } else if ( game_state == game_state_e::PLAYING ){
                if (current_player-1 != 0){
                    //exibe as possíveis ações do jogador humano
                    cout << "Commands syntax:" << endl;
                    cout << " 'r' + <Enter> -> ROLL the dice." << endl;
                    cout << " 'h' + <Enter> -> HOLD (add turn total and pass turn over)." << endl;
                    cout << " 'q' + <Enter> -> quit the match (no winner)." << endl;
                    cout << "Enter command >> ";
                    cin >> action_command;

                    //se colocar um comando inválido
                    while (action_command != 'r' && action_command != 'h' && action_command != 'q'){
                        cout << "Invalid command. Please try again." << endl;
                        cout << "Enter command >> ";
                        cin >> action_command;
                    }
                }
                
            } else if ( game_state == game_state_e::UPDATING_SCORE){

            } else if ( game_state == game_state_e::JOKER ){
                cout << "Do you want to use you JOKER?" << endl;
                cout << " 'y' + <Enter> -> YES" << endl;
                cout << " 'n' + <Enter> -> NO" << endl;
                cout << "Enter your choice >> ";
                cin >> joker_choice;

                while (joker_choice != 'y' && joker_choice != 'n'){
                    cout << "Invalid command. Please try again." << endl;
                    cout << "Enter your choice >> ";
                    cin >> joker_choice;
                }

            } else if ( game_state == game_state_e::QUITTING ){
                cout << "Are you sure you want to exit the game?" << endl;
                cout << " 'y' + <Enter> -> YES" << endl;
                cout << " 'n' + <Enter> -> NO" << endl;
                cout << "Enter your choice >> ";
                char quite_choice;
                cin >> quite_choice;

                while (joker_choice != 'y' && joker_choice != 'n'){
                    cout << "Invalid command. Please try again." << endl;
                    cout << "Enter your choice >> ";
                    cin >> quite_choice;
                }
            }
        };

        /// Update the game based on the current game state.
        void update(void){
            if (game_state == game_state_e::STARTING ){
                //Go to WELCOME state
                game_state = game_state_e::WELCOME;
            } else if ( game_state == game_state_e::WELCOME ){
                // Go to PLAY state.
                game_state = game_state_e::PLAYING;
            } else if ( game_state == game_state_e::PLAYING ){
                //process the user's command based on the input.
                if (action_command == 'r'){
                    player_action = game_state_e::ROLLING; 
                } else if (action_command == 'h'){
                    player_action = game_state_e::HOLDING; 
                } else if (action_command == 'q'){
                    player_action = game_state_e::QUITTING; 
                }

            } else if ( game_state == game_state_e::ROLLING ){

            } else if ( game_state == game_state_e::HOLDING ){

            } else if ( game_state == game_state_e::JOKER ){
        
            }else if ( game_state == game_state_e::UPDATING_SCORE ){

            } else if ( game_state == game_state_e::QUITTING ){
                if (quite_choice == 'y'){
                    game_over();
                    player_action = game_state_e::QUITTING; 
                }
                if (action_command == 'n'){
                    player_action = game_state_e::PLAYING; 
                }
            } else {
                // Do nothing in these states.
                //  + ENDING
            }
        };

        /// Renders the game to the user.
        void render(void) const{
            if ( game_state == game_state_e::STARTING ){
                // Do nothing in this state.
            } else if ( game_state == game_state_e::WELCOME){
                // Welcome msg and rules.
            } else if ( game_state == game_state_e::PLAYING ){
                //Exibe de quem é a vez
                cout << ">>> The current player is: " << players[current_player].get_name() << endl;
            } else if ( game_state == game_state_e::ROLLING){
                cout << ">>> Requested action: 'Roll' " << endl;
            } else if ( game_state == game_state_e::HOLDING ){
                cout << ">>> Requested action: 'Hold' " << endl;
            } else if ( game_state == game_state_e::JOKER ){
            
            }else if ( game_state == game_state_e::UPDATING_SCORE ){

            } else if ( game_state == game_state_e::ENDING ){

            } else if ( game_state == game_state_e::QUITTING )
                cout << ">>> ";
            {

            }
        };

        /// Returns true when the user wants to quit the game.
        bool game_over(void){
            end_game = true;
            return end_game;
        }; 

};