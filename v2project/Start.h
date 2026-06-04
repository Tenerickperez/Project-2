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
        InvalidName(int m){

        }
};
//card setup
class Card {
    private: 
        int number; // private data members
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
            number = n;
            color = c;
        }
        
        static int getotalcreated() {return totalcards; }
        int getnumber() const {return number;}
        string getcolor() const {return color;}
        bool iswild() {return number == 13;}
        bool isskip() {return number == 14;}
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
        char specialcards() {
            if (iswild()) {
                return 'w';
            } 
            if (isskip()) {
                return 's';
            }
        }

};
int Card::totalcards = 0;
class Deck {
    private:
        vector<int> numbers;
        string options[4] = {"Red", "Yellow", "Blue", "Green"};
        vector<string> colors;
    public:
        Deck() {
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

class Player {
    private:
        string name;
        int phase;
        vector<int> deck_numbers;
        vector<string> deck_colors;
        bool skipped;
    public:
        void setname(string n) {
            name = n;
        }
        string getname() const {return name;}
        int getcurrent_phase() {return phase; }
        bool isskipped() {return skipped;}
};
#endif