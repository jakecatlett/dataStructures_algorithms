//============================================================================
// Name        : Lab1-3.cpp
// Author      : Jake Catlett
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Lab 1-3 Up to Speed in C++
//============================================================================

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// (1): Data structure bidData created to hold bid information as a single unit of storage.
struct bidData {
	string title;
	string fund;
	string vehicle;
	int bidAmt;
};

// FIXME (4): Display the bid values passed in data structure
/**
 * Display the bid information
 *
 * @param ?type? data structure containing the bid info
 */
void displayBid(bidData newBid) {
    cout << "Title: " << newBid.title << endl;
    cout << "Fund: " << newBid.fund << endl;
    cout << "Vehicle: " << newBid.vehicle << endl;
    cout << "Bid Amount: " << newBid.bidAmt << endl;

    return;
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */

double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

// FIXME (3): Store input values in data structure
/**
 * Prompt user for bid information
 *
 * @return data structure containing the bid info
 */
bidData getBid() {

    bidData tempData;

    cout << "Enter title: ";
    cin.ignore();
    getline(cin, tempData.title);

    cout << "Enter fund: ";
    cin >> tempData.fund;

    cout << "Enter vehicle: ";
    cin.ignore();
    getline(cin, tempData.vehicle);

    cout << "Enter amount: ";
    cin.ignore();
    string strAmount;
    getline(cin, strAmount);
    tempData.bidAmt = strToDouble(strAmount, '$');

    return tempData;
}

/**
 * The one and only main() method
 */
int main() {

    // FIXME (2): Declare instance of data structure to hold bid information
	bidData newBid;

    // loop to display menu until exit chosen
    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Enter Bid" << endl;
        cout << "  2. Display Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        // FIXME (5): Complete the method calls then test the program
        switch (choice) {
            case 1:
            	newBid = getBid();
                break;
            case 2:
                displayBid(newBid);
                break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}
