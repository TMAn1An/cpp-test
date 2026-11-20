// Assignment 02: Control of a sliding door using DFA
// Q = {CLOSE, OPEN}, Sigma = {NONE, REAR, FRONT, BOTH}, q_st = CLOSE, F = {}
#include <iostream>
#include <string>
using namespace std;

string stateName[2] = {"CLOSE", "OPEN"};
string inputName[4] = {"NONE", "REAR", "FRONT", "BOTH"};

// delta[state][input]  NONE REAR FRONT BOTH
int delta[2][4] = {
    {0, 1, 1, 1},    // CLOSE
    {0, 1, 1, 1}     // OPEN
};

int main() {
    int state = 0, in;                       // start state = CLOSE
    cout << "Sliding Door Controller (DFA)\n";
    cout << "1 = NONE, 2 = REAR, 3 = FRONT, 4 = BOTH, 0 = exit\n";
    cout << "Door is " << stateName[state] << "\n";

    while (true) {
        cout << "\nWho is at the door? ";
        if (!(cin >> in) || in == 0) break;
        if (in < 1 || in > 4) {
            cout << "Invalid input\n";
            continue;
        }
        int next = delta[state][in - 1];
        cout << stateName[state] << " --" << inputName[in - 1]
             << "--> " << stateName[next] << "\n";
        state = next;
    }
    cout << "\nFinal state: " << stateName[state] << "\n";
    return 0;
}
