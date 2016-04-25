#include <iostream>
#include <string>
#include "Evidence.h"

void printMenu();

using namespace std;

int main(int argc, char* argv[]) {
	
	Evidence tree;
	tree.buildEvidenceLog(argv[1]);
	int answer(0);
    string caseNumber = "";
	bool repeat = false;  //when the quit option is chosen, "repeat" is changed to true to exit the whilke loop
	string renterName;
				
    while (!repeat) {
        printMenu();
        cin >> answer;

        switch (answer) {
            case 1: 
				cout << "Enter case number:" << endl;
				cin >> caseNumber;
				tree.findEvidence(caseNumber);
                break;
            case 2:
                cout << "Enter case number:" << endl;
                cin >> caseNumber;
				tree.rentEvidence(caseNumber);
                break;
            case 3:
				tree.printEvidenceInventory();
                break;
			case 4:
				cout << "Enter case number:" << endl;
				cin >> caseNumber;
				//tree.deleteEvidenceNode(caseNumber);
				break;
			case 5:
				cout << "There are " << tree.countEvidenceNodes() << "available cases." << endl;
				break;
            case 6:
                cout << "Enter case number:" << endl;
                cin >> caseNumber;
                //tree.returnEvidence(caseNumber);
                break;
            case 7:
                cout << "Goodbye!" << endl;
                repeat = true;
            default:
                if(!repeat)
                    cout << "Pick choose an option from the list" << endl;
                break;
            }
        }

    return 0;
}

void printMenu() {
	cout << "======Main Menu======" << endl; // The Menu
	cout << "1. Search for evidence by case number" << endl; 
	cout << "2. Check out evidence for a case" << endl; //
	cout << "3. Print evidence inventory" << endl; //prints all the cases and their evidence items
	cout << "4. Delete a case" << endl; //if the case has been solved, the evidence is destroyed
	cout << "5. Count the number of open cases" << endl;
	cout << "6. Return evidence item" << endl;
	cout << "7. Quit" << endl;
}

