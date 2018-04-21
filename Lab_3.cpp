//============================================================================
// Name        : LinkedList.cpp
// Author      : Jake Catlett
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Lab 3-3 Lists and Searching
//============================================================================

#include <algorithm>
#include <iostream>
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

// define a structure to store bids in nodes
struct Node {
	Bid bid;
	Node* nextNodePtr;
};

//============================================================================
// Linked-List class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a linked-list.
 */
class LinkedList {

public:
    LinkedList();
    virtual ~LinkedList();
    void Append(Bid bid);
    void Prepend(Bid bid);
    void PrintList();
    void Remove(string bidId);
    Bid Search(string bidId);
    int Size();

private:
    // create a pointer variable which identifies the head node in the linked list

	Node* headPtr;

};

/**
 * Default constructor
 */
LinkedList::LinkedList() {
    // initialize the head pointer variable

	headPtr = NULL;
}

/**
 * Destructor
 */
LinkedList::~LinkedList() {
}

/**
 * Append a new bid to the end of the list
 */
void LinkedList::Append(Bid bid) {
    // logic to traverse the linked list to the last node and append a bid
	if (headPtr==NULL) {
		headPtr = new Node;
		headPtr->bid = bid;
		headPtr->nextNodePtr = NULL;
	}
	else {
		Node* tempPtr = headPtr;
		Node* prevPtr;
		while (tempPtr != NULL) {
			prevPtr = tempPtr;
			tempPtr = tempPtr->nextNodePtr;
			}
		prevPtr->nextNodePtr = new Node;
		prevPtr->nextNodePtr->bid = bid;
		prevPtr->nextNodePtr->nextNodePtr = NULL;
	}
}

/**
 * Prepend a new bid to the start of the list
 */
void LinkedList::Prepend(Bid bid) {
    // logic to either add a bid to an empty list or prepend it to the first node in the list
	if (headPtr==NULL) {
			headPtr = new Node;
			headPtr->bid = bid;
			headPtr->nextNodePtr = NULL;
		}
	else {
		Node* tempPtr = headPtr;
		headPtr = new Node;
		headPtr->bid = bid;
		headPtr->nextNodePtr = tempPtr;
	}
}

/**
 * Simple output of all bids in the list
 */
void LinkedList::PrintList() {
    // code below prints all nodes in the linked list
	if (headPtr == NULL) {
		cout << "There are no items to print" << endl;
	}
	else {
		Node* tempPtr = headPtr;
		while (tempPtr != NULL) {
			cout << tempPtr->bid.bidId << ": " << tempPtr->bid.title << " | "
					<< tempPtr->bid.amount << " | " << tempPtr->bid.fund << endl;
			tempPtr = tempPtr->nextNodePtr;
		}
	}
}

/**
 * Remove a specified bid
 *
 * @param bidId The bid id to remove from the list
 */
void LinkedList::Remove(string bidId) {
    // search for a given node by ID and remove the node if discovered
	Node* tempPtr = headPtr;
	if (tempPtr == NULL) {
		cout << "There are no nodes in this list.  Attempt aborted." << endl;
	}
	while (tempPtr != NULL) {
		if (tempPtr->bid.bidId == bidId) {
			if (tempPtr == headPtr) {
				headPtr = headPtr->nextNodePtr;
				tempPtr = NULL;
				cout << "Record has been found and deleted" << endl;
				break;
			}
		}
		else {
			Node* prevPtr = tempPtr;
			tempPtr = tempPtr->nextNodePtr;
			if (tempPtr->bid.bidId == bidId) {
				prevPtr->nextNodePtr = tempPtr->nextNodePtr;
				tempPtr = NULL;
				cout << "Record has been found and deleted" << endl;
				break;
			}
			if (tempPtr->bid.bidId != bidId && tempPtr->nextNodePtr == NULL) {
				cout << "No record with that ID number exists" << endl;
				break;
			}
		}
	}
}
/**
 * Search for the specified bidId
 *
 * @param bidId The bid id to search for
 */
Bid LinkedList::Search(string bidId) {
    // code searches for a node by supplied ID number and returns contents if found
	Node* tempPtr = headPtr;
	Bid returnBid;
	if (tempPtr == NULL) {
			cout << "There are no nodes in this list.  Search aborted." << endl;
			return returnBid;
		}
	else {
		while (tempPtr != NULL){
			if (tempPtr->bid.bidId == bidId) {
				returnBid = tempPtr->bid;
				break;
			}
			tempPtr = tempPtr->nextNodePtr;
		}
	}
	return returnBid;
}

/**
 * Returns the current size (number of elements) in the list
 */
int LinkedList::Size() {
    return 0;
}

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount
         << " | " << bid.fund << endl;
    return;
}

/**
 * Prompt user for bid information
 *
 * @return Bid struct containing the bid info
 */
Bid getBid() {
    Bid bid;

    cout << "Enter Id: ";
    cin.ignore();
    getline(cin, bid.bidId);

    cout << "Enter title: ";
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
 * Load a CSV file containing bids into a LinkedList
 *
 * @return a LinkedList containing all the bids read
 */
void loadBids(string csvPath, LinkedList *list) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser
    csv::Parser file = csv::Parser(csvPath);

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // initialize a bid using data from current row (i)
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << bid.bidId << ": " << bid.title << " | " << bid.fund << " | " << bid.amount << endl;

            // add this bid to the end
            list->Append(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
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
 *
 * @param arg[1] path to CSV file to load from (optional)
 * @param arg[2] the bid Id to use when searching the list (optional)
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "98109";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
        bidKey = "98109";
    }

    clock_t ticks;

    LinkedList bidList;

    Bid bid;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Enter a Bid" << endl;
        cout << "  2. Load Bids" << endl;
        cout << "  3. Display All Bids" << endl;
        cout << "  4. Find Bid" << endl;
        cout << "  5. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            bid = getBid();
            bidList.Append(bid);
            displayBid(bid);

            break;

        case 2:
            ticks = clock();

            loadBids(csvPath, &bidList);

            cout << bidList.Size() << " bids read" << endl;

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " milliseconds" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 3:
            bidList.PrintList();

            break;

        case 4:{
        	string bidKey;
        	cout << "Please enter a bid ID number: " << endl;
        	cin >> bidKey;

            ticks = clock();

            bid = bidList.Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            } else {
            	cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;
        }
        case 5:
        	cout << "Please enter a bid ID number:";
        	cin >> bidKey;
            bidList.Remove(bidKey);

            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}
