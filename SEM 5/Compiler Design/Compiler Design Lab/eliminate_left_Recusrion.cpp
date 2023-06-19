#include <iostream>
#include <string>

using namespace std;

int main() {
  int num;
  cout << "Enter Number of Production : ";
  cin >> num;

  string productions[num];
  for (int i = 0; i < num; i++) {
    cout << "Enter the grammar as S->S-A :\n";
    cin >> productions[i];
  }

  for (int i = 0; i < num; i++) {
    cout << "\nGRAMMAR : : : " << productions[i] << endl;
    char non_terminal = productions[i][0];
    int index = 3;

    if (non_terminal == productions[i][index]) {
      cout << " is left recursive.\n";
      while (productions[i][index] != 0 && productions[i][index] != '|') {
        index++;
      }

      if (productions[i][index] != 0) {
        char beta = productions[i][index + 1];
        cout << "Grammar without left recursion:\n";
        cout << non_terminal << "->" << beta << non_terminal;
        cout << "\n" << non_terminal << "'" << "->" << non_terminal << beta << non_terminal;
        cout << "|" << "E\n";
      } else {
        cout << " can't be reduced\n";
      }
    } else {
      cout << " is not left recursive.\n";
    }
  }

  return 0;
}