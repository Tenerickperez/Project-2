#include <iostream>
using namespace std;
#include <string>
#include <ctime>
#include <vector>
#include "Start.h"

//template
template <typename T, typename B, typename C>
string player_phase_info(T a, B b, C c) {
    string result;
    result = a;
    result += "  Is Currently On Phase " + b;
    result += ", " + c;
    return result;
}
// At first it wouldn't let me print the different data types so i just used a string and put them together

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
        getline(cin, name);
        players[i].setname(name); 
        // setname checks for exceptions and returns error if the input is invalid
    }

    if (players[0] == players[1]) { // using a overloaded operator
        cout << "Same Name Detected" << endl;
        cout << "Must Use Seperate Names!" << endl;
        return false; // ends program
    }
    // using the overloaded operator it compares the two names

    // classes
    Deck deck;

    // this uses a template for the game
    Game <int>game;
    bool stopgame = false;
    int choosen_phase = 0;

    //phase picker
    do {

        cout << "Would You Like To Start At A Specific Stage? " << endl;
        cout << "Type (1) To Start At The Very First Or Type (2) To Start At Second" << endl;
        cout << "Type Any Number From 1-10" << endl;
        cin >> choosen_phase;

    } while (!game.ValidatePhase(choosen_phase));
    // if the phase is invalid it returns an error
    
    // assign phase
    for (int i = 0; i < 2; i++) {
        players[i].changephase(choosen_phase);
    }
    
    while (stopgame != true) {
        int turn = game.getturn(); // determines which player is next

        if (players[turn].isskipped()) {
            cout << players[turn].getname() << " has been skipped!" << endl;
            game.changeturn(); // this changes the turn
            // for example if the turn is 1 it turns into 0. (0 is player 1, 1 is player 2)
            turn = game.getturn(); // just returns the turn
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
            // this checks for when a player passes a stage
            // if a player passes a stage it resets the cards and shuffles a new set of cards
        } else if (players[turn].getcurrent_phase() == 11) {
            // this starts once the player is done with the final stage
            stopgame = true; // stops the while loop
            players[turn].changephase(10); // changes the phase for scoreboard purposes
        }

        //moves onto the next player turn
        game.changeturn();
    }

    cout << "------------------------------------------------------------SCOREBOARD------------------------------------------------------------" << endl;

    cout << "Total Cards Given = " << game.gettotalcreated() << endl; // returns all cards created
    cout << "Player 1 (" << players[0].getname() << ")'s Ended In Phase " << players[0].getcurrent_phase() << endl;
    cout << "Player 2 (" << players[1].getname() << ")'s Ended In Phase " << players[1].getcurrent_phase() << endl;
    cout << "Hope You Enjoyed!" << endl;

}


