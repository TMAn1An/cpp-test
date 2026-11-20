/*
 * Assignment 01 - Theory of Computation
 * Scanner to verify whether a string is a valid C/C++ identifier,
 * built as a DFA (Deterministic Finite Automaton).
 *
 * Rule for an identifier:
 *   - it starts with a letter or underscore '_'
 *   - followed by any string of letters, digits or '_'
 *
 *   L = { _, a..z, A..Z }      (letters, underscore counted as a letter)
 *   D = { 0..9 }               (digits)
 *   Sigma = L U D
 *
 *   identifier = { Lw | w is in (L U D)* }
 *
 * DFA:
 *   Q  = {q0, q1, q2}
 *   q0 = start state
 *   q1 = final state (string read so far is a valid identifier)
 *   q2 = dead state (once here, the string can never be valid)
 *   F  = {q1}
 */

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

// states of the DFA
enum State { Q0 = 0, Q1 = 1, Q2 = 2 };

// every character falls into one of these groups
// OTHER = anything not in Sigma (like @, -, space, $)
enum Symbol { L = 0, D = 1, OTHER = 2 };

// transition table: next = delta[current state][symbol]
//                  L     D     OTHER
const State delta[3][3] = {
    /* q0 */      { Q1,   Q2,   Q2 },
    /* q1 */      { Q1,   Q1,   Q2 },
    /* q2 */      { Q2,   Q2,   Q2 }
};

Symbol classify(char c) {
    if (isalpha((unsigned char)c) || c == '_') return L;
    if (isdigit((unsigned char)c)) return D;
    return OTHER;
}

string stateName(State s) {
    if (s == Q0) return "q0";
    if (s == Q1) return "q1";
    return "q2";
}

string symbolName(Symbol s) {
    if (s == L) return "L";
    if (s == D) return "D";
    return "not in Sigma";
}

// C++ keywords match the pattern but can't be used as identifiers,
// so we check them separately after the DFA says yes.
bool isKeyword(const string& w) {
    const char* keywords[] = {
        "alignas", "alignof", "and", "and_eq", "asm", "auto", "bitand",
        "bitor", "bool", "break", "case", "catch", "char", "char16_t",
        "char32_t", "class", "compl", "const", "constexpr", "const_cast",
        "continue", "decltype", "default", "delete", "do", "double",
        "dynamic_cast", "else", "enum", "explicit", "export", "extern",
        "false", "float", "for", "friend", "goto", "if", "inline", "int",
        "long", "mutable", "namespace", "new", "noexcept", "not", "not_eq",
        "nullptr", "operator", "or", "or_eq", "private", "protected",
        "public", "register", "reinterpret_cast", "return", "short",
        "signed", "sizeof", "static", "static_assert", "static_cast",
        "struct", "switch", "template", "this", "thread_local", "throw",
        "true", "try", "typedef", "typeid", "typename", "union", "unsigned",
        "using", "virtual", "void", "volatile", "wchar_t", "while", "xor",
        "xor_eq"
    };
    int n = sizeof(keywords) / sizeof(keywords[0]);
    for (int i = 0; i < n; i++) {
        if (w == keywords[i]) return true;
    }
    return false;
}

// runs the DFA on the string and prints each move
State runDFA(const string& input) {
    State current = Q0;
    cout << "  Start at " << stateName(current) << "\n";

    for (size_t i = 0; i < input.size(); i++) {
        Symbol sym = classify(input[i]);
        State next = delta[current][sym];
        cout << "  '" << input[i] << "' (" << symbolName(sym) << ") : "
             << stateName(current) << " -> " << stateName(next) << "\n";
        current = next;
    }
    return current;
}

int main() {
    cout << "=============================================\n";
    cout << "   Scanner for C/C++ identifiers (DFA)\n";
    cout << "=============================================\n";
    cout << "Type a string and press Enter.\n";
    cout << "Type 'exit' to stop.\n";

    string line;
    while (true) {
        cout << "\nEnter string: ";
        if (!getline(cin, line)) break;
        if (line == "exit") break;

        State last = runDFA(line);
        cout << "  Final state: " << stateName(last) << "\n";

        if (last != Q1) {
            cout << "  Result: \"" << line << "\" is NOT a valid identifier\n";
        } else if (isKeyword(line)) {
            cout << "  Result: \"" << line << "\" fits the pattern, but it is "
                 << "a reserved keyword, so it can't be used as an identifier\n";
        } else {
            cout << "  Result: \"" << line << "\" is a VALID identifier\n";
        }
    }

    cout << "\nProgram ended.\n";
    return 0;
}
