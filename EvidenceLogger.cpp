#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "MovieTree.cpp"

using namespace std;

int main(int argc, char* argv[]) {
	
	MovieTree *tree = new MovieTree();
	int rank, year, qty;
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
					year = atoi(word.c_str());
					count++;
				}
				else if(count == 3){
					qty = atoi(word.c_str());
					count++;
				}
			}
			tree -> addMovieNode(rank, title, year, qty);
		}
	}
				
    while (true) {
        cout << "======Main Menu======" << endl; // The Menu
        cout << "1. Find a movie" << endl;
        cout << "2. Rent a movie" << endl;
        cout << "3. Print the inventory" << endl;
        cout << "4. Delete a movie" << endl;
        cout << "5. Count the movies" << endl;
        cout << "6. Quit" << endl;
        getline(cin, user_command);

        // Takes whatever the user entered and executes the corresponding function
        switch (stoi(user_command)) {
            case 1:
            {
				cout << "Enter title:" << endl;
				string input;
				getline(cin, input , '\n');
				tree->findMovie(input);
                break;
            }
            case 2:
            {
                cout << "Enter title:" << endl;
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
				cout << "Enter title:" << endl;
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

