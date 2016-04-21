#include <cstdlib>
#include <iostream>
#include <fstream>
#include "Evidence.h"

using namespace std;

MovieTree::MovieTree(){
    //ctor
    //////////////////
}
MovieTree::~MovieTree(){
	DeleteAll(root);
	cout << "Goodbye!" << endl;
	////DONE//////
}

void Evidence::buildEvidenceLog(char * filename) {
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
    infile.close();
}

void Evidence::addEvidenceeNode(int ranking, std::string title, int caseNum, int quantity){
	/////////////////
	EvidenceNode *tmp = new EvidenceNode;
	tmp = root;
	EvidenceNode *parent = new EvidenceNode;
	parent = NULL;

	EvidenceNode *node = new EvidenceNode(ranking, title, caseNum, quantity);
	node->leftChild = NULL;
	node->rightChild = NULL;
	node->parent = NULL;

	while(tmp!=NULL){
		parent = tmp;
		if(node->title.compare(tmp->title) < 0){
			tmp = tmp->leftChild;
		}
		else if(node->title.compare(tmp->title) > 0){
			tmp = tmp->rightChild;
		}
	
	}
	if(parent == NULL){
		root = node;
	}
	else if(node->title.compare(parent->title) < 0){
		parent->leftChild = node;
		node->parent = parent;
	}
	else{
		parent->rightChild = node;
		node->parent = parent;
	}
	
}

void Evidence::rentEvidence(int caseNum, string in_renterName)
{
    Evidence *node = findEvidence(caseNum);
    node->renterName = in_renterName;
}


void Evidence::printEvidenceInventory(EvidenceNode *node){
	if(node->leftChild !=NULL){
		printMovieInventory(node->leftChild);
	}
	cout << "Item: " << node->title << " " << node->quantity << endl;
	if(node->rightChild != NULL){
		printMovieInventory(node->rightChild);
	}
}

void Evidence::printEvidenceInventory(){
	printMovieInventory(root);
}

void Evidence::findEvidence(int caseNum){ //and this
    EvidenceNode *node = findEvidence(caseNum);
    if(node !=NULL)
    {
        cout << "Item Info:" << endl;
        cout << "===========" << endl;
        cout << "Ranking:" << node->ranking << endl;
        cout << "Title:" << node->title << endl;
        cout << "Case Number:" << node->year << endl;
        cout << "Quantity:" << node->quantity << endl;
    }
    else 
    {
        cout << "Evidence not found." << endl;
    }
    return;
}

EvidenceNode *Evidence::findEvidence(int caseNum)
{
    bool found = false;
	MovieNode *node = new MovieNode;
	node = root;
	while(node !=NULL){
		if(title.compare(node->title) < 0){
			node = node->leftChild;
		}
		else if(title.compare(node->title) > 0){
			node = node->rightChild;
		}
		else{
			found = true;
			return node;
		}
	}
	if(found == false){
		cout << "Item not found." << endl;
	}
}

void Evidence::deleteEvidenceNode(std::string title){
    // Create the object for this operation
    EvidenceNode * node = search(root,title);
    // If the movie exists
    if (node != NULL)
    {
        // If it has no children
        if (node->leftChild == NULL && node->rightChild == NULL)
        {
            // If this node is the left child, set the parents left child to NULL
            if (node->parent->leftChild == node){
                node->parent->leftChild = NULL;
			}
            // Else, this node is the right child, set that to NULL
            else
                node->parent->rightChild = NULL;
            // Delete the node
            delete node;

        }
        // If it only has a left child
        else if (node->rightChild == NULL)
        {
            if (node->parent->leftChild == node)
                node->parent->leftChild = node->leftChild;
            else
                 node->parent->rightChild = node->leftChild;

            delete node;

        }
        // If it only has a right child
        else if (node->leftChild == NULL)
        {
            if (node->parent->leftChild == node)
                node->parent->leftChild = node->rightChild;
            else
                 node->parent->rightChild = node->rightChild;

            delete node;
        }

        // Node has two children, we need the smallest node from the right child
        else
        {
            // Start on the right sub-tree
            EvidenceNode * replacementNode = node->rightChild;

            // search for the smallest left child
            while (replacementNode->leftChild != NULL)
            {
                replacementNode = replacementNode->leftChild;
            }

            // Swap in all the info from the replacement to this node we are "deleting"
            node->title = replacementNode->title;
            node->quantity = replacementNode->quantity;
            node->ranking = replacementNode->ranking;
            node->caseNum = replacementNode->year;


            // If the replacement node has a right child, update the parent
            if (replacementNode->rightChild != NULL)
                replacementNode->rightChild->parent = replacementNode->parent;

            // If the replacement node is a left child
            if (replacementNode->parent->leftChild == replacementNode)
                replacementNode->parent->leftChild = replacementNode->rightChild;
            // If it is a right child
            else
                replacementNode->parent->rightChild = replacementNode->rightChild;

            // Delete the node
            delete replacementNode;
        }
    }
    // If it doesn't exist
    else{
        cout << "Item not found." << endl;
	}


}


int Evidence::countEvidenceNodes(EvidenceNode *node){
    if (node == NULL){
        return 0;
	}
    return countEvidenceNodes(node->leftChild) + countEvidenceNodes(node->rightChild) + 1;

}

int Evidence::countEvidenceNodes(){
	int count = countEvidenceNodes(root);
	cout<<"Log contains: "<<count<<" items."<<endl;
	return count;
}

void Evidence::DeleteAll(EvidenceNode * node)
{
    // clean to the left
    if (node->leftChild != NULL)
        DeleteAll(node->leftChild);
    // clean to the right
    if (node->rightChild != NULL)
        DeleteAll(node->rightChild);
    // delete this node
    cout<<"Deleting: "<<node->title<<endl;
    delete node;

    return;
}
