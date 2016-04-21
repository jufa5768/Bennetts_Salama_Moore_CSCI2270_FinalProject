#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


#include "Evidence.cpp"

using namespace std;

int main(int argc, char* argv[]) {
	
	EvidenceTree *tree = new EvidenceTree();
	
	//int type, year, qty;
	int caseNum, shelfNumber, quantity;
	string itemName,line,word, renterName;
	int count = 0;
	
	ifstream infile;
	string user_command;
	infile.open(argv[1]);
	
	if(infile.good()){
		while(getline(infile,line,'\n')){
			istringstream ss(line);
			count = 0;
			while(getline(ss,word,',')){
				if(count == 0){
					caseNum = atoi(word.c_str());
					count++;
				}
				else if(count == 1){
					itemName = word;
					count++;
				}
				else if(count == 2){
					shelfNumber = atoi(word.c_str());
					count++;
				}
				else if(count == 3){
					quantity = atoi(word.c_str());
					count++;
				}
			}
			tree -> addEvidenceNode(caseNum, itemName, shelfNumber, quantity);
		}
	}
				
    while (true) {
        cout << "======Main Menu======" << endl; // The Menu
        cout << "1. Search for an evidence item" << endl;
        cout << "2. Check out an evidence item" << endl;
        cout << "3. Print the evidence inventory" << endl;
        cout << "4. Delete an evidence item" << endl;
        cout << "5. Count the evidence items" << endl;
        cout << "6. Return evidence item" << endl;
        cout << "7. Quit" << endl;
        getline(cin, user_command);

        // Takes whatever the user entered and executes the corresponding function
        switch (stoi(user_command)) {
            case 1:
            {
				cout << "Enter case number:" << endl;
				string input;
				getline(cin, input , '\n');
				tree->findEvidence(atoi(input.c_str());
                break;
            }
            case 2:
            {
                cout << "Enter case number:" << endl;
				string l;
                getline(cin, l, '\n');
                cout << "Enter renter name:" << endl;
                string 2;
                getline(cin, 2, '\n');
				tree->rentEvidence(atoi(1.c_str()), 2);
                
                break;
            }
            case 3:
            {
				tree->printEvidenceInventory();
                break;
            }
			case 4:
			{
				cout << "Enter case number:" << endl;
				string input;
				getline(cin, input , '\n');
				tree->deleteEvidenceNode(atoi(input.c_str());
				break;
			}
			case 5:
			{
				tree -> countEvidenceNodes();
				break;
			}
            case 6:
            {
                cout << "Enter case number:" << endl;
                string input;
                getline(cin, input , '\n');
                tree->returnEvidence(atoi(input.c_str()));
            }
            case 7:
            {
                tree -> ~EvidenceNode();
                return 0; // Finished
            }
            default:
            {
                cout << "Pick a value from the above list" << endl;
                //if another number is inputed that's not in the menu options
            }

        }

    }
    return 0;
}
