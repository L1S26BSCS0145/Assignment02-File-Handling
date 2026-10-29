/*
 * Name       : Anas Zafar
 * Reg No     : L1S26BSCS0145
 * Assignment : 02 - File Handling
 * Question   : Q5 - Expense Tracker
 */

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int main() {
    int choice;
    char category[20];
    char catRead[20];
    int amount;
    int amounts[100];
    char categories[100][20];

    do {
        cout << "===== Expense Tracker =====" << endl;
        cout << "1. Add an expense" << endl;
        cout << "2. Show all expenses" << endl;
        cout << "3. Show total of a category" << endl;
        cout << "4. Clear all expenses" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter category: ";
            cin >> category;
            cout << "Enter amount: ";
            cin >> amount;
            if (amount <= 0) {
                cout << "Invalid amount!" << endl;
            } else {
                ofstream outFile("expenses.txt", ios::app);
                outFile << category << " " << amount << endl;
                outFile.close();
                cout << "Expense saved." << endl;
            }
        }
        else if (choice == 2) {
            ifstream inFile("expenses.txt");
            if (!inFile) {
                cout << "No expenses yet." << endl;
            } else {
                int count = 0;
                int total = 0;
                int largestAmt = -1;
                char largestCat[20] = "";
                
                while (count < 100 && inFile >> categories[count] >> amounts[count]) {
                    total += amounts[count];
                    if (amounts[count] > largestAmt) {
                        largestAmt = amounts[count];
                        strcpy(largestCat, categories[count]);
                    }
                    count++;
                }
                inFile.close();
                
                if (count == 0) {
                    cout << "No expenses yet." << endl;
                } else {
                    for (int i = 0; i < count; i++) {
                        cout << i+1 << ". " << categories[i] << " " << amounts[i] << endl;
                    }
                    cout << "Total spent: " << total << endl;
                    cout << "Largest expense: " << largestCat << " (" << largestAmt << ")" << endl;
                }
            }
        }
        else if (choice == 3) {
            cout << "Enter category: ";
            cin >> category;
            ifstream inFile("expenses.txt");
            if (!inFile) {
                cout << "No expenses found for " << category << endl;
            } else {
                int count = 0;
                int total = 0;
                while (inFile >> catRead >> amount) {
                    if (strcmp(catRead, category) == 0) {
                        count++;
                        total += amount;
                    }
                }
                inFile.close();
                if (count == 0) {
                    cout << "No expenses found for " << category << endl;
                } else {
                    cout << "Expenses in " << category << ": " << count << endl;
                    cout << "Total for " << category << ": " << total << endl;
                }
            }
        }
        else if (choice == 4) {
            ofstream outFile("expenses.txt");
            outFile.close();
            cout << "All expenses cleared." << endl;
        }
        else if (choice == 5) {
            cout << "Goodbye!" << endl;
        }
        else {
            cout << "Invalid choice!" << endl;
        }

    } while (choice != 5);

    return 0;
}