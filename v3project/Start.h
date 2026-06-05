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
        FirstCard() {
            cout << "First Card Detected" << endl;
        }
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
                cout << "You have recieved a SKIP card! This Will Skip The Another Player's Turn" << endl;
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
            cout << "Shuffling Deck...\n" << endl;
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
                if (numbers.back() == 14) {
                    swap(numbers.back(), numbers[10]);
                }
                if (numbers.back() == 13) {
                    swap(numbers.back(), numbers[9]);
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
    private:
        static vector<int> runs;
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
                     return "1 run of 9";
                }
                case 7: {
                    return "1 set of 4";
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
        bool haset(vector<int> &num, vector<string> &color) {
            bool nextphase = false;
            try {
                if (num.size() <= 1) {
                    throw FirstCard();
                }

                for (int i = 1; i < num.size(); i++) {
                    if (num[i] == 14) {
                        cout << "Your Wild Has Been Turned Into A " << num[0] << endl;
                        num[i] = num[0];
                    }
                }

                if (num.size() != 4) { 
                    for (int i = 1; i < num.size(); i++) {
                        if (num[i] != num[0]) {
                            num.pop_back();
                        }
                    }
                } else {
                    for (int i = 1; i < 4; i++) {
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
                cout << "Get 3 Cards With The Color " <<  color.back() << " OR the number " << num.back() << endl;
                cout << endl;
            }
             return false;  
        }
        bool haset_hasrun(vector<int> &num, vector<string> &color){
            for (int i = 1; i < num.size(); i++) {
                if (num[i] == num[0]) {
                    runs.push_back(num[i]);
                }
            }
             for (int i = 0; i < runs.size(); i++) {
                cout << runs[i] << endl;
            }
            return false;
        }
}; 
vector<int> Phase::runs = {};

class Player : public Phase {
    private:
        string name;
        int phase;
        vector<int> deck_numbers;
        vector<string> deck_colors;
        bool skipped;
    public:
        Player() {
            phase = 2;
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
        void printdeck() {
            for (int i=0; i < deck_numbers.size();i++) {
                cout << deck_numbers[i] << " " ;
            }
            cout << endl;
        }
        bool checkphase() {
            switch(phase) {
                case 1: {
                    if(haset(deck_numbers, deck_colors)) {
                        cout << "You Have Passed This Phase " << getname() << endl;
                        phase++;
                        return true;

                    } else {
                        printdeck();
                        return false;
                    }
                }
                case 2: {
                    haset(deck_numbers, deck_colors);
                    return false;
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
