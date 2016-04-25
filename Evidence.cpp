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
            }
            else if(answer == 'n' || answer == 'N')
                return;
        } while(answer != 'y' || answer != 'Y' || answer != 'n' || answer != 'N');
    }
}

void Evidence::rentEvidence(string caseNumber) {
    //do we want to include an option for cases that do not have any evidence?
    EvidenceNode * node = search(root, caseNumber);
    if(node->renterName != "NONE") {
        cout << "The evidence for this case is currently being used by " << node->renterName << "." << endl;
    }
    else {
        string name;
        cout << "Please enter your first and last name: ";
        getline(cin, name);
        node->renterName = name;
        cout << "You have just rented the evidence for case number: " << node->caseNum << endl;
        cout << "Included are the following items:" << endl;
        for(int i=0; i<node->evidenceList.size(); i++) {
            cout << setw(3) << "-" << node->evidenceList[i] << endl;
        }
        cout << endl << "You have one week to these items. If you wish to use them for a longer period of time, please talk to  case manager Jim Lahey.\n" << endl;
    }
}

int Evidence::countEvidenceNodes(EvidenceNode *node, int &c) {
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
    char blue[] = { 0x1b, '[', '1', ';', '3', '4', 'm', 0 };
    char normal[] = { 0x1b, '[', '0', ';', '3', '9', 'm', 0 };

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

EvidenceNode * Evidence::search(EvidenceNode *root, std::string caseNumber) {
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
