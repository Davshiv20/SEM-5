#include <iostream>
#include <vector>

using namespace std;

// A struct to represent a state in the DFA
struct State {
  int id;
  vector<int> transitions;
  bool accepting;
};

// A function to construct the DFA from the given regular expression
vector<State> constructDFA(string regex) {
  // Create a syntax tree for the regular expression
  vector<State> states;
  State startState;
  startState.id = 0;
  startState.accepting = false;
  states.push_back(startState);

  for (int i = 0; i < regex.length(); i++) {
    char c = regex[i];

    // If the character is a literal, create a new state for it
    if (isalpha(c)) {
      State newState;
      newState.id = states.size();
      newState.transitions.push_back(i);
      newState.accepting = false;
      states.push_back(newState);
    }

    // If the character is a *, create a new state for it and connect it to the
    // current state
    else if (c == '*') {
      State newState;
      newState.id = states.size();
      newState.transitions.push_back(i);
      newState.accepting = false;
      states.push_back(newState);

      for (int j = 0; j < states.size(); j++) {
        states[j].transitions.push_back(newState.id);
      }
    }

    // If the character is a |, create a new state for it and connect it to the
    // current state and the next state
    else if (c == '|') {
      State newState;
      newState.id = states.size();
      newState.transitions.push_back(i);
      newState.accepting = false;
      states.push_back(newState);

      for (int j = 0; j < states.size(); j++) {
        states[j].transitions.push_back(newState.id);
      }
    }

    // If the character is a #, mark the current state as accepting
    else if (c == '#') {
      states[states.size() - 1].accepting = true;
    }
  }

  return states;
}

// A function to print the DFA
void printDFA(vector<State> dfa) {
  for (int i = 0; i < dfa.size(); i++) {
    cout << "State " << dfa[i].id << ": ";
    for (int j = 0; j < dfa[i].transitions.size(); j++) {
      cout << dfa[i].transitions[j] << " ";
    }
    cout << "(accepting: " << dfa[i].accepting << ")" << endl;
  }
}

int main() {
  string regex = "(a|b)*abb#";
  vector<State> dfa = constructDFA(regex);
  printDFA(dfa);

  return 0;
}