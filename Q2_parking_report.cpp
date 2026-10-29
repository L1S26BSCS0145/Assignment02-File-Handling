/*
 * Name       : Anas Zafar
 * Reg No     : L1S26BSCS0145
 * Assignment : 02 - File Handling
 * Question   : Q2 - Parking Report
 */
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int main() {
    ifstream inFile("parking.txt");
    if (!inFile) {
        cout << "parking.txt not found!" << endl;
        return 1;
    }

    int d, m, y;
    char slash;
    inFile >> d >> slash >> m >> slash >> y;
    inFile.ignore(1000, '\n');
    inFile.ignore(1000, '\n');

    cout << "Parking report for " << d << "/" << m << "/" << y << endl;

    char plates[30][15];
    int fees[30];
    int stayMins[30];
    int count = 0;
    int cars = 0, bikes = 0, total = 0;
    int longestIdx = -1, longestMin = -1;

    char plate[15], type, colon;
    int inH, inM, outH, outM;

    while (count < 30 && inFile >> plate >> type >> inH >> colon >> inM >> outH >> colon >> outM) {
        int mins = (outH * 60 + outM) - (inH * 60 + inM);
        int hrs = (mins + 59) / 60;
        if (hrs == 0) hrs = 1;
        int fee = (type == 'C' || type == 'c') ? hrs * 100 : hrs * 40;

        strcpy(plates[count], plate);
        fees[count] = fee;
        stayMins[count] = mins;
        count++;
        total += fee;

        if (type == 'C' || type == 'c') cars++;
        else bikes++;

        if (mins > longestMin) {
            longestMin = mins;
            longestIdx = count - 1;
        }

        cout << plate << " " << ((type == 'C' || type == 'c') ? "Car" : "Bike") << " " << mins / 60 << " h " << mins % 60 << " min Fee: " << fee << endl;
    }
    inFile.close();

    if (count == 0) {
        cout << "No vehicles found!" << endl;
        ofstream out("receipts.txt");
        out << "Receipts for " << d << "/" << m << "/" << y << endl;
        out.close();
        return 0;
    }

    cout << "Vehicles: " << count << endl;
    cout << "Cars: " << cars << " Bikes: " << bikes << endl;
    cout << "Total collected: " << total << endl;
    cout << "Longest stay: " << plates[longestIdx] << " (" << stayMins[longestIdx] / 60 << " h " << stayMins[longestIdx] % 60 << " min)" << endl;

    ofstream out("receipts.txt");
    out << "Receipts for " << d << "/" << m << "/" << y << endl;
    for (int i = 0; i < count; i++) {
        out << plates[i] << " " << fees[i] << endl;
    }
    out.close();

    return 0;
}
