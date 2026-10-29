/*Name : Anas Zafar
Reg No :L1S26BSCS0145
Assignment : 02 - File Handling
*/Question : Q1

// FIX 1: <fstream> was missing
#include <fstream>
#include <iostream>
using namespace std;
int main() {
    ifstream inFile("stock.txt");
// FIX 2: check was wrong
    if (!inFile) {
        cout << "stock.txt not found!" << endl;
        return 1;
    }
// FIX 3: need ios::app to keep old data
    ofstream reorder("reorder.txt", ios::app);
    char code[10];
    int qty, count = 0, low = 0;
    double price;
// FIX 4: total must be double
    double total = 0;
// FIX 5: skip header line
    inFile.ignore(100, '\n');
    while (count < 50 && inFile >> code >> qty >> price) {
        count++;
        total = total + qty * price;
        if (qty < 10) {
// FIX 6: endl missing
            reorder << code << " " << qty << endl;
            low++;
        }
    }
    inFile.close();
    reorder.close();
    cout << "Items: " << count << endl;
    cout << "Total stock value: " << total << endl;
    cout << "Low stock items: " << low << endl;
    return 0;
}
