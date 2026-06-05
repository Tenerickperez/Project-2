#include <iostream>
using namespace std;
#include <string>
#include <ctime>
#include <vector>
#include "Start.h"
#include <sstream>


template <typename T, typename B, typename C>
string player_phase_info(T a, B b, C c) {
    stringstream ss;
    ss << a << " Is Currently On Phase " << b << ", " << c;
    return ss.str();
}

int main() {
    cout << "------------------------------------------------------------Welcome To PHASE 10--------------------------------------------------\n" << endl;
    cout<< "This game was built for 2 players with 10 phases!" << endl;
    cout << "The First One To Complete A Phase Moves On" << endl;

    // create 2 class objects
    Player players[2];

    //get the names of the players
    for (int i = 0; i < 2; i++) {
        string name;
        cout << "Enter Player " << i + 1 << " name (Name must be 10 characters or less)" << endl;
        cin >> name;
        players[i].setname(name);
    }
    
    // classes
    Deck deck;
    Game game;
    bool stopgame = false;

    while (stopgame != true) {
        int turn = game.getturn(); // determines which player is next
        // prints the player stage and desc
        cout << player_phase_info(players[turn].getname(), players[turn].getcurrent_phase(), players[turn].print_phasedesc()) << endl;
        //asks to quit or get a card
        game.menu(players[turn].getname());
        //player gets a card
        players[turn].addcard(deck.set());
        // checks phase progress
        if(players[turn].checkphase()) {
            Deck deck;
            players[0].clearcards();
            players[1].clearcards();
        }
        //moves onto the next player turn
        game.changeturn();
    }
    
}


