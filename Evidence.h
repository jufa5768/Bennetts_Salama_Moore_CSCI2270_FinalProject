#ifndef EVIDENCE_H
#define EVIDENCE_H

struct MovieNode{
    std::string itemName; //type of evidence, eg. drugs/guns
    int caseNum; //case number attached to evidence.
    int quantity; //amount of evidence attached to individual person
    std::string renterName; //name of renter
    int shelfNumber; //shelf number
    EvidenceNode *parent;
    EvidenceNode *leftChild;
    EvidenceNode *rightChild;

    EvidenceNode(){};

    EvidenceNode(int in_caseNum, std::string in_itemName, int in_shelfNumber, int in_quantity)
    {
        itemName = in_itemName;
        caseNum = in_caseNum;
        quantity = in_quantity;
        shelfNumber = in_shelfNumber;
        renterName = NULL;
        parent = NULL;
        leftChild = NULL;
        rightChild = NULL;
    }
};

class Evidence
{
    public:
        EvidenceNode();
        ~EvidenceNode();
        void printEvidenceInventory();
        int countEvidenceNodes();
        void deleteEvidenceNode(std::string title);
        void addEvidenceNode(int in_caseNum, std::string in_itemName, int in_shelfNumber, int in_quantity); //does not include renter name.
        void findEvidence(int caseNum); //currently only searches for caseNum
        void rentEvidence(int caseNum, std::string in_renterName);
        void returnEvidence(int caseNum) //sets renterName to null

    protected:

    private:
        void DeleteAll(EvidenceNode * node); //use this for the post-order traversal deletion of the tree
        void printEvidenceInventory(EvidenceNode * node);
        int countEvidenceNodes(EvidenceNode *node);
        EvidenceNode* search(EvidenceNode *search,int in_caseNum);
        EvidenceNode* EvidenceMinimum(EvidenceNode *node);
        EvidenceNode *root;
};

#endif // MOVIETREE_H
