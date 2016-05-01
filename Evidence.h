#ifndef EVIDENCE_H
#define EVIDENCE_H
#include <vector>
#include <string>


struct EvidenceNode {
    std::string caseNum; //case number attached to evidence.
    int numSuspects; //number of suspected criminals
    int shelfNumber; //shelf number where evidence is kept
    std::string renterName; //name of detective currently working on the case
    
    std::vector<std::string> evidenceList; //dynamic list of all pieces of evidence linked to each case
    
    EvidenceNode *parent;
    EvidenceNode *leftChild;
    EvidenceNode *rightChild;

    EvidenceNode(){};

    EvidenceNode(std::string in_caseNum, int in_shelfNumber, int in_suspects, std::string in_renterName)
    {
        caseNum = in_caseNum;
        numSuspects = in_suspects;
        shelfNumber = in_shelfNumber;
        renterName = in_renterName;
        parent = NULL;
        leftChild = NULL;
        rightChild = NULL;
    }
};

class Evidence
{
    public:
        Evidence();
        ~Evidence();
        void buildEvidenceLog(char *filename);
        void addEvidenceNode(std::string caseNumber, int shelfNumber, int suspects, std::string renterName);
        void initializeEvidence(std::string item, std::string caseNumber);
        void findEvidence(std::string caseNumber); //currently only searches for caseNum
        void printSpecificCase(EvidenceNode *node);
        void printEvidenceInventory();
        void rentEvidence(std::string caseNumber);
        int countEvidenceNodes();
        void deleteEvidenceNode(std::string caseNumber);
        void returnEvidence(std::string caseNumber); //sets renterName to null

    protected:

    private:
        EvidenceNode* search(EvidenceNode *root, std::string caseNumber);
        void printEvidenceInventory(EvidenceNode * node);
        void DeleteAll(EvidenceNode * node); //use this for the post-order traversal deletion of the tree
        void countEvidenceNodes(EvidenceNode *node, int &c);
        //void countTotalCases(EvidenceNode *node, int &c);
        int countTotalNodes(EvidenceNode *node);
        EvidenceNode * EvidenceMinimum(EvidenceNode *node);
        EvidenceNode *root;
};

#endif // EVIDENCETREE_H
