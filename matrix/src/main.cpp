#include <iostream>
#include <matrix.h>
#include <string>
using namespace std;


int main() {
    matrix reg[10];
    string command;
    while(cin >> command) {
        if (command == "exit") {
            return 0;
        }
        try {
            if (command == "load") {
                char pref;
                int index;
                cin >> pref >> index;
                reg[index].load();
            }
            if (command == "print") {
                char pref;
                int index;
                cin >> pref >> index;
                reg[index].print();
            }
            if (command == "add") {
                char pref;
                int index1, index2;
                cin >> pref >> index1 >> pref >> index2;
                reg[index1].add(reg[index2]);
            }
            if (command == "mul") {
                char pref;
                int index1, index2;
                cin >> pref >> index1 >> pref >> index2;
                reg[index1].mul(reg[index2]);
            }
            if (command == "elem") {
                char pref;
                int index, row, col;
                cin >> pref >> index >> row >> col;
                reg[index].elem(row, col);
            }
        }
        catch (MatrixException &ex) {
            cout << ex.what() << endl;
        } catch (std::bad_alloc) {
            cout << "Unable to allocate memory. endl";
        }
    }
}

