#include <iostream>
using namespace std;
#include <string>
#include <ctime>
#include <vector>
#include "Start.h"

string phase_description(int);


int main() {
    cout << "Welcome To PHASE 10" << endl;
    cout<< "This game was built for 2 players with 10 phases!" << endl;
    Player players[2];
    for (int i = 0; i < 2; i++) {
        string name;
        cout << "Enter Player " << i + 1 << " name" << endl;
        cin >> name;
        players[i].setname(name);
    }
    Deck();
    
}

string phase_description(int phase) {
    switch(phase) {
        case 1: {
            return "2 Sets of 3";
        }
        case 2: {
            return "1 set of 3 + 1 run of 4";
        }
        case 3: {
            return "1 set of 4 + 1 run of 4";
        }
        case 4: {
            return "1 run of 7";
        }
        case 5: {
            return "1 run of 8";
        }
        case 6: {
            return "1 run of 9";
        }
        case 7: {
            return "2 sets of 4";
        }
        case 8: {
            return "1 run of 9";
        }
        case 9: {
            return "1 set of 5 + 1 set of 2";
        }
        case 10: {
            return "1 set of 5 + 1 set of 3";
        }
        default: {
            return "Phase Number Out Of Range!";
        }
    }
}
