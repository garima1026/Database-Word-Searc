// Do NOT add any other includes
#include <string> 
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class Node{
public:
    int count;
    int height;
    string words;

    Node*par=nullptr;
    Node*left=nullptr;
    Node*right=nullptr;
    Node(string k);
    ~Node();
};

class Dict {
private:
    // You can add attributes/helper functions here
    
    Node* root=nullptr;
    vector<Node* > hash_table ;
    
    
public: 
    /* Please do not touch the attributes and 
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    // vector<Node* > hash_table (int 100000 , nullptr);

    // vector<pair<string, int> > commands;

    Dict();

    ~Dict();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    int get_word_count(string word);

    void dump_dictionary(string filename);

    /* -----------------------------------------*/
};
