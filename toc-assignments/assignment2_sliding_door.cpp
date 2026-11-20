/*
 * Assignment 02 - Theory of Computation
 * Controller for an automatic sliding door, built as a DFA.
 *
 * There is one sensor pad in FRONT of the door and one at the REAR.
 * The door opens when someone is waiting in front, and it must not
 * swing into a person who is standing behind it.
 *
 * DFA:
 *   Q   = {CLOSED, OPEN}
 *   E   = {NONE, FRONT, REAR, BOTH}   (where people are standing)
 *   q0  = CLOSED
 *   F   = {} (empty) - the door just keeps running, there is no
 *         "accept" or "reject", we only care about the current state
 */

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

enum State { CLOSED = 0, OPEN = 1 };
enum Input { NONE = 0, FRONT = 1, REAR = 2, BOTH = 3, INVALID = -1 };

// transition table: next = delta[current state][input]
//                  NONE     FRONT   REAR    BOTH
const State delta[2][4] = {
    /* CLOSED */  { CLOSED,  OPEN,   CLOSED, CLOSED },
    /* OPEN   */  { CLOSED,  OPEN,   OPEN,   OPEN   }
};

string stateName(State s) {
    return (s == CLOSED) ? "CLOSED" : "OPEN";
}

string inputName(Input in) {
    switch (in) {
        case NONE:  return "NONE";
        case FRONT: return "FRONT";
        case REAR:  return "REAR";
        case BOTH:  return "BOTH";
        default:    return "?";
    }
}

string toUpper(string s) {
    for (size_t i = 0; i < s.size(); i++) {
        s[i] = toupper((unsigned char)s[i]);
    }
    return s;
}

// accepts the full word, the first letter, or the menu number
Input readInput(const string& token) {
    string t = toUpper(token);
    if (t == "NONE"  || t == "N" || t == "1") return NONE;
    if (t == "REAR"  || t == "R" || t == "2") return REAR;
    if (t == "FRONT" || t == "F" || t == "3") return FRONT;
    if (t == "BOTH"  || t == "B" || t == "4") return BOTH;
    return INVALID;
}

// a short reason for each move, so the output is easy to follow
string reason(State from, Input in) {
    if (from == CLOSED) {
        if (in == FRONT) return "someone is in front, door opens";
        if (in == REAR)  return "someone is behind, opening would hit them";
        if (in == BOTH)  return "someone is behind, so it stays shut";
        return "nobody around, stays closed";
    } else {
        if (in == NONE)  return "nobody around, door closes";
        return "someone is still on a pad, keep it open";
    }
}

int main() {
    cout << "=============================================\n";
    cout << "   Automatic Sliding Door Controller (DFA)\n";
    cout << "=============================================\n";
    cout << "Inputs (where people are standing):\n";
    cout << "  1 / N = NONE   (no one on either pad)\n";
    cout << "  2 / R = REAR   (someone on the rear pad)\n";
    cout << "  3 / F = FRONT  (someone on the front pad)\n";
    cout << "  4 / B = BOTH   (people on both pads)\n";
    cout << "Enter one input at a time. Type 'exit' to stop.\n";

    State current = CLOSED;   // start state
    cout << "\nDoor starts in state: " << stateName(current) << "\n";

    string token;
    int step = 1;
    while (true) {
        cout << "\nInput " << step << ": ";
        if (!(cin >> token)) break;
        if (toUpper(token) == "EXIT") break;

        Input in = readInput(token);
        if (in == INVALID) {
            cout << "  Not a valid input, try N, R, F or B (or 1-4).\n";
            continue;
        }

        State next = delta[current][in];
        cout << "  " << stateName(current) << " --" << inputName(in) << "--> "
             << stateName(next) << "   (" << reason(current, in) << ")\n";
        current = next;
        step++;
    }

    cout << "\nFinal state of the door: " << stateName(current) << "\n";
    cout << "Program ended.\n";
    return 0;
}
