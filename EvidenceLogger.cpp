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
	int item, caseNum, qty;
	string title,line,word;
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
					rank = atoi(word.c_str());
					count++;
				}
				else if(count == 1){
					title = word;
					count++;
				}
				else if(count == 2){
					caseNum = atoi(word.c_str());
					count++;
				}
				else if(count == 3){
					qty = atoi(word.c_str());
					count++;
				}
			}
			tree -> addMovieNode(rank, title, caseNum, qty);
		}
	}
				
    while (true) {
        cout << "======Main Menu======" << endl; // The Menu
        cout << "1. Search for an Evidence Item" << endl;
        cout << "2. Check out an Evidence Item" << endl;
        cout << "3. Print the Evidence inventory" << endl;
        cout << "4. Delete an Evidence Item" << endl;
        cout << "5. Count the Evidence Items" << endl;
        cout << "6. Quit" << endl;
        getline(cin, user_command);

        // Takes whatever the user entered and executes the corresponding function
        switch (stoi(user_command)) {
            case 1:
            {
				cout << "Enter Item:" << endl;
				string input;
				getline(cin, input , '\n');
				tree->findMovie(input);
                break;
            }
            case 2:
            {
                cout << "Enter Item:" << endl;
				string l;
				getline(cin, l, '\n');
				tree->rentMovie(l);
                
                break;
            }
            case 3:
            {
				tree->printMovieInventory();
                break;
            }
			case 4:
			{
				cout << "Enter Item:" << endl;
				string input;
				getline(cin, input , '\n');
				tree->deleteMovieNode(input);
				break;
			}
			case 5:
			{
				tree -> countMovieNodes();
				break;
			}
            case 6:
            {
                tree -> ~MovieTree();
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
