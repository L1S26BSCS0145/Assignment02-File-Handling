/*
 * Name       : Anas Zafar
 * Reg No     : L1S26BSCS0145
 * Assignment : 02 - File Handling
 * Question   : Q3 - Scholarship List
 */
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int main() {
    char path[100];
    cout << "Enter the file name: ";
    cin.getline(path, 100);

    ifstream inFile(path);
    if (!inFile.is_open()) {
        cout << "Could not open " << path << "!" << endl;
        return 1;
    }

    int n;
    inFile >> n;
    if (n > 30) {
        cout << "Too many students!" << endl;
        inFile.close();
        return 0;
    }
    inFile.ignore(100, '\n');

    char names[30][30];
    double cgpas[30];
    int count = 0;
    double total = 0;
    int eligible = 0;
    double highest = -1;
    char topName[30] = "";
    int topIdx = -1;

    char tempName[30];
    double tempCgpa;

    for (int i = 0; i < n; i++) {
        if (!inFile.getline(tempName, 30, ',')) break;
        if (!(inFile >> tempCgpa)) break;
        inFile.ignore(100, '\n');

        strcpy(names[count], tempName);
        cgpas[count] = tempCgpa;
        cout << "[" << names[count] << "] CGPA: " << cgpas[count] << endl;

        total += cgpas[count];
        if (cgpas[count] >= 3.5) eligible++;
        if (cgpas[count] > highest) {
            highest = cgpas[count];
            strcpy(topName, tempName);
            topIdx = count;
        }
        count++;
    }

    if (count < n) {
        cout << "Warning: only " << count << " of " << n << " records found." << endl;
    }

    if (count == 0) {
        cout << "No students found!" << endl;
        ofstream out("scholarship.txt");
        out.close();
        inFile.close();
        return 0;
    }

    ofstream outFile("scholarship.txt");
    for (int i = 0; i < count; i++) {
        if (cgpas[i] >= 3.5) {
            outFile << names[i] << "," << cgpas[i] << endl;
        }
    }
    outFile.close();

    cout << "Students: " << count << endl;
    cout << "Average CGPA: " << total / count << endl;
    cout << "Eligible for scholarship: " << eligible << endl;
    cout << "Top student: " << topName << " (" << highest << ")" << endl;

    inFile.close();
    return 0;
}
