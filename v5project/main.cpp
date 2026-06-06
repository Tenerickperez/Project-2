#include <iostream>
using namespace std;
#include <string>
#include <ctime>
#include <vector>
#include "Start.h"
#include <sstream>

//template
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
    cout << "Cards ranging From 1-12 exist and special cards as well!" << endl;

    // created 2 class objects
    // array of objects
    Player players[2];

    //get the names of the players
    for (int i = 0; i < 2; i++) {
        string name;
        cout << "Enter Player " << i + 1 << " name (Name must be 10 characters or less)" << endl;
        cin >> name;
        players[i].setname(name);
    }

    if (players[0] == players[1]) { // using a overloaded operator
        cout << "Same Name Detected" << endl;
        cout << "Must Use Seperate Names!" << endl;
        return false; // ends program
    }

    // classes
    Deck deck;
    Game game;
    bool stopgame = false;
    int choosen_phase = 0;
    //phase picker

    do {

        cout << "Would You Like To Start At A Specific Stage? " << endl;
        cout << "Type (1) To Start At The Very First Or Type (2) To Start At Second" << endl;
        cout << "Type Any Number From 1-10" << endl;
        cin >> choosen_phase;

    } while (!game.ValidatePhase(choosen_phase));
    
    
    // assign phase

    players[0].changephase(choosen_phase);
    players[1].changephase(choosen_phase);

    while (stopgame != true) {
        int turn = game.getturn(); // determines which player is next

        if (players[turn].isskipped()) {
            cout << players[turn].getname() << " has been skipped!" << endl;
            game.changeturn();
            turn = game.getturn();
        }

        cout << "------------------------------------------------------------" << endl;

        // prints the player stage and desc
        cout << player_phase_info(players[turn].getname(), players[turn].getcurrent_phase(), players[turn].print_phasedesc()) << endl;
        //asks to quit or get a card
        game.menu(players[turn].getname());
        //player gets a card
        players[turn].addcard(deck.set());
        // checks phase progress
        if(players[turn].checkphase() && players[turn].getcurrent_phase() != 11) {
            Deck deck;
            players[0].clearcards();
            players[1].clearcards();
        } else if (players[turn].getcurrent_phase() == 11) {
            stopgame = true;
            players[turn].changephase(10);
        }
        //moves onto the next player turn
        game.changeturn();
    }

    cout << "------------------------------------------------------------SCOREBOARD------------------------------------------------------------" << endl;

    cout << "Total Cards Given = " << game.gettotalcreated() << endl;
    cout << "Player 1 (" << players[0].getname() << ")'s Ended In Phase " << players[0].getcurrent_phase() << endl;
    cout << "Player 2 (" << players[1].getname() << ")'s Ended In Phase " << players[1].getcurrent_phase() << endl;
    cout << "Hope You Enjoyed!" << endl;
}


