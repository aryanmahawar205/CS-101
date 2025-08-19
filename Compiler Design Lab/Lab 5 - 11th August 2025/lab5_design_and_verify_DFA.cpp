#include <bits/stdc++.h>

using namespace std;

int main() {
    int totalStates, totalSymbols, totalAcceptStates;
    string initialState;

    cout << "How many states does your DFA have? ";
    cin >> totalStates;

    cout << "How many symbols are in the input alphabet? ";
    cin >> totalSymbols;

    vector<char> alphabet(totalSymbols);
    cout << "List the input symbols (separated by spaces): ";
    for (int i = 0; i < totalSymbols; i++) {
        cin >> alphabet[i];
    }

    // Transition mapping: (state, symbol) -> next_state
    map<pair<string, char>, string> transitions;

    cout << "\nNow define the state transitions in the format:\n";
    cout << "[current_state] [input_symbol] [next_state]\n";
    cout << "Type 'stop' when you are done entering transitions.\n";

    while (true) {
        string current;
        cin >> current;
        if (current == "stop") break;

        char symbol;
        string next;
        cin >> symbol >> next;

        transitions[{current, symbol}] = next;
    }

    cout << "\nEnter the starting state: ";
    cin >> initialState;

    cout << "How many accepting (final) states? ";
    cin >> totalAcceptStates;

    vector<string> acceptingStates(totalAcceptStates);
    cout << "Enter the accepting states: ";
    for (int i = 0; i < totalAcceptStates; i++) {
        cin >> acceptingStates[i];
    }

    string testString;
    cout << "\nEnter the string you want to test: ";
    cin >> testString;

    string currentState = initialState;
    cout << "\nDFA Processing Trace:\n";
    cout << "(Start) " << currentState << endl;

    for (char symbol : testString) {
        if (transitions.find({currentState, symbol}) == transitions.end()) {
            cout << "No transition found for (" << currentState << ", " << symbol << ") → REJECTED\n";
            return 0;
        }
        string nextState = transitions[{currentState, symbol}];
        cout << currentState << " --" << symbol << "--> " << nextState << endl;
        currentState = nextState;
    }

    bool isAccepted = false;
    for (const string &fs : acceptingStates) {
        if (currentState == fs) {
            isAccepted = true;
            break;
        }
    }

    cout << "Final state reached: " << currentState << endl;
    if (isAccepted) {
        cout << "The string is ACCEPTED by the DFA.\n";
    } else {
        cout << "The string is REJECTED by the DFA.\n";
    }

    return 0;
}