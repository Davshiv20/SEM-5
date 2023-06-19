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

void computeFirst(char symbol, const vector<Production>& productions);
void computeFollow(char symbol, const vector<Production>& productions);
void computePredictiveParsingTable(const vector<Production>& productions);

void printFirstSets();
void printFollowSets();
void printParsingTable();

int main() {
    int numProductions;
    cout << "Enter the number of productions: ";
    cin >> numProductions;

    vector<Production> productions(numProductions);

    for (int i = 0; i < numProductions; ++i) {
        cout << "Enter production " << (i + 1) << " (in the form A -> alpha): ";
        cin >> productions[i].lhs;
        cin.ignore();  // Ignore newline character
        getline(cin, productions[i].rhs);
    }

    for (const Production& production : productions) {
        computeFirst(production.lhs, productions);
        computeFollow(production.lhs, productions);
    }

    computePredictiveParsingTable(productions);

    cout << "\nFirst Sets:\n";
    printFirstSets();

    cout << "\nFollow Sets:\n";
    printFollowSets();

    cout << "\nPredictive Parsing Table:\n";
    printParsingTable();

    return 0;
}

void computeFirst(char symbol, const vector<Production>& productions) {
    if (firstSet.find(symbol) != firstSet.end()) {
        return;
    }

    unordered_set<char>& first = firstSet[symbol];

    for (const Production& production : productions) {
        if (production.lhs == symbol) {
            char firstSymbol = production.rhs[0];

            if (isupper(firstSymbol)) {
                computeFirst(firstSymbol, productions);

                unordered_set<char>& firstOfFirstSymbol = firstSet[firstSymbol];
                first.insert(firstOfFirstSymbol.begin(), firstOfFirstSymbol.end());
            } else {
                first.insert(firstSymbol);
            }
        }
    }
}

void computeFollow(char symbol, const vector<Production>& productions) {
    if (followSet.find(symbol) != followSet.end()) {
        return;
    }

    unordered_set<char>& follow = followSet[symbol];

    if (symbol == productions[0].lhs) {
        follow.insert('$');
    }

    for (const Production& production : productions) {
        const string& rhs = production.rhs;

        size_t pos = rhs.find(symbol);
        while (pos != string::npos) {
            if (pos < rhs.size() - 1) {
                char nextSymbol = rhs[pos + 1];

                if (isupper(nextSymbol)) {
                    unordered_set<char>& firstOfNextSymbol = firstSet[nextSymbol];
                    follow.insert(firstOfNextSymbol.begin(), firstOfNextSymbol.end());

                    if (firstOfNextSymbol.find('#') != firstOfNextSymbol.end()) {
                        follow.erase('#');
                        pos++;
                    } else {
                        break;
                    }
                } else {
                    follow.insert(nextSymbol);
                    break;
                }
            } else {
                if (production.lhs != symbol) {
                    computeFollow(production.lhs, productions);
                    unordered_set<char>& followOfLHS = followSet[production.lhs];
                    follow.insert(followOfLHS.begin(), followOfLHS.end());
                }

                break;
            }

            pos = rhs.find(symbol, pos + 1);
        }
    }
}

void computePredictiveParsingTable(const vector<Production>& productions) {
    for (const Production& production : productions) {
        char lhs = production.lhs;
        const string& rhs = production.rhs;

        char firstSymbol = rhs[0];
        if (isupper(firstSymbol)) {
            unordered_set<char>& first = firstSet[firstSymbol];
            for (char terminal : first) {
                if (terminal != '#') {
                    parsingTable[lhs][terminal] = production;
                }
            }

            if (first.find('#') != first.end()) {
                unordered_set<char>& follow = followSet[lhs];
                for (char terminal : follow) {
                    parsingTable[lhs][terminal] = production;
                }
            }
        } else {
            parsingTable[lhs][firstSymbol] = production;
        }
    }
}

void printFirstSets() {
    for (const auto& entry : firstSet) {
        char symbol = entry.first;
        const unordered_set<char>& first = entry.second;

        cout << "First(" << symbol << ") = { ";
        for (char ch : first) {
            cout << ch << " ";
        }
        cout << "}\n";
    }
}

void printFollowSets() {
    for (const auto& entry : followSet) {
        char symbol = entry.first;
        const unordered_set<char>& follow = entry.second;

        cout << "Follow(" << symbol << ") = { ";
        for (char ch : follow) {
            cout << ch << " ";
        }
        cout << "}\n";
    }
}

void printParsingTable() {
    for (const auto& row : parsingTable) {
        char lhs = row.first;
        const unordered_map<char, Production>& tableRow = row.second;

        cout << "Non-terminal: " << lhs << "\n";

        for (const auto& entry : tableRow) {
            char terminal = entry.first;
            const Production& production = entry.second;

            cout << "Terminal: " << terminal << ", Production: " << production.lhs << " -> " << production.rhs << "\n";
        }

        cout << "\n";
    }
}
