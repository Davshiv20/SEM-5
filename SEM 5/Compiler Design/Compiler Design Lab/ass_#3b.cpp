#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

struct Production {
    char lhs;
    string rhs;
};

unordered_map<char, unordered_set<char>> firstSet;
unordered_map<char, unordered_set<char>> followSet;
unordered_map<char, unordered_map<char, Production>> parsingTable;

void computeFirstSets(const vector<Production>& productions);
void computeFollowSets(const vector<Production>& productions);
bool isLL1Grammar(const vector<Production>& productions);
void printFirstSets();
void printFollowSets();
void printParsingTable();

int main() {
    int numProductions;
    cout << "Enter the number of productions: ";
    cin >> numProductions;

    vector<Production> productions(numProductions);
    cout << "Enter the productions in the form A -> alpha:\n";
    for (int i = 0; i < numProductions; i++) {
        cout << "Enter production " << i + 1 << ": ";
        cin >> productions[i].lhs;
        cin.ignore(); // Ignore the '->' symbol
        getline(cin, productions[i].rhs);
    }

    computeFirstSets(productions);
    computeFollowSets(productions);
    bool isLL1 = isLL1Grammar(productions);

    cout << "\nFirst Sets:\n";
    printFirstSets();

    cout << "\nFollow Sets:\n";
    printFollowSets();

    cout << "\nParsing Table:\n";
    printParsingTable();

    cout << "\nGiven grammar is" << (isLL1 ? " LL(1)." : " not LL(1).") << endl;

    return 0;
}

void computeFirstSets(const vector<Production>& productions) {
    for (const Production& production : productions) {
        char lhs = production.lhs;
        const string& rhs = production.rhs;

        char firstSymbol = rhs[0];
        if (isupper(firstSymbol)) {
            unordered_set<char>& first = firstSet[lhs];
            first.insert(firstSymbol);
        } else {
            unordered_set<char>& first = firstSet[lhs];
            first.insert(firstSymbol);
        }
    }
}

void computeFollowSets(const vector<Production>& productions) {
    for (const Production& production : productions) {
        char lhs = production.lhs;
        const string& rhs = production.rhs;

        for (int i = 0; i < rhs.length(); i++) {
            char symbol = rhs[i];
            if (isupper(symbol)) {
                unordered_set<char>& follow = followSet[symbol];
                if (i == rhs.length() - 1) {
                    follow.insert(lhs);
                } else {
                    char nextSymbol = rhs[i + 1];
                    if (isupper(nextSymbol)) {
                        const unordered_set<char>& first = firstSet[nextSymbol];
                        follow.insert(first.begin(), first.end());
                    } else {
                        follow.insert(nextSymbol);
                    }
                }
            }
        }
    }
}

bool isLL1Grammar(const vector<Production>& productions) {
    for (const Production& production : productions) {
        char lhs = production.lhs;
        const string& rhs = production.rhs;

        char firstSymbol = rhs[0];
        if (!isupper(firstSymbol)) {
            continue;
        }

        unordered_map<char, Production>& tableRow = parsingTable[lhs];
        const unordered_set<char>& first = firstSet[firstSymbol];
        for (char terminal : first) {
            if (tableRow.find(terminal) != tableRow.end()) {
                return false;
            }
            tableRow[terminal] = production;
        }

        if (first.find('#') != first.end()) {
            const unordered_set<char>& follow = followSet[lhs];
            for (char terminal : follow) {
                if (tableRow.find(terminal) != tableRow.end()) {
                    return false;
                }
                tableRow[terminal] = production;
            }
        }
    }

    return true;
}

void printFirstSets() {
    for (const auto& entry : firstSet) {
        cout << "First(" << entry.first << ") = { ";
        const unordered_set<char>& first = entry.second;
        for (char symbol : first) {
            cout << symbol << " ";
        }
        cout << "}\n";
    }
}

void printFollowSets() {
    for (const auto& entry : followSet) {
        cout << "Follow(" << entry.first << ") = { ";
        const unordered_set<char>& follow = entry.second;
        for (char symbol : follow) {
            cout << symbol << " ";
        }
        cout << "}\n";
    }
}

void printParsingTable() {
    for (const auto& entry : parsingTable) {
        char nonTerminal = entry.first;s
        const unordered_map<char, Production>& tableRow = entry.second;

        for (const auto& cell : tableRow) {
            char terminal = cell.first;
            const Production& production = cell.second;

            cout << "M[" << nonTerminal << ", " << terminal << "] = ";
            cout << production.lhs << " -> " << production.rhs << endl;
        }
    }
}
