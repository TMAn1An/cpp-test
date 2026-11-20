/*
 * Assignment 02 - Theory of Computation
 * Program for the control of an automatic sliding door using DFA.
 *
 * There is a sensor on the FRONT side and one on the REAR side.
 * If a person is on any side, the door opens. When nobody is
 * there, the door closes.
 *
 * DFA:
 *   Q    = {CLOSE, OPEN}
 *   E    = {NONE, REAR, FRONT, BOTH}   (where people are standing)
 *   q_st = CLOSE
 *   F    = {} (empty set) - the door keeps running, there is no
 *          "accept" or "reject", we only care about the current state
 *
 * Truth table (1 = person on that sensor):
 *   rear  front  | state
 *    0     0     | CLOSE
 *    1     0     | OPEN
 *    0     1     | OPEN
 *    1     1     | OPEN
 *   so the door is OPEN = rear OR front
 */

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

enum State { CLOSE = 0, OPEN = 1 };
enum Input { NONE = 0, REAR = 1, FRONT = 2, BOTH = 3, INVALID = -1 };

// transition table: next = delta[current state][input]
//                  NONE    REAR   FRONT  BOTH
const State delta[2][4] = {
    /* CLOSE */   { CLOSE,  OPEN,  OPEN,  OPEN },
    /* OPEN  */   { CLOSE,  OPEN,  OPEN,  OPEN }
};

string stateName(State s) {
    return (s == CLOSE) ? "CLOSE" : "OPEN";
}

string inputName(Input in) {
    switch (in) {
        case NONE:  return "NONE";
        case REAR:  return "REAR";
        case FRONT: return "FRONT";
        case BOTH:  return "BOTH";
        default:    return "?";
    }
}

// sensor bits for the truth table: rear bit, front bit
string sensorBits(Input in) {
    switch (in) {
        case NONE:  return "rear=0 front=0";
        case REAR:  return "rear=1 front=0";
        case FRONT: return "rear=0 front=1";
        case BOTH:  return "rear=1 front=1";
        default:    return "";
    }
}

string toUpper(string s) {
    for (size_t i = 0; i < s.size(); i++) {
        s[i] = toupper((unsigned char)s[i]);
    }
    return s;
}

// accepts the full word, the first letter, the menu number,
// or the two sensor bits (rear front) like 10 or 01
Input readInput(const string& token) {
    string t = toUpper(token);
    if (t == "NONE"  || t == "N" || t == "1" || t == "00") return NONE;
    if (t == "REAR"  || t == "R" || t == "2" || t == "10") return REAR;
    if (t == "FRONT" || t == "F" || t == "3" || t == "01") return FRONT;
    if (t == "BOTH"  || t == "B" || t == "4" || t == "11") return BOTH;
    return INVALID;
}

// a short reason for each move, so the output is easy to follow
string reason(State from, Input in) {
    if (in == NONE) {
        return (from == OPEN) ? "nobody around, door closes"
                              : "nobody around, stays closed";
    }
    return (from == CLOSE) ? "someone is there, door opens"
                           : "someone is still there, stays open";
}

int main() {
    cout << "=============================================\n";
    cout << "   Automatic Sliding Door Controller (DFA)\n";
    cout << "=============================================\n";
    cout << "Inputs (where people are standing):\n";
    cout << "  1 / N / 00 = NONE   (no one on either side)\n";
    cout << "  2 / R / 10 = REAR   (someone at the rear)\n";
    cout << "  3 / F / 01 = FRONT  (someone at the front)\n";
    cout << "  4 / B / 11 = BOTH   (people on both sides)\n";
    cout << "Enter one input at a time. Type 'exit' to stop.\n";

    State current = CLOSE;   // start state
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
        cout << "  [" << sensorBits(in) << "]  "
             << stateName(current) << " --" << inputName(in) << "--> "
             << stateName(next) << "   (" << reason(current, in) << ")\n";
        current = next;
        step++;
    }

    cout << "\nFinal state of the door: " << stateName(current) << "\n";
    cout << "Program ended.\n";
    return 0;
}
