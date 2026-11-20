// Assignment 01: Scanner to verify a valid C/C++ identifier using DFA
// L = {_, a-z, A-Z},  D = {0-9},  identifier = { Lw | w in (L U D)* }
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// states : 0 = q0 (start), 1 = q1 (final), 2 = q2 (dead)
// symbols: 0 = L, 1 = D, 2 = other (not in Sigma)
int delta[3][3] = {
    {1, 2, 2},   // q0
    {1, 1, 2},   // q1
    {2, 2, 2}    // q2
};

int symbolOf(char c) {
    if (isalpha((unsigned char)c) || c == '_') return 0;   // L
    if (isdigit((unsigned char)c)) return 1;               // D
    return 2;                                              // other
}

int main() {
    string s;
    cout << "Scanner for C/C++ identifier (DFA)\n";
    cout << "Type 'exit' to stop.\n";
    while (true) {
        cout << "\nEnter string: ";
        if (!getline(cin, s) || s == "exit") break;

        int state = 0;                       // start at q0
        cout << "q0";
        for (size_t i = 0; i < s.size(); i++) {
            state = delta[state][symbolOf(s[i])];
            cout << " -" << s[i] << "-> q" << state;
        }
        if (state == 1)                      // q1 is the final state
            cout << "\nResult: " << s << " is a VALID identifier\n";
        else
            cout << "\nResult: " << s << " is NOT a valid identifier\n";
    }
    return 0;
}
