
#include <iostream>
#include <vector>
#include <map>
#include <fstream>

using namespace std;

class FiniteAutomaton {
public:
    FiniteAutomaton(int alphabet, int numStates, int startState, std::vector<int> acceptingStates) {
        numStates_ = numStates;
        alphabet_ = alphabet;
        startState_ = startState;
        acceptingStates_ = acceptingStates;
        transitions_.resize(numStates_);

    }

    void AddTransition(int fromState, char symbol, int toState) {
        transitions_[toState][symbol].push_back(fromState);
    }
   /* void AddReverseTransition(int fromState, char symbol, int toState) {
        int temp = fromState;
        fromState = toState;
        toState = temp;
        transitions_[fromState][symbol] = toState;
    }*/


    bool IsAcceptingState(int state) const {
        return count(acceptingStates_.begin(), acceptingStates_.end(), state) > 0;
    }

    int GetStartState() const {
        return startState_;
    }

    
    bool SearchMatchesDFS(int currentState, const std::string& w0, int &w0Index) {
        if (w0Index >= w0.size())
            return true;  // Були вичерпані всі символи w0, знайдено співпадіння
        
        
        for (int nextState : transitions_[currentState][w0[w0Index]]) {
            w0Index++;
            if(SearchMatchesDFS(nextState, w0, w0Index)) return true;
            w0Index--;
        }

        return false;  // Невідомий перехід, співпадіння не знайдено

    }

private:
    int numStates_;
    int alphabet_;
    int startState_;
    std::vector<int> acceptingStates_;
    std::vector<map<char, vector<int> > > transitions_;//откуда(2 число)<символ,куда идем(1 число)>

};

int main() {
    string fName = "automaton.txt";
    ifstream file(fName);
    if (!file.is_open())
    {
        cout << "cannot open file" << endl;
        return 1;
    }
    int alphabet, numberOfStates, startState;
    std::vector<int> acceptingStates;
    file >> alphabet >> numberOfStates >> startState;

    int n, a, b;
    file >> n;
    for (int i = 0; i < n; i++)
    {
        file >> a;
        acceptingStates.push_back(a);
    }

    FiniteAutomaton automaton = FiniteAutomaton(alphabet, numberOfStates, startState, acceptingStates);

    char c;
    while (!file.eof())
    {
        file >> a >> c >> b;
        automaton.AddTransition(a, c, b);
    }

    file.close();

    //std::vector<char> alphabet = { 'a', 'b' };
    //std::vector<int> acceptingStates = { 2 }; // Приймаючі стани
    //FiniteAutomaton automaton(4, alphabet, 0, acceptingStates);

    //// Додати функції переходу
    //automaton.AddTransition(0, 'a', 1);
    //automaton.AddTransition(1, 'a', 2);
    //automaton.AddTransition(2, 'b', 1);
    //automaton.AddTransition(1, 'b', 3);
    //automaton.AddTransition(3, 'a', 1);

    // Перевірка чи стани є приймаючими
    for (int state = 0; state < 3; ++state) {
        std::cout << "State " << state << " is accepting: " << automaton.IsAcceptingState(state) << std::endl;
    }

    std::cout << "Enter word w0 to check " << std::endl;

    std::string w0 = "baaa";
    cin >> w0;
    
    std::string revw = "";
    for (int i = w0.length() - 1; i >= 0; i--)
    {
        revw += w0[i];
    }
    // Отримати початковий стан

    bool matchesW0 = false;
    int w0ind = 0;
    for (int i = 0; i < acceptingStates.size(); i++) {
        matchesW0 = automaton.SearchMatchesDFS(acceptingStates[i], revw, w0ind = 0);
        if (matchesW0) {
            break;
        }
    }
    

    if (matchesW0) {
        std::cout << "Yes" << std::endl;
    }
    else {
        std::cout << "No" << std::endl;
    }

    return 0;
}
