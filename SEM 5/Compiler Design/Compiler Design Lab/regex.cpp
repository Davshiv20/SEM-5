#include <bits/stdc++.h>

using namespace std;

// Represents a state in the NFA
struct State {
    char label;
    State *edge1;
    State *edge2;
};

// Represents an NFA fragment
struct Frag {
    State *start;
    State *end;
};

// Converts a regular expression to an NFA
Frag regexToNFA(const string& regex) {
    stack<Frag> fragStack;
    
    for (char c : regex) {
        if (c == '.') {
            Frag frag2 = fragStack.top();
            fragStack.pop();
            Frag frag1 = fragStack.top();
            fragStack.pop();
            
            frag1.end->edge1 = frag2.start;
            
            fragStack.push({frag1.start, frag2.end});
        } else if (c == '|') {
            Frag frag2 = fragStack.top();
            fragStack.pop();
            Frag frag1 = fragStack.top();
            fragStack.pop();
            
            State *start = new State{'\0', frag1.start, frag2.start};
            State *end = new State{'\0', nullptr, nullptr};
            
            frag1.end->edge1 = end;
            frag2.end->edge1 = end;
            
            fragStack.push({start, end});
        } else if (c == '*') {
            Frag frag = fragStack.top();
            fragStack.pop();
            
            State *start = new State{'\0', frag.start, nullptr};
            State *end = new State{'\0', nullptr, nullptr};
            
            frag.end->edge1 = frag.start;
            frag.end->edge2 = end;
            
            fragStack.push({start, end});
        } else {
            State *start = new State{c, nullptr, nullptr};
            State *end = new State{'\0', nullptr, nullptr};
            
            start->edge1 = end;
            
            fragStack.push({start, end});
        }
    }
    
    Frag nfa = fragStack.top();
    fragStack.pop();
    
    return nfa;
}

// Converts the NFA to a DFA
set<int> nfaToDFA(const Frag& nfa) {
    map<int, map<char, set<int>>> nfaTransitionTable;
    int nextState = 1;
    
    stack<set<int>> dfaStack;
    set<int> startState;
    startState.insert(epsilonClosure(nfa.start));
    
    dfaStack.push(startState);
    
    map<set<int>, int> dfaStateMap;
    dfaStateMap[startState] = nextState++;
    
    while (!dfaStack.empty()) {
        set<int> currentState = dfaStack.top();
        dfaStack.pop();
        
        for (char c = 'a'; c <= 'z'; c++) {
            set<int> newState;
            
            for (int state : currentState) {
                if (nfaTransitionTable[state].count(c) > 0) {
                    const set<int>& transitionStates = nfaTransitionTable[state][c];
                    newState.insert(transitionStates.begin(), transitionStates.end());
                }
            }
            
            if (!newState.empty()) {
                if (dfaStateMap.count(newState) == 0) {
                    dfaStateMap[newState] = nextState++;
                    dfaStack.push(newState);
                }
                
                nfaTransitionTable[dfaStateMap[currentState]][c] = newState;
            }
        }
    }
    
    return dfaStateMap;
}

// Finds the epsilon closure of a state
set<int> epsilonClosure(State *state) {
    set<int> closure;
    stack<State*> stateStack;
    
    stateStack.push(state);
    
    while (!stateStack.empty()) {
        State *currentState = stateStack.top();
        stateStack.pop();
        
        closure.insert(reinterpret_cast<int>(currentState));
        
        if (currentState->label == '\0') {
            if (currentState->edge1 != nullptr && closure.count(reinterpret_cast<int>(currentState->edge1)) == 0) {
                stateStack.push(currentState->edge1);
            }
            
            if (currentState->edge2 != nullptr && closure.count(reinterpret_cast<int>(currentState->edge2)) == 0) {
                stateStack.push(currentState->edge2);
            }
        }
    }
    
    return closure;
}

int main() {
    string regex;
    cout << "Enter a regular expression: ";
    cin >> regex;
    
    Frag nfa = regexToNFA(regex);
    set<int> dfaStates = nfaToDFA(nfa);
    
    cout << "DFA States: ";
    for (int state : dfaStates) {
        cout << state << " ";
    }
    cout << endl;
    
    return 0;
}
