#include <iostream>
using namespace std;
#include <string>
#include <ctime>
#include "Start.h"

int main() {
    srand(time(0));

    int num = rand() % 7 + 1; // 1-7 range

    Card(num, "Red");
}