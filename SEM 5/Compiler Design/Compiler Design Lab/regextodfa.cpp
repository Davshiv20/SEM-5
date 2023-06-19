#include <iostream>
#include <vector>

using namespace std;

// This function eliminates left recursion from a given grammar.
vector<string> eliminateLeftRecursion(const vector<string>& productions) {
  // Create a new vector to store the new productions.
  vector<string> newProductions;

  // Iterate over the given productions.
  for (const string& production : productions) {
    // If the production is left recursive, then eliminate it.
    if (production.find(production[0]) != string::npos) {
      // Create a new non-terminal to represent the left-recursive part of the production.
      string newNonTerminal = production[0] + "'";

      // Add a new production to the new vector that replaces the left-recursive part with the new non-terminal.
      newProductions.push_back(production.substr(0, production.find(production[0])) + newNonTerminal);

      // Add a new production to the new vector that produces the new non-terminal followed by the right-hand side of the original production.
      newProductions.push_back(newNonTerminal + production.substr(production.find(production[0]) + 1));
    } else {
      // If the production is not left recursive, then add it to the new vector as-is.
      newProductions.push_back(production);
    }
  }

  // Return the new vector of productions.
  return newProductions;
}

int main() {
  // Create a vector to store the given productions.
  vector<string> productions = {
    "S -> S + T | T",
    "T -> T * F | F",
    "F -> ( S ) | id"
  };

  // Eliminate left recursion from the given productions.
  vector<string> newProductions = eliminateLeftRecursion(productions);

  // Print the new productions.
  for (const string& production : newProductions) {
    cout << production << endl;
  }

  return 0;
}
