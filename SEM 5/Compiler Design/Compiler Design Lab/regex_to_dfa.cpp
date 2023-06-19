#include <iostream>
#include <vector>

using namespace std;

// Represents a state in the DFA.
struct State {
  // The set of positions in the regular expression that can reach this state.
  vector<int> positions;

  // The next state to transition to, given the input symbol.
  State* next[256];

  // Whether this state is an accepting state.
  bool accepting;

  State() {
    accepting = false;
  }
};

// Converts a regular expression to a DFA.
State* convertToDFA(string regex) {
  // Create a syntax tree for the regular expression.
  vector<State*> nodes;
  for (int i = 0; i < regex.length(); i++) {
    nodes.push_back(new State());
  }

  // Create a mapping from positions in the regular expression to nodes.
  vector<int> positionToNode(regex.length());
  for (int i = 0; i < regex.length(); i++) {
    positionToNode[i] = nodes[i];
  }

  // Build the syntax tree.
  for (int i = 0; i < regex.length(); i++) {
    if (regex[i] == '|') {
      // The current node is a union node.
      nodes[i]->next['|'] = nodes[i + 1];
    } else if (regex[i] == '.') {
      // The current node is a concatenation node.
      nodes[i]->next['.'] = nodes[i + 1];
    } else if (regex[i] == '*') {
      // The current node is a closure node.
      nodes[i]->next['*'] = nodes[i];
    } else {
      // The current node is a terminal node.
      nodes[i]->accepting = true;
    }
  }

  // Create the DFA.
  vector<State*> states;
  for (int i = 0; i < regex.length(); i++) {
    states.push_back(nodes[i]);
  }

  // Compute the transitions for each state.
  for (int i = 0; i < states.size(); i++) {
    for (int j = 0; j < 256; j++) {
      if (states[i]->next[j] == nullptr) {
        // The current state does not have a transition for the given input symbol.
        states[i]->next[j] = states[i];
      }
    }
  }

  // Return the root of the DFA.
  return states[0];
}

int main() {
  // Get the regular expression from the user.
  string regex;
  cin >> regex;

  // Convert the regular expression to a DFA.
  State* dfa = convertToDFA(regex);

  // Print the DFA.
  for (int i = 0; i < dfa->positions.size(); i++) {
    cout << "State " << dfa->positions[i] << " -> ";
    for (int j = 0; j < 256; j++) {
      cout << dfa->next[j]->positions[0] << " ";
    }
    cout << endl;
  }

  return 0;
}