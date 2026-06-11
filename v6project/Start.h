#ifndef START_H
#define START_H

//exception classes
// .h file is spilt
class InvalidCardRange {
    public:
        InvalidCardRange(int m) {
            cout << "Card Range Must Be 1-12" << endl;
            cout << "Your Card Number Was " << m << endl;
            cout << "ERROR...SHUTTING DOWN" << endl;
        }
        // This class is used to catch a error
};

class InvalidName {
    public:
        InvalidName(){
            cout << "Name is not valid!!" << endl;
            cout << "Make Sure To Follow The Rules!" << endl;
        }
        // detects an invalid name
};

class InvalidInput {
    public:
        InvalidInput() {
            cout << "Input Was Invalid, Please Try Again!" << endl;
            cout << "Please Follow The Rules" << endl;
        }
        // detects an invalid input
};

class FirstCard {
    public: 
        FirstCard() {
            // used for every phase
            // this class is just used for detection
        }
};

class Quitting {
    public: 
        Quitting() {
            cout << "Programming Is Shutting Down" << endl;
            cout << "Goodbye!" << endl;
            exit(EXIT_FAILURE);
        }
        // this is used when a user wishes to end the program
};

class InvalidTurn {
    public:
        InvalidTurn() {
            cout << "Error..Shuttting Down" << endl;
            exit(EXIT_FAILURE);
        }
        // detects an error in the program
};

class InvalidCardColor {
    public:
    InvalidCardColor() {
        cout << "This Card Color Is Invalid" << endl;
        cout << "Error..." << endl;
    }
    // detects an error
};

class EmptyVector {
    public:
        EmptyVector() {
            cout << "Card Deck Is Empty..." << endl;
            cout << "Error..." << endl;
        }
        // detects an error
};

//card setup
//instance of a class
class Card {
    protected: 
        int number;
        string color;
    public:
    // constructor
        Card(int n, string c){
            //exceptions
            try {

                if (n < 1 || n > 14) {
                    throw InvalidCardRange(n); 
                }

                if (c != "Red" && c != "Yellow" && c != "Blue" && c != "Green") {
                    throw InvalidCardColor();
                }
                number = n;
                color = c;
                
            } catch (InvalidCardRange) {
                exit(EXIT_FAILURE);
            } catch (InvalidCardColor) {
                exit(EXIT_FAILURE);
            }
            print_card(); // prints the number and color
        }
        //get functions
        int getnumber() const {return number;}
        string getcolor() const {return color;}
        bool iswild() {return number == 14;}
        bool isskip() {return number == 13;}
        // set functions
        void setnumber(int n) {
            try {
                if (n < 1 || n > 14) {
                    throw InvalidCardRange(n);
                }
                number = n;
            } catch (InvalidCardRange) {
                exit(EXIT_FAILURE);
            }
        }

        void setcolor(string c) {
            try {
            if (c != "Red" || c != "Yellow" || c != "Blue" || c != "Green") {
                    throw InvalidCardColor(); 
            }
            } catch (InvalidCardColor) {
                exit(EXIT_FAILURE);
            }
        }

        bool specialcards() {
            if (iswild()) {
                cout << "You have recieved a wild card! This Will Turn Into Any Card You Need." << endl;
                return true;
            } 
            if (isskip()) {
                cout << "You have recieved a SKIP card! This Will Skip The Other Player's Turn" << endl;
                return true;
            }
            return false;
        }

        void print_card() {
            if (!specialcards()) { // if special cards return false then print 
                cout << "You got a " << number << " " << color << endl;
            }
        }

};

class Deck {
    private:
        vector<int> numbers; // deck_nums
        string options[4] = {"Red", "Yellow", "Blue", "Green"};
        vector<string> colors; // deck_colors
        bool firstrun; // used to prevent wilds and skips to be given first turn
    public:
        Deck() {
            firstrun = true;
            cout << "Shuffling Deck..." << endl;
            fillcards();
            shuffle();
            fill_colors();
            shuffle_colors();
            // this just sets up all the cards to be given
        }

        void printoptions() {
            for (int i = 0; i < 4; i++) {
                cout << options[i] << " ";
            }
            cout << endl;
            // just prints the options for testing purposes
        }

        void fillcards() {
            numbers.clear();
            srand(time(0));
            for (int i = 0; i < 48; i++) {
                int num = rand() % 12 + 1; // 1-12 range
                numbers.push_back(num);
                numbers.push_back(num);
            } // pushes 96 cards 1-12, two of each.
            for (int i = 0; i < 4; i++) {
                numbers.push_back(13); // skip cards
            }
            // pushes 4 skip cards
            for (int i = 0; i < 8; i++) {
                numbers.push_back(14); // wild cards
            }
            // pushes 8 wild cards
        }

        void shuffle() {
            for (int i = 0; i < numbers.size() - 1; i++){
                int p = rand() % numbers.size() - 1 + 1; // 1-96
                swap(numbers[i], numbers[p]);
            }
            // above just shuffles them

            if (firstrun == true) {
                int secondtolast = numbers.size() - 2; 
                if (numbers.back() == 14) {
                    // swap(numbers.back(), numbers[10]); // realized the swap to postion 10 could contain a wild.
                    numbers.back() = 2;
                } else if (numbers[secondtolast] == 14) {
                    numbers[secondtolast] = 7;
                }
                if (numbers.back() == 13) {
                    // swap(numbers.back(), numbers[9]); // realized the swap to postion 9 could contain a skip.
                    numbers.back() = 4;
                } else if (numbers[secondtolast] == 13) {
                    numbers[secondtolast] = 1;
                }
            } // this just makes sure wilds and skips don't appear on the first cards given
            // it checks the last postion and second to last
            firstrun = false;
        }

        void shuffled_deck() {
            for (int i = 0; i < numbers.size(); i++){
                cout << numbers[i] << " " ;
            }
            cout << endl;
            // testing purposes
        }

        void fill_colors() {
            colors.clear();
            srand(time(0));
            for (int i = 0; i < 27; i++) {
                int num = rand() % 3 + 0; // 0-3 range for options array
                colors.push_back(options[num]);
                colors.push_back(options[num]);
                colors.push_back(options[num]);
                colors.push_back(options[num]);
            } // pushes 108 card colors, 4 of each.
        }

        void shuffle_colors() {
            for (int i = 0; i < colors.size() - 1; i++){
                int p = rand() % colors.size() - 1 + 1; // 1-108
                swap(colors[i], colors[p]);
            }
            // this does the same thing as the numbers
        }

        void shuffled_colors() {
            for (int i = 0; i < colors.size(); i++){
                cout << colors[i] << " " ;
            }
            cout << endl;
            // testing purposes
        }

        Card set() {
            // exceptions
            try {
                if (numbers.empty()) {
                    throw EmptyVector();
                }
                if (colors.empty()) {
                    throw EmptyVector();
                }

                int value = numbers.back(); // gets the last vector postion
                string colorrr = colors.back(); // gets the last vector postion
                Card c(value, colorrr); // passes it into the card
                numbers.pop_back(); // deletes the last vector postion
                colors.pop_back(); // deletes the last vector postion
                return c;
            } catch (EmptyVector){
                exit(EXIT_FAILURE);
            }
        }
        
};

class Phase {
    public:
        void printallphases() {
            cout << "1 Set Of 3" << endl;
            cout <<"1 Set Of 3 + 1 Run Of 4" << endl;
            cout << "1 Set Of 4 + 1 Run Of 4" << endl;
            cout << " 1 Run Of 7" << endl;
            cout << "1 Run Of 8" << endl;
            cout << "1 Set Of 4 + 1 Set Of 2" << endl;
            cout << "1 Set Of 5 "<< endl; 
            cout << "1 Run Of 9" << endl;
            cout << "1 Set Of 4 (Colors)" <<  endl;
            cout << "1 Set Of 5 + 1 Set Of 2" << endl;
            // this just prints all the stages for the user
        }

        string phase_description(int p) {
            switch(p) {
                case 1: {
                    return "1 Set of 3 (1 Group Of 3 Of The Same Card Numbers)";
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
                     return "1 set of 4 + 1 set of 2";
                }
                case 7: {
                    return "1 set of 5";
                }
                 case 8: {
                    return "1 run of 9";
                    }
                case 9: {
                     return "1 set of 4 (Colors)";
                    }
                 case 10: {
                     return "1 set of 5 + 1 set of 2";
                }
                default: {
                    return "Phase Number Out Of Range!";
                }
            }
            // this is used for functions
        }

        // has set for nums
        bool haset(vector<int> &num, vector<string> &color, int set) {
            bool nextphase = false;
            try {
                if (num.size() <= 1) {
                    throw FirstCard();
                    // detects if it's the player's first run
                }

                for (int i = 1; i < num.size(); i++) {
                    if (num[i] == 14) {
                        num[i] = num[0];
                        // detects wild cards
                    }
                }

                if (num.size() < set) {  // excutes while vector size is less than set 
                    for (int i = 1; i < num.size(); i++) {
                        if (num[i] != num[0]) {
                            num.pop_back();
                        }
                        // if num isn't equal to the desired value then delete
                    }
                } 
                if (num.size() == set) { // excutes when vector size is equal to set 
                    for (int i = 1; i < set; i++) {
                        if (num[i] == num[0]) {
                            nextphase = true;
                        } else {
                            nextphase = false;
                            num.pop_back();
                            break;
                        }
                        // detects if all values are true or else deletes
                    }
                }
                
                if (nextphase == true) {
                    return true;
                } 

            } catch (FirstCard) {
                cout << "Get " << set - 1 << " Cards With The number " << num[0] << endl;
            }
             return false;  
        }

        bool haset_hasrun(vector<int> &num, vector<string> &color, vector<int> &placeholder, int set, int run){
            bool rundone = false;
            bool setdone = false;
            int nextnum = 0;
           
            try {
                // below is the logic for runs
                // the past phase is similar so i won't explain much here
                if (num.size() <= 1) {
                    throw FirstCard(); 
                }

            if (placeholder.size() < run) {
                 if (placeholder.empty()) {
                    nextnum = num[0] + 1; // next num is the value + 1
                } else {
                    nextnum = placeholder.back() + 1; 
                }

                for (int i = 1; i < num.size(); i++) {
                    if (nextnum >= 13) {
                        nextnum = 1; // goes back to 1 because greater than 13 are special cards
                    }
                    if (num[i] == nextnum) {
                        placeholder.push_back(nextnum); // saves it
                        nextnum++;
                    } else if (num[i] == 14) {
                        placeholder.push_back(nextnum); // wild cards
                        nextnum++;
                    }
                }
            } 
            if (placeholder.size() == run) {
                nextnum = placeholder[0];
                    if (nextnum >= 13) {
                        nextnum = 1; 
                    }
                 for (int i = 0; i < run; i++) {
                        if (placeholder[i] == nextnum) {
                            rundone = true;
                            nextnum++;
                        } else {
                            rundone = false;
                            break;
                        }
                }
            }  

            // below is the logic for sets
            // i explained sets in the past phase
             for (int i = 1; i < num.size(); i++) {
                    if (num[i] == 14) {
                        num[i] = num[0];
                    }
            }

            if (num.size() < set) { 
                    for (int i = 1; i < num.size(); i++) {
                        if (num[i] != num[0]) {
                            num.pop_back();
                        }
                    }
                } if (num.size() == set) {
                    for (int i = 1; i < set; i++) {
                        if (num[i] == num[0]) {
                            setdone = true;
                        } else {
                            setdone = false;
                            num.pop_back();
                            break;
                        }
                    }
                }
            if (rundone == true) {
                cout << "Run Complete" << endl;
                placeholder.push_back(0);
            }
            if(setdone == true) {
                cout << "Set Complete" << endl;
                num.push_back(0);
            }

            if (num.size() > set && placeholder.size() > run) { // checks if vectors are greater than the sets because
                // that means they aren't being deleted, which means the sets are complete
                return true;
            }
        } catch(FirstCard) {
            cout << "Get " << set - 1 << " Cards With The Number " << num.back() << " + A Run of " <<  run << endl;
        }
            return false;
        }

        bool hasrun(vector<int> &num, vector<string> &color, vector<int> &placeholder, int run) {
            bool rundone = false;
            try {
                // explained run in the past phase
                if (num.size() <= 1) {
                    throw FirstCard();
                }
                int nextnum = 0;
                if (placeholder.size() < run) {
                    if (placeholder.empty()) {
                    nextnum = num[0] + 1;
                } else {
                    nextnum = placeholder.back() + 1;
                }

                for (int i = 1; i < num.size(); i++) {
                    if (nextnum >= 13) {
                        nextnum = 1; 
                    }
                    if (num[i] == nextnum) {
                        placeholder.push_back(nextnum);
                        nextnum++;
                    } else if (num[i] == 14) {
                        placeholder.push_back(nextnum);
                        nextnum++;
                    }
                }
                } if (placeholder.size() == run) {
                    nextnum = placeholder[0];
                    if (nextnum >= 13) {
                        nextnum = 1; 
                    }
                 for (int i = 0; i < run; i++) {
                        if (placeholder[i] == nextnum) {
                            rundone = true;
                            nextnum++;
                        } else {
                            rundone = false;
                            break;
                        }
                }
                }  
                num.pop_back();
                if (rundone) {
                    cout << "You have completed the run!" << endl;
                    return true;
                }
            } catch(FirstCard) {
                cout << "Get A Run Of " << run << endl;
            }
            return false;
        }

        bool hasset_haset(vector<int> &num, vector<string> &color, int set, int set2){
            bool doneset = false;
            bool doneset2 = false;
            try {
                if (num.size() <= 1) {
                    throw FirstCard(); // detects first card given
                }

                for (int i = 1; i < num.size(); i++) { 
                    if (num[i] == 14) {
                        num[i] = num[0];
                        color[i] = color[0];
                    }
                    // detects wild cards
                }

                if (num.size() < set) {  // this excutes while num is less than the set length
                    for (int i = 1; i < num.size(); i++) {
                        if (num[i] != num[0]) {
                            num.pop_back();
                        }
                    }
                } 

                if (num.size() == set) { // this excutes when color is equal to the set length
                    for (int i = 1; i < set; i++) {
                        if (num[i] == num[0]) {
                            doneset = true;
                        } else {
                            doneset = false;
                            num.pop_back();
                            break;
                        }
                    }
                }

                if (color.size() < set2) { // this excutes while color is less than the set length
                    for (int i = 1; i < color.size(); i++) {
                        if (color[i] != color[0]) {
                            color.pop_back();
                        }
                    }
                }
 
                if (color.size() == set2) { // this excutes when color is equal to the set length
                    for (int i = 1; i < set2; i++) {
                        if (color[i] == color[0]) {
                            doneset2 = true;
                        } else {
                            doneset2 = false;
                            color.pop_back();
                            break;
                        }
                    }
                }
                
                if (doneset) {
                    cout << "Number Set Done" << endl;
                    num.push_back(0);
                }
                if (doneset2) {
                    cout << "Color Set Done" << endl;
                }
                if (num.size() > set && color.size() > set2) {
                    return true;
                }
            }
            catch (FirstCard) {
                cout << "Get " << set - 1 << " cards with the same number + " << set2 - 1<< " cards with the same colors" << endl;
            }
            return false;
        }
        // has set for colors
        bool haset(vector<string> color, int set) { 
            bool done = false; 
            try {

                if (color.size() <= 1) {
                    throw FirstCard(); // first card given for the player
                }

                 if (color.size() < set) { // this excutes while color is less than the set length
                    for (int i = 1; i < color.size(); i++) {
                        if (color[i] != color[0]) {
                            color.pop_back();
                        }
                    }
                }

                if (color.size() == set) { // this excutes when the color is the same set length
                    for (int i = 1; i < set; i++) {
                        if (color[i] == color[0]) {
                            done = true;
                        } else {
                            done = false;
                            color.pop_back();
                            break;
                        }
                        // checks if the set is correct or else deletes the last value
                    }
                }

                if (done) {
                    return true; // this means the phase is done
                }
            } catch(FirstCard) {
                cout << "You need " << set << " cards with the color " << color[0] << endl;
            }
            return false;
        }
}; 

class Player : public Phase { // base to derived
    private:
        string name;
        int phase;
        vector<int> deck_numbers; // deck of numbers
        vector<string> deck_colors; // deck of colors
        static bool skipped; // static var
        vector<int> deck_placeholder; // second deck of cards
    public:
        Player() {
            phase = 1; // def value
        }

        //copy constructor
        Player(const Player &obj) {
            name = obj.name;
            phase = obj.phase;
            deck_numbers = obj.deck_numbers;
            deck_colors = obj.deck_colors;
            deck_placeholder = obj.deck_placeholder;
            skipped = obj.skipped;
        }

        //destructor
        ~Player() {
            deck_numbers.clear();
            deck_colors.clear();
            deck_placeholder.clear();
        }

        void setname(string n) {
            try {
                if (n.length() > 10) {
                    throw InvalidName();
                }

                for (int i = 0; i < n.length(); i++) {
                    if (!isalpha(n[i]) && n[i] != ' ') {
                        throw InvalidName(); // validates input
                    }
                }
                name = n;
            } catch (InvalidName) {
                exit(EXIT_FAILURE);
            }
        }
        // get functions 
        void changephase(int p) {phase = p;}
        string getname() const {return name;}
        int getcurrent_phase() {return phase; }
        string print_phasedesc() {return phase_description(phase);}
        bool isskipped() {return skipped;}

        void clearcards() {
            deck_numbers.clear(); 
            deck_colors.clear(); 
            deck_placeholder.clear();
            // just clears all the deck
        }

        void addcard(Card c) {
            skipped = false; // this is passed to main
            deck_numbers.push_back(c.getnumber());
            deck_colors.push_back(c.getcolor());
            checkskip();
        }

        void checkskip() {
            if (deck_numbers.back() == 13) {
                skipped = true;
            }
        }

        void printdeck(int set) {
            // prints vector
            if (deck_numbers.size() < set) {
            cout << "Current Set Progress (" ;
            for (int i=1; i < deck_numbers.size();i++) {
                cout << deck_numbers[i] << ", " ;
            }
            cout << ")" << endl;
            }
        }

        void printplaceholder(int run) {
            // prints vector
            if (deck_placeholder.size() < run ) {
            cout << "Current Run Progress (";
            for (int i = 0; i < deck_placeholder.size(); i++) {
                cout << deck_placeholder[i] << ", " ;
            }
            cout << ")" << endl;
            }
        }

        void printcolordeck(int set) {
            // prints vector
            if (deck_colors.size() < set ) {
            cout << "Current Color Set Progress (";
            for (int i = 1; i < deck_colors.size(); i++) {
                cout << deck_colors[i] << ", " ;
            }
            cout << ")" << endl;
            }
        }

        bool checkphase() {
            switch(phase) {
                case 1: {
                    if(haset(deck_numbers, deck_colors, 4)) { // if this is true then the phase
                        // is complete
                        cout << "You Have Passed This Phase " << getname() << endl;
                        phase++;
                        return true; // returns to main
                    } else {
                        printdeck(4); // prints progress
                        return false;
                    }
                }
                case 2: {
                    if(haset_hasrun(deck_numbers, deck_colors, deck_placeholder, 4 , 4)) { // if this is true then the phase
                        // is complete
                        cout << "You Have Passed This Phase " << getname() << endl;
                        phase++;
                        return true;
                    } else {
                        printplaceholder(4);
                        printdeck(4);
                        cout << endl;
                        return false;
                    }
                }
                case 3: {
                    if(haset_hasrun(deck_numbers, deck_colors, deck_placeholder, 5,4)) { // if this is true then the phase
                        // is complete
                        cout << "You Have Passed This Phase " << getname() << endl;
                        phase++;
                        return true;
                    } else {
                        printplaceholder(4);
                        printdeck(5);
                        cout << endl;
                        return false;
                    }
                }
                case 4: {
                    if(hasrun(deck_numbers, deck_colors, deck_placeholder, 7)) { // if this is true then the phase
                        // is complete
                        cout << "You Have Passed This Phase " << getname() << endl;
                        phase++;
                        return true;
                    } else {
                        printplaceholder(7);
                        cout << endl;
                        return false;
                    }
                } 
                case 5: {
                    if(hasrun(deck_numbers, deck_colors, deck_placeholder, 8)) { // if this is true then the phase
                        // is complete
                        cout << "You Have Passed This Phase " << getname() << endl;
                        phase++;
                        return true;
                    } else {
                        printplaceholder(8);
                        cout << endl;
                        return false;
                    }
                } case 6: {
                    if(hasset_haset(deck_numbers, deck_colors, 5, 3)) { // if this is true then the phase
                        // is complete
                        cout << "You Have Passed This Phase " << getname() << endl;
                        phase++;
                        return true;
                    } else {
                        printdeck(5);
                        printcolordeck(3);
                        cout << endl;
                        return false;
                    }
                }
                case 7: {
                    if (haset(deck_numbers, deck_colors, 5)) { // if this is true then the phase
                        // is complete
                        cout << "You Have Passed This Phase " << getname() << endl;
                        phase++;
                        return true;
                    } else {
                        printdeck(5);
                        cout << endl;
                        return false;
                    }
                } case 8: {
                     if(hasrun(deck_numbers, deck_colors, deck_placeholder, 9)) { // if this is true then the phase
                        // is complete
                        cout << "You Have Passed This Phase " << getname() << endl;
                        phase++;
                        return true;
                    } else {
                        printplaceholder(9);
                        cout << endl;
                        return false;
                    }
                }
                case 9: {
                    if (haset(deck_colors, 4)) { // if this is true then the phase
                        // is complete
                        cout << "You Have Passed This Phase " << getname() << endl;
                        phase++;
                        return true;
                    } else {
                        printdeck(4);
                        cout << endl;
                        return false;
                    }
                }
                case 10: {
                    if(hasset_haset(deck_numbers, deck_colors, 6, 3)) { // if this is true then the phase
                        // is complete
                        cout << "You Have Passed All Phases " << getname() << endl;
                        phase++;
                        return true; // returns to main
                    } else {
                        printdeck(6); // print progress
                        printcolordeck(3); // print progress
                        cout << endl;
                        return false;
                    }
                }
                default: {
                    cout << "Invalid Phase!" << endl;
                    Quitting(); // ends program
                }
            }
            return false;
        }
        //overloaded operator
        bool operator==(const Player & opp) {
            return name == opp.name;
        }
        // detects if both classes have the same name

        bool operator>(const Player &opp){
            return phase > opp.phase;
        }
        // compares two classes's phase numbers

        bool operator<(const Player &opp){
            return phase < opp.phase;
        }
        // compares two classes's phase numbers

};

bool::Player::skipped = false;

template <typename T>
// use of a class template
class Game {
    // protected members
    protected:
        T turn;
        static int totalcards; // used to detect the total cards created
        Phase p; // aggregation
    public:
        Game() {
            turn = 0;
        }

        bool ValidatePhase(int p) {
            if (p > 10 || p < 1) {
                cout << "Invalid Phase" << endl;
                return false;
            } else {
                return true;
            }
            // detects a bad phase input
        }
        // get functions
        int gettotalcreated() {return totalcards;}
        int getturn() {return turn; }

        void changeturn() {
            try {
                if (turn > 2) {
                    throw InvalidTurn();
                }
            if (turn == 0) {
                turn = 1;
            } else {
                turn = 0;
            }
            } catch(InvalidTurn) {
                InvalidTurn();
            }
            // just changes turn for game
        }

        void menu(string n) {
            bool valid = false;
            do {
                try {
            char input;
           
            cout << n << " Type (C) For A Card | (Q) To Quit | (P) To View All Phases" << endl;
            cin >> input;

            switch(input) {
                case 'c':
                case 'C': {
                    totalcards++;
                    break;
                }
                case 'q':
                case 'Q': {
                    Quitting(); // quits program
                }
                case 'p':
                case 'P': {
                    p.printallphases();
                    valid = true; // this continues the menu
                    break;
                }
                default: {
                    throw InvalidInput();
                }
            }
        }
        catch (InvalidInput) {
            valid = true; // continues the menu
        }
    } while(valid != false); 
}
};

template <typename T>
int::Game<T>::totalcards = 0;
// template
#endif
