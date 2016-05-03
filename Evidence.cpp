#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "Evidence.h"

using namespace std;

Evidence::Evidence(){
    root = NULL;
}

Evidence::~Evidence(){
    if(root != NULL) 
        DeleteAll(root);
}

void Evidence::buildEvidenceLog(char *filename) {
    string line, caseNumber, shelfNumber, suspects, renter, evidence;
    ifstream fileIn;
    fileIn.open(filename);
    if(fileIn.is_open()) {
        while(!fileIn.eof()) {
            getline(fileIn, line);
            stringstream ss(line);
            getline(ss, caseNumber, ',');
            getline(ss, shelfNumber, ',');
            getline(ss, suspects, ',');
            getline(ss, renter);
            renter.erase(renter.end()-1);
            addEvidenceNode(caseNumber, atoi(shelfNumber.c_str()), atoi(suspects.c_str()), renter);
            getline(fileIn, line);
            ss.clear();
            ss.str(line);
            while(getline(ss, evidence, ',')) {
                initializeEvidence(evidence, caseNumber);
            }
        }
    }
    else {
        cout << "File error." << endl;
    }
    fileIn.close();
}

void Evidence::addEvidenceNode(string caseNumber, int shelfNumber, int suspects, string renterName) {
    EvidenceNode *newNode = new EvidenceNode(caseNumber, shelfNumber, suspects, renterName);
    EvidenceNode *current = root;
    //test to see if they are initialized to NULL

    if(root == NULL) {
        root = newNode;
    }

    else {
        while(current != NULL) {
            if(current->caseNum > caseNumber) {
                if(current->leftChild == NULL) {
                    current->leftChild = newNode;
                    newNode->parent = current;
                    return;
                }
                else
                    current = current->leftChild;
            }
            else {
                if(current->rightChild == NULL) {
                    current->rightChild = newNode;
                    newNode->parent = current;
                    return;
                }
                else
                    current = current->rightChild;
            }
        }
    }
}

void Evidence::initializeEvidence(string item, string caseNumber) {
    EvidenceNode * found = search(root, caseNumber);
    if(found == NULL) {
        cout << "Case not found." << endl;
    }
    else {
        found->evidenceList.push_back(item);
    }
}

void Evidence::findEvidence(string caseNumber) {
    char answer;
    EvidenceNode * found = search(root, caseNumber);
    printSpecificCase(found);
    if(found != NULL && found->renterName == "NONE") {
        do {
            cout << "Do you wish to rent the evidence for this case? (Y/N)" << endl;
            cin >> answer;
            if(answer == 'y' || answer == 'Y') {
                rentEvidence(caseNumber);
                return;
            }
            else if(answer == 'n' || answer == 'N')
                return;
        } while(answer != 'y' || answer != 'Y' || answer != 'n' || answer != 'N');
    }
}

void Evidence::rentEvidence(string caseNumber) {
    EvidenceNode * node = search(root, caseNumber);
    if(node->renterName != "NONE") {
        cout << "The evidence for this case is currently being used by " << node->renterName << "." << endl;
    }
    else {
        string name;
        cout << "Please enter your first and last name: " << endl;
        cin.ignore();
        getline(cin, name);
        node->renterName = name;
        cout << "You have just rented the evidence for case number: " << node->caseNum << endl;
        cout << "Included are the following items:" << endl;
        for(int i=0; i<node->evidenceList.size(); i++) {
            cout << setw(3) << "-" << node->evidenceList[i] << endl;
        }
        cout << endl << "You have one week to these items. If you wish to use them for a longer period of time, please talk to the case manager.\n" << endl;
    }
}

void Evidence::returnEvidence(string caseNumber) {
    EvidenceNode * found = search(root, caseNumber);
    cout << "You are returning evidence for case number " << caseNumber << "." << endl;
    cout << "The evidence for this case includes:" << endl;
    for(int i=0; i<found->evidenceList.size(); i++) {
        cout << setw(3) << "-" << found->evidenceList[i] << endl;
    }
    cout << "Please return it to storage." << endl;
    found->renterName = "NONE";
}

void Evidence::countEvidenceNodes(EvidenceNode *node, int &c) {
    if(node != NULL) {
        if(node->leftChild != NULL)
            countEvidenceNodes(node->leftChild, c);
        if(node->renterName == "NONE")
            c++;
        if(node->rightChild != NULL)
            countEvidenceNodes(node->rightChild, c);
    }   
}

int Evidence::countEvidenceNodes(){
    int c(0);
    countEvidenceNodes(root, c);
    return c;
}

int Evidence::countTotalNodes(EvidenceNode *node){
    if (node == NULL){
        return 0;
    }
    return countTotalNodes(node->leftChild) + countTotalNodes(node->rightChild) + 1;
}

void Evidence::printEvidenceInventory() {
    printEvidenceInventory(root);
}

void Evidence::printEvidenceInventory(EvidenceNode *node){

    if(node->leftChild != NULL)
        printEvidenceInventory(node->leftChild);

    printSpecificCase(node);

    if(node->rightChild != NULL){
        printEvidenceInventory(node->rightChild);
    }
}

void Evidence::printSpecificCase(EvidenceNode *node) {
    char blue[] = { 0x1b, '[', '1', ';', '3', '4', 'm', 0 }; //changes case number to blue
    char normal[] = { 0x1b, '[', '0', ';', '3', '9', 'm', 0 }; //changes text back to white 

    if(node == NULL){
        cout << "Case number could not be traced." << endl;
    }

    else {
        cout << endl << "------------------------"<< endl;

        cout << blue << "Case Number: " << node->caseNum << normal << endl;

        cout << "Number of suspects: " << node->numSuspects << endl;
        cout << "Evidence related to the crime: " << endl;

        if(node->evidenceList.empty())
            cout << "There is currently no evidence for this case." << endl;
        else {
            for(int i=0; i<node->evidenceList.size(); i++) {
                cout << setw(3) << "-" << node->evidenceList[i] << endl;
            }
        }
        
        cout << endl << "Shelf number: " << node->shelfNumber << endl;

        if(node->renterName == "NONE")
            cout << "The evidence for this case is currently available." << endl;
        else
            cout << "This case is currently being used by: " << node->renterName << endl;

        cout << "------------------------\n" << endl;
    }
}

void Evidence::deleteEvidenceNode(string caseNumber) {
    EvidenceNode *temp = search(root, caseNumber);

    if(temp == NULL) {
        cout << "Case not found." << endl;
        return;
    }

    cout << "Before there were " << countTotalNodes(root) << " cases." << endl;
    //cases for deleting a node that is NOT the root
    if(temp != root) {
        //with no children
        if(temp->leftChild == NULL && temp->rightChild == NULL) {
            if(temp->parent->leftChild == temp) 
                temp->parent->leftChild = NULL;
            else 
                temp->parent->rightChild = NULL;
        }

        //two children
        else if (temp->leftChild != NULL && temp->rightChild != NULL) {
            EvidenceNode * min = EvidenceMinimum(temp->rightChild);
            if(min == temp->rightChild) {
                if(temp->parent->rightChild == temp) {
                    temp->parent->rightChild = min;
                }
                else 
                    temp->parent->leftChild = min;
                min->parent = temp->parent;
                min->leftChild = temp->leftChild;
            }
            else {
                min->parent->leftChild = min->rightChild;
                if(min->rightChild != NULL) {
                    min->rightChild->parent = min->parent;
                }
                min->parent = temp->parent;
                if(temp->parent->rightChild == temp) {
                    temp->parent->rightChild = min;
                }
                else 
                    temp->parent->leftChild = min;
                min->leftChild = temp->leftChild;
                min->rightChild = temp->rightChild;
                temp->rightChild->parent = min;
                temp->leftChild->parent = min;
            }
        }
        //one child
        else {
            EvidenceNode * x = NULL;
            if(temp->leftChild != NULL)
                x = temp->leftChild;
            else
                x = temp->rightChild;

            if(temp->parent->rightChild == temp)
                temp->parent->rightChild = x;
            else 
                temp->parent->leftChild = x;
            x->parent = temp->parent;
        }
    }

    //cases for deleting a node that is the root
    else {
        //no children
        if(temp->leftChild == NULL && temp->rightChild == NULL) {
            root = NULL;
        }
        //two children
        else if(temp->leftChild != NULL && temp->rightChild != NULL) {
            EvidenceNode * min = EvidenceMinimum(temp->rightChild);
            if(min == temp->rightChild) {
                temp->leftChild->parent = min;
                min->leftChild = temp->leftChild;
                min->parent = temp->parent;
            }
            else {
                min->parent->leftChild = min->rightChild;
                if(min->rightChild != NULL) {
                    min->rightChild->parent = min->parent;
                }
                min->parent = temp->parent;
                min->leftChild = temp->leftChild;
                min->rightChild = temp->rightChild;
                temp->rightChild->parent = min;
                temp->leftChild->parent = min;
            }
            root = min;
        }

        else {
            //EvidenceNode * x = NULL;
            if(temp->leftChild != NULL) {
                temp->leftChild->parent = temp->parent;
                root = temp->leftChild;
            }
            else {
                temp->rightChild->parent = temp->parent;
                root = temp->rightChild;
            }
        }
    }

    delete temp;
    cout << "Now there are " << countTotalNodes(root) << " cases." << endl;

}

void Evidence::DeleteAll(EvidenceNode* node){
    // clean to the left
    if (node->leftChild != NULL)
        DeleteAll(node->leftChild);
    // clean to the right
    if (node->rightChild != NULL)
        DeleteAll(node->rightChild);
    // delete this node
    //cout<<"Deleting: "<< node->caseNum << endl;
    delete node;
}

EvidenceNode * Evidence::search(EvidenceNode *root, string caseNumber) {
    if(root == NULL){
        return NULL;
    }
    if(root->caseNum == caseNumber){
        return root;
    }
    if(root->caseNum > caseNumber){
        return search(root->leftChild, caseNumber);
    }
    if(root->caseNum < caseNumber){
        return search(root->rightChild, caseNumber);
    }

    return NULL;
}

EvidenceNode * Evidence::EvidenceMinimum(EvidenceNode *node) {
    if(node != NULL) {
        if(node->leftChild == NULL)
            return node;            
        else
            return EvidenceMinimum(node->leftChild);
    }
    return NULL;
}