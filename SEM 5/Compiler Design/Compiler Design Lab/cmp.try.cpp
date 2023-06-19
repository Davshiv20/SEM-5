#include <iostream>
#include <vector>
#include <stack>
#include <map>
using namespace std;

struct State {
    bool isFinal;
    map<char, int> transitions;
};

class DFA {
    vector<State> states;
    stack<int> stateStack;
    int currentState;

public:
    DFA(string regex) {
        currentState = 0;
        constructDFA(regex);
    }

    void constructDFA(string regex) {
        for (int i = 0; i < regex.length(); i++) {
            char c = regex[i];

            if (c == '(') {
                stateStack.push(currentState);
            } else if (c == ')') {
                int prevState = stateStack.top();
                stateStack.pop();
                currentState = prevState;
            } else if (c == '*') {
                int prev = currentState;
                currentState++;
                states[prev].transitions[' '] = currentState;
                states[currentState].transitions[' '] = prev;
                states[currentState].transitions['#'] = currentState + 1;
                states[currentState + 1].transitions[' '] = currentState;
                currentState++;
            } else if (c == '|') {
                int prevState = stateStack.top();
                stateStack.pop();
                states[currentState].transitions[' '] = currentState + 1;
                states[currentState].transitions[' '] = prevState + 1;
                states[prevState].transitions[' '] = currentState + 1;
                currentState++;
            } else {
                State state;
                state.isFinal = false;
                states.push_back(state);

                states[currentState].transitions[c] = currentState + 1;
                currentState++;
            }
        }

        states[currentState].isFinal = true;
    }

    bool match(string input) {
        int currentState = 0;

        for (int i = 0; i < input.length(); i++) {
            char c = input[i];
            
            if (states[currentState].transitions.find(c) != states[currentState].transitions.end()) {
                currentState = states[currentState].transitions[c];
            } else if (states[currentState].transitions.find('#') != states[currentState].transitions.end()) {
                currentState = states[currentState].transitions['#'];
                i--; // Retry current character
            } else {
                return false;
            }
        }

        return states[currentState].isFinal;
    }
};

int main() {
    string regex;
    cout << "Enter a regular expression: ";
    cin >> regex;

    DFA dfa(regex);

    string input;
    cout << "Enter an input string: ";
    cin >> input;

    bool isMatch = dfa.match(input);

    if (isMatch) {
        cout << "The input string matches the regular expression." << endl;
    } else {
        cout << "The input string does not match the regular expression." << endl;
    }
	    return 0;
}

