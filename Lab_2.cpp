//============================================================================
// Name        : Lab2-2.cpp
// Author      : Jake Catlett
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Lab 2-2 Up to Speed in C++, Part 2
//============================================================================

#include <algorithm>
#include <iostream>
#include <time.h>
#include "CSVParser.hpp"

// FIXME (1): Reference the CSVParser library

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

struct Bid {
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.title << " | " << bid.amount << " | " << bid.fund << endl;
    return;
}

/**
 * Prompt user for bid information
 *
 * @return Bid struct containing the bid info
 */
Bid getBid() {
    Bid bid;

    cout << "Enter title: ";
    cin.ignore();
    getline(cin, bid.title);

    cout << "Enter fund: ";
    cin >> bid.fund;

    cout << "Enter amount: ";
    cin.ignore();
    string strAmount;
    getline(cin, strAmount);
    bid.amount = strToDouble(strAmount, '$');

    return bid;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */

vector<Bid> loadBids(string csvPath) {
	// FIXME (2): Define a vector data structure to hold a collection of bids.

	vector<Bid> tempBid;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // set the size of the vector tempBid to match the number of rows in the csv file
    tempBid.resize(file.rowCount());

	// loop to read rows of a CSV file
	for (unsigned int i = 0; i < file.rowCount(); i++) {
        // FIXME (3): create a data structure to hold data from each row and add to vector

		tempBid.at(i).title = file[i][0];
		tempBid.at(i).amount = strToDouble(file[i][4], '$');
		tempBid.at(i).fund = file[i][8];
    }
    return tempBid;
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
/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
    }

    // FIXME (4): Define a vector to hold all the bids
    vector<Bid> bidHolder;

    // FIXME (7a): Define a timer variable
    clock_t ticks;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Enter a Bid" << endl;
        cout << "  2. Load Bids" << endl;
        cout << "  3. Display All Bids" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
        	cout << "Not currently implemented." << endl;

            break;
        case 2:

        	// Iniitialize timer
            ticks = clock();

            // call the loadBids method to populate the bidHolder variable with bids
            bidHolder = loadBids(csvPath);

            // calculate the number of clock ticks that have passed
            ticks = clock() - ticks;

            cout << "time: " << ticks << " milliseconds" << endl;
            cout << "time: " << ticks*1.0/CLOCKS_PER_SEC << " seconds" << endl;

            break;
        case 3:
            // FIXME (6): Loop and display the bids read
            for (unsigned int i = 0; i < bidHolder.size(); ++i) {
            	displayBid(bidHolder.at(i));
            }
            cout << endl;

            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}
