#include <iostream>
#include <stack>

using namespace std;

// Function to print the current state of the towers
void printTowers(const stack<int>& source, const stack<int>& aux, const stack<int>& dest) {
    cout << "Source Tower: ";
    stack<int> temp = source;
    while (!temp.empty()) {
        cout << temp.top() << " ";
        temp.pop();
    }
    cout << endl;

    cout << "Auxiliary Tower: ";
    temp = aux;
    while (!temp.empty()) {
        cout << temp.top() << " ";
        temp.pop();
    }
    cout << endl;

    cout << "Destination Tower: ";
    temp = dest;
    while (!temp.empty()) {
        cout << temp.top() << " ";
        temp.pop();
    }
    cout << endl;

    cout << "------------" << endl;
}

// Function to solve the Tower of Hanoi problem iteratively using stacks
void solveTowerOfHanoi(int numDiscs) {
    stack<int> source, aux, dest; // Stacks representing the towers

    // Initialize the source tower with discs
    for (int i = numDiscs; i >= 1; i--) {
        source.push(i);
    }

    int totalMoves = (1 << numDiscs) - 1; // Total number of moves

    // Determine the direction of movement based on the number of discs
    bool clockwise = (numDiscs % 2 == 0);

    for (int move = 1; move <= totalMoves; move++) {
        if (move % 3 == 1) {
            // Move disc between source and destination towers
            if (clockwise) {
                if (!aux.empty() && (source.empty() || aux.top() < source.top())) {
                    source.push(aux.top());
                    aux.pop();
                } else {
                    aux.push(source.top());
                    source.pop();
                }
            } else {
                if (!dest.empty() && (source.empty() || dest.top() < source.top())) {
                    source.push(dest.top());
                    dest.pop();
                } else {
                    dest.push(source.top());
                    source.pop();
                }
            }
        } else if (move % 3 == 2) {
            // Move disc between source and auxiliary towers
            if (clockwise) {
                if (!dest.empty() && (aux.empty() || dest.top() < aux.top())) {
                    aux.push(dest.top());
                    dest.pop();
                } else {
                    dest.push(aux.top());
                    aux.pop();
                }
            } else {
                if (!aux.empty() && (dest.empty() || aux.top() < dest.top())) {
                    dest.push(aux.top());
                    aux.pop();
                } else {
                    aux.push(dest.top());
                    dest.pop();
                }
            }
        } else {
            // Move disc between auxiliary and destination towers
            if (clockwise) {
                if (!source.empty() && (dest.empty() || source.top() < dest.top())) {
                    dest.push(source.top());
                    source.pop();
                } else {
                    source.push(dest.top());
                    dest.pop();
                }
            } else {
                if (!source.empty() && (aux.empty() || source.top() < aux.top())) {
                    aux.push(source.top());
                    source.pop();
                } else {
                    source.push(aux.top());
                    aux.pop();
                }
            }
        }

        // Print the current state
        cout << "Move #" << move << endl;
        printTowers(source, aux, dest);
    }
}

int main() {
    int numDiscs;

    cout << "Enter the number of discs: ";
    cin >> numDiscs;

    cout << "Tower of Hanoi solution:" << endl;
    solveTowerOfHanoi(numDiscs);

    return 0;
}
