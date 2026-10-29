/*
 * Name       : Anas Zafar
 * Reg No     : L1S26BSCS0145
 * Assignment : 02 - File Handling
 * Question   : Q5 - Expense Tracker
 */
// FIX 1: <fstream> was missing for file handling
#include <fstream>
#include <iostream>
using namespace std;
int main() {
    ifstream inFile("expenses.txt");
// FIX 2: file check was inverted
    if (!inFile) {
        cout << "expenses.txt not found!" << endl;
        return 1;
    }
// FIX 3: need ios::app so old expenses are not deleted
    ofstream outFile("monthly_report.txt", ios::app);
    char category[20];
    int count = 0;
    double amount;
// FIX 4: total was int but amount is double
    double total = 0;
// FIX 5: skip header line of file
    inFile.ignore(100, '\n');
    while (count < 50 && inFile >> category >> amount) {
        count++;
        total = total + amount;
        if (amount > 5000) {
// FIX 6: endl missing, all high expenses in one line
            outFile << category << " " << amount << endl;
        }
    }
    inFile.close();
    outFile.close();
    cout << "Total Expenses: " << count << endl;
    cout << "Total Amount: " << total << endl;
    return 0;
}
