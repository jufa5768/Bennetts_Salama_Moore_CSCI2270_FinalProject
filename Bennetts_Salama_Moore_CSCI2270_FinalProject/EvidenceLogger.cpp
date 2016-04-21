#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


#include "Evidence.cpp"

using namespace std;

int main(int argc, char* argv[]) {
	
	EvidenceTree tree;
	tree.buildEvidenceLog(argv[1]);
	int answer = 0;
	bool repeat = false;
	string input, renterName;
				
    while (true) {
        printMenu();
        cin >> answer;

        // Takes whatever the user entered and executes the corresponding function
        switch (answer) {
            case 1: 
				cout << "Enter case number:" << endl;
				getline(cin, input , '\n');
				tree.findEvidence(atoi(input.c_str());
                break;
            case 2:
                cout << "Enter case number:" << endl;
                getline(cin, input, '\n');
                cout << "Enter renter name:" << endl;
                getline(cin, renterName, '\n');
				tree.rentEvidence(atoi(1.c_str()), 2);
                break;
            case 3:
				tree.printEvidenceInventory();
                break;
			case 4:
				cout << "Enter case number:" << endl;
				string input;
				getline(cin, input , '\n');
				tree.deleteEvidenceNode(atoi(input.c_str());
				break;
			case 5:
				cout << "There are " << tree.countEvidenceNodes() << " cases." << endl;
				break;
            case 6:
                cout << "Enter case number:" << endl;
                string input;
                getline(cin, input , '\n');
                tree.returnEvidence(atoi(input.c_str()));
                break;
            case 7:
                cout << "Goodbye!" << endl;
                repeat = true;
            }
            default:
                cout << "Pick a value from the above list" << endl;
        }

    }
    return 0;
}

void printMenu() {
	cout << "======Main Menu======" << endl; // The Menu
	cout << "1. Search for an evidence item" << endl;
	cout << "2. Check out an evidence item" << endl;
	cout << "3. Print the evidence inventory" << endl;
	cout << "4. Delete an evidence item" << endl;
	cout << "5. Count the evidence items" << endl;
	cout << "6. Return evidence item" << endl;
	cout << "7. Quit" << endl;
}