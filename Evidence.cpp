#include <cstdlib>
#include <iostream>
#include <fstream>
#include "Evidence.h"

using namespace std;

MovieTree::MovieTree(){
    
    //////////////////
}
MovieTree::~MovieTree(){
	DeleteAll(root);
	cout << "Goodbye!" << endl;
	////DONE//////
}


void MovieTree::addMovieNode(int ranking, std::string title, int caseNum, int quantity){
	/////////////////
	MovieNode *tmp = new MovieNode;
	tmp = root;
	MovieNode *parent = new MovieNode;
	parent = NULL;

	MovieNode *node = new MovieNode(ranking, title, caseNum, quantity);
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

void MovieTree::findMovie(string title){ //and this
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
			cout << "Item Info:" << endl;
			cout << "===========" << endl;
			cout << "Ranking:" << node->ranking << endl;
			cout << "Title:" << node->title << endl;
			cout << "Case Number:" << node->year << endl;
			cout << "Quantity:" << node->quantity << endl;
			found = true;
			break;
		}
	}
	if(found == false){
		cout << "Item not found." << endl;
	}
}



void MovieTree::rentMovie(std::string title){
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
			if(node->quantity > 0){
			cout << "Item has been checked out." << endl;
			node->quantity = node->quantity-1;
			cout << "Item Info:" << endl;
			cout << "===========" << endl;
			cout << "Ranking:" << node->ranking << endl;
			cout << "Title:" << node->title << endl;
			cout << "Case Number:" << node->year << endl;
			cout << "Quantity:" << node->quantity << endl;
			found = true;
			break;
			}
			else{
			cout <<"All Items already checked out." << endl;
			}
		}
	}
	if(found == false){
		cout << "Item not found." << endl;
	}
}


void MovieTree::printMovieInventory(MovieNode *node){
	if(node->leftChild !=NULL){
		printMovieInventory(node->leftChild);
	}
	cout << "Item: " << node->title << " " << node->quantity << endl;
	if(node->rightChild != NULL){
		printMovieInventory(node->rightChild);
	}
}

void MovieTree::printMovieInventory(){
	printMovieInventory(root);
}
MovieNode* MovieTree::search(MovieNode *node,std::string title)
{
    // If the node is NULL, we just return. Failed to find node.
    if (node == NULL)
        return NULL;
    // Return this node if it is the one we are searching for
    else if (node->title == title)
        return node;

    // Else return the correct recursive call.
    else
    {
        if(title.compare(node->title) < 0)
            return search(node->leftChild,title);

        else
            return search(node->rightChild,title);
    }
}

void MovieTree::deleteMovieNode(std::string title){
    // Create the object for this operation
    MovieNode * node = search(root,title);
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
            MovieNode * replacementNode = node->rightChild;

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


int MovieTree::countMovieNodes(MovieNode *node){
    if (node == NULL){
        return 0;
	}
    return countMovieNodes(node->leftChild) + countMovieNodes(node->rightChild) + 1;

}

int MovieTree::countMovieNodes(){
	int count = countMovieNodes(root);
	cout<<"Log contains: "<<count<<" items."<<endl;
	return count;
}

void MovieTree::DeleteAll(MovieNode * node)
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

