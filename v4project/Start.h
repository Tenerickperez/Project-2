#ifndef START_H
#define START_H
//exception classes

class InvalidCardRange {
    public:
        InvalidCardRange(int m) {
            cout << "Card Range Must Be 1-12" << endl;
            cout << "Your Card Number Was " << m << endl;
            cout << "ERROR...SHUTTING DOWN" << endl;
        }
};
class InvalidName {
    public:
        InvalidName(){
            cout << "Name is not valid!!" << endl;
        }
};
class InvalidInput {
    public:
        InvalidInput() {
            cout << "Input Was Invalid, Please Try Again!" << endl;
        }
};
class FirstCard {
    public: 
        FirstCard() {}
};
//card setup
class Card {
     // private data members
    private: 
        int number;
        static int totalcards;
        string color;
    public:
        Card(int n, string c){
            try {
                if (n < 1 || n > 14) {
                    throw InvalidCardRange(n);
                }
                number = n;
                color = c;
            } catch (InvalidCardRange) {
                exit(EXIT_FAILURE);
            }
            print_card();
        }
        
        static int getotalcreated() {return totalcards; }
        int getnumber() const {return number;}
        string getcolor() const {return color;}
        bool iswild() {return number == 14;}
        bool isskip() {return number == 13;}
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
            if (!specialcards()) {
                cout << "You got a " << number << " " << color << endl;
            }
        }

};
int Card::totalcards = 0;
class Deck {
    private:
        vector<int> numbers;
        string options[4] = {"Red", "Yellow", "Blue", "Green"};
        vector<string> colors;
        bool firstrun;
    public:
        Deck() {
            firstrun = true;
            cout << "Shuffling Deck..." << endl;
            fillcards();
            shuffle();
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
            for (int i = 0; i < 8; i++) {
                numbers.push_back(14); // wild cards
            }
        }
        void shuffle() {
            for (int i = 0; i < numbers.size() - 1; i++){
                int p = rand() % numbers.size() - 1 + 1; // 1-48
                swap(numbers[i], numbers[p]);
            }
            if (firstrun == true) {
                int secondtolast = numbers.size() - 2;
                if (numbers.back() == 14) {
                    // swap(numbers.back(), numbers[10]); // realized the swap to postion 10 could contain a wild.
                    numbers.back() = 7;
                } else if (numbers[secondtolast] == 14) {
                    numbers[secondtolast] = 7;
                }
                if (numbers.back() == 13) {
                    // swap(numbers.back(), numbers[9]); // realized the swap to postion 9 could contain a skip.
                    numbers.back() = 1;
                } else if (numbers[secondtolast] == 13) {
                    numbers[secondtolast] = 1;
                }
            }
            firstrun = false;
        }

        void shuffled_deck() {
            for (int i = 0; i < numbers.size(); i++){
                cout << numbers[i] << " " ;
            }
            cout << endl;
        }
        Card set() {
            int value = numbers.back();
            Card c(value, "Red");
            numbers.pop_back();
            return c;
        }
        int size() const {return numbers.size();}
        bool empty_numbers()  {return numbers.empty();}
        bool empty_colors() {return colors.empty();}
};
class Phase {
    public:
        string phase_description(int p) {
            switch(p) {
                case 1: {
                    return "1 Set of 3 (1 Group Of 3 Of The Same Cards disregarding colors)";
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
                     return "1 set of 4";
                    }
                 case 10: {
                     return "1 set of 5 + 1 set of 2";
                }
                default: {
                    return "Phase Number Out Of Range!";
                }
            }
        }
        bool haset(vector<int> &num, vector<string> &color, int set) {
            bool nextphase = false;
            try {
                if (num.size() <= 1) {
                    throw FirstCard();
                }

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
                            nextphase = true;
                        } else {
                            nextphase = false;
                            num.pop_back();
                            break;
                        }
                    }
                }
                
                if (nextphase == true) {
                    return true;
                } 
            } catch (FirstCard) {
                cout << "Get " << set - 1 << " Cards With The number " << num[0] << endl;
                cout << endl;
            }
             return false;  
        }
        bool haset_hasrun(vector<int> &num, vector<string> &color, vector<int> &placeholder, int set, int run){
            bool rundone = false;
            bool setdone = false;
            int nextnum = 0;
           
            try {
                if (num.size() <= 1) {
                    throw FirstCard();
                }

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
            if (num.back() == 0 && placeholder.back() == 0) {
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
                    throw FirstCard();
                }
                for (int i = 1; i < num.size(); i++) {
                    if (num[i] == 14) {
                        num[i] = num[0];
                        color[i] = color[0];
                    }
                }

                if (num.size() < set) { 
                    for (int i = 1; i < num.size(); i++) {
                        if (num[i] != num[0]) {
                            num.pop_back();
                        }
                    }
                } 

                if (num.size() == set) {
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

                if (color.size() < set2) {
                    for (int i = 1; i < color.size(); i++) {
                        if (color[i] != color[0]) {
                            color.pop_back();
                        }
                    }
                }

                if (color.size() == set2) {
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
                    color.push_back("White");
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
}; 

class Player : public Phase {
    private:
        string name;
        int phase;
        vector<int> deck_numbers;
        vector<string> deck_colors;
        bool skipped;
        vector<int> deck_placeholder;
    public:
        Player() {
            phase = 7;
        }
        void setname(string n) {
            try {
                if (n.length() > 10) {
                    throw InvalidName();
                }
                name = n;
            } catch (InvalidName) {
                exit(EXIT_FAILURE);
            }
        }
        string getname() const {return name;}
        int getcurrent_phase() {return phase; }
        string print_phasedesc() {return phase_description(phase);}
        bool isskipped() {return skipped;}
        void clearcards() {deck_numbers.clear(); deck_colors.clear();}
        void addcard(Card c) {
            deck_numbers.push_back(c.getnumber());
            deck_colors.push_back(c.getcolor());
        }
        void printdeck(int set) {
            if (deck_numbers.size() < set) {
            cout << "Current Set Progress (" ;
            for (int i=1; i < deck_numbers.size();i++) {
                cout << deck_numbers[i] << ", " ;
            }
            cout << ")" << endl;
            }
        }
        void printplaceholder(int run) {
            if (deck_placeholder.size() < run ) {
            cout << "Current Run Progress (";
            for (int i = 0; i < deck_placeholder.size(); i++) {
                cout << deck_placeholder[i] << ", " ;
            }
            cout << ")" << endl;
            }
        }
        void printcolordeck(int set) {
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
                    if(haset(deck_numbers, deck_colors, 4)) {
                        cout << "You Have Passed This Phase " << getname() << endl;
                        phase++;
                        return true;

                    } else {
                        printdeck(4);
                        return false;
                    }
                }
                case 2: {
                    if(haset_hasrun(deck_numbers, deck_colors, deck_placeholder, 4 , 4)) {
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
                    if(haset_hasrun(deck_numbers, deck_colors, deck_placeholder, 5,4)) {
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
                    if(hasrun(deck_numbers, deck_colors, deck_placeholder, 7)) {
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
                    if(hasrun(deck_numbers, deck_colors, deck_placeholder, 8)) {
                        cout << "You Have Passed This Phase " << getname() << endl;
                        phase++;
                        return true;
                    } else {
                        printplaceholder(8);
                        cout << endl;
                        return false;
                    }
                } case 6: {
                    if(hasset_haset(deck_numbers, deck_colors, 5, 3)) {
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
                    if (haset(deck_numbers, deck_colors, 6)) {
                        cout << "You Have Passed This Phase " << getname() << endl;
                        phase++;
                        return true;
                    } else {
                        printdeck(6);
                        cout << endl;
                        return false;
                    }
                }
            }
            return false;
        }
};

class Game : public Player {
    private:
        int turn;
    public:
        Game() {
            turn = 0;
        }
        int getturn() {return turn; }
        void changeturn() {
            if (turn == 0) {
                turn = 1;
            } else {
                turn = 0;
            }
        }
        void menu(string n) {
            bool valid = false;
            do {
                try {
            char input;
           
            cout << n << " Type (C) For A Card Or (Q) To Quit" << endl;
            cin >> input;
            switch(input) {
                case 'c':
                case 'C': {
                    break;
                }
                case 'q':
                case 'Q': {
                    cout << "Quitting..." << endl;
                    exit(EXIT_FAILURE);
                }
                default: {
                    throw InvalidInput();
                }
            }
        }
        catch (InvalidInput) {
            valid = true;
        }
    } while(valid != false);
}
};
#endif
