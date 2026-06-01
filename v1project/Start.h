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
//card setup
class Card {
    private: 
        int number; // private data members
        static int totalcards;
        string color;
    public:
        Card(); // constructor
        Card(int n, string c) {
            try {
                if (n < 1 || n > 14) {
                    throw InvalidCardRange(n);
                }
                number = n;
                color = c;
            } catch (InvalidCardRange) {
                exit(EXIT_FAILURE);
            }
        }
        static int getotalcreated() {return totalcards; }
        int getnumber() const {return number;}
        string getcolor() const {return color;}
        bool iswild() {return number == 7;}
        bool isskip() {return number == 8;}
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

};

#endif