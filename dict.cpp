// Do NOT add any other includes
#include "dict.h"
#include <vector>

int hash1(std::string id) {
    long long int hash_ans = 0;
    for (int i = 0; i < id.length(); i++) {
        hash_ans += static_cast<int>(id[i]) * (i + 1); // Multiply by position (1-based)
    }
    int hash_value = hash_ans % 100019;
    return hash_value;
}


Dict::Dict() {
    root = nullptr;
    hash_table.resize(100019, nullptr);
}


Node::Node(string k){
    words=k;
    count=1;
    height =1;
}


int heights(Node*N) 
{ 
	if (N == nullptr) 
		return 0; 
	return N->height; 
} 

string max(string a,string b){
    if(a>=b){
        return a;
    }
    return b;
}

Node*rightRotate(Node*y) 
{ 
	Node*x = y->left; 
	Node*T2 = x->right; 

	x->right = y; 
	y->left = T2; 

	y->height = max(heights(y->left), 
					heights(y->right)) + 1; 
	x->height = max(heights(x->left), 
					heights(x->right)) + 1; 

	return x; 
} 
 
Node*leftRotate(Node*x) 
{ 
	Node*y = x->right; 
	Node*T2 = y->left; 

	y->left = x; 
	x->right = T2; 

	x->height = max(heights(x->left), 
					heights(x->right)) + 1; 
	y->height = max(heights(y->left), 
					heights(y->right)) + 1; 
 
	return y; 
} 

int getBalance(Node*N) 
{ 
	if (N == nullptr) 
		return 0; 
	return heights(N->left) - 
		heights(N->right); 
} 

Node* insertion(Node* node, string key) 
{   
    
	if (node == nullptr) {
		return new Node(key); 
    }
	if (key < node->words) 
		node->left = insertion(node->left, key); 
	else if (key > node->words) 
		node->right = insertion(node->right, key); 
	else 
		return node; 


	node->height = 1 + max(heights(node->left), 
						heights(node->right)); 

	
	int balance = getBalance(node); 

	

	if (balance > 1 && key < node->left->words) 
		return rightRotate(node); 

	if (balance < -1 && key > node->right->words) 
		return leftRotate(node); 

	if (balance > 1 && key > node->left->words) 
	{ 
		node->left = leftRotate(node->left); 
		return rightRotate(node); 
	} 

	if (balance < -1 && key < node->right->words) 
	{ 
		node->right = rightRotate(node->right); 
		return leftRotate(node); 
	} 


	return node; 
} 

Node* search(Node* node, string k) {
    while (node != NULL) {
        if (node->words == k) {
            return node;
        }
        if (k > node->words) {
            node = node->right;
        } else {
            node = node->left;
        }
    }
    return NULL;
}



void InOrderT(vector<pair<string, int> >& command1, Node* root) {
    if (root == NULL) {
        return;
    }

    InOrderT(command1, root->left);

    command1.push_back(std::make_pair(root->words, root->count));

    InOrderT(command1, root->right);
}



vector <string> * sent_to_word(string s){
	vector<string> * v = new vector<string> () ;
	string str="";

	for (char &c:s){
		if(std::isupper(c)){
			c=std::tolower(c);
		}
	}
for (std::size_t i = 0; i < s.length(); i++) {
        if (std::isalpha(s[i]) || std::isdigit(s[i]) || s[i]=='/' ||s[i]=='|' || s[i]=='&' || s[i]=='$'|| s[i]=='%'|| s[i]=='~'|| s[i]=='_'|| s[i]=='#'|| s[i]=='+'|| s[i]=='='|| s[i]=='*'|| s[i]=='<'|| s[i]=='>'|| s[i]=='^'|| s[i]=='`'|| s[i]=='{'|| s[i]=='}'|| s[i]=='\\') {
            // if(s[i]!='.' && s[i]!=' ' && s[i]!=',' && s[i]!='-' && s[i]!='!' && s[i]!='"' && s[i]!='\'' && s[i]!='(' && s[i]!=')' && s[i]!='?' && s[i]!='—' && s[i]!='[' && s[i]!=']' && s[i]!='“'&& s[i]!='”' && s[i]!='˙'&& s[i]!=';'&&s[i]!='@' ){
            str += s[i];
        } else if (!str.empty()) {
            v->push_back(str);
            str = ""; 
        }
    }

    if (!str.empty()) {
        v->push_back(str);
    }
	return v;
}


void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence) {
    if (sentence.empty()) {
        return; // Skip empty sentences
    }

    vector<string>* temp = sent_to_word(sentence);

    while (!temp->empty()) {
        for (int i = 0; i < temp->size(); i++) {
            int position = hash1((*temp)[i]);
            if (hash_table[position] == NULL) {
                Node* temp1 = new Node((*temp)[i]);
                hash_table[position] = temp1;
            } else {
                Node* foundNode = search(hash_table[position], (*temp)[i]);
                if (foundNode == NULL) {
                    hash_table[position] = insertion(hash_table[position], (*temp)[i]);
                } else {
                    foundNode->count++;
                }
            }
        }
        temp->clear();
    }
    delete temp; // Free the allocated memory
}


        
    
    



int Dict::get_word_count(string word) {
    // Normalize the word to lowercase
    for (char& c : word) {
        c = std::tolower(c);
    }

    int position = hash1(word);
    Node* searchNode = search(hash_table[position], word);

    if (searchNode) {
        return searchNode->count;
    } else {
        return 0; // Word not found in the dictionary
    }
}






void Dict::dump_dictionary(string filename) {
    ofstream output(filename);
    if (!output.is_open()) {
        // Handle the case where the file couldn't be opened
        return;
    }

vector<pair<string, int> > commands;

    for (int i = 0; i < hash_table.size(); i++)
    {
        if(hash_table[i]==NULL){
            continue;
        }
        else{
            InOrderT( commands , hash_table[i]);
        }
    }
    
    

    for (const auto& command : commands) {
        output << command.first << ", " << command.second << endl;
    }

    output.close();
}




Dict::~Dict() {
    // for (Node* node : hash_table) {
    //     if (node != nullptr) {
    //         delete node; // Clean up dynamically allocated nodes
    //     }
    // }
}


// int main() {
//     // Create an instance of your Dict class
//     Dict dictionary;

//     // Insert sentences into the dictionary
//     // dictionary.insert_sentence(1, 1, 1, 1, "(Missing: & - Missing: 1 - Missing: 1/ - Missing: 1/2 - Missing: 1/2d 1/s 1/2lb 1/3 1/3s 1/4 1/6 10 10/ 100 101 102 103 104 105 106 107 108 109 10klip 10s 10th 11 11/2 11/2d 11/2s 11/3d 110 111 112 113 114 1140 1145 115 116 117 118 119 1192 11d 11newcastle 11s 11th 12 120 121 122 123 124 125 126 127 128 129 12alexandra 12handkerchiefs 12th 13 130 131 1310 132 133 134 1340 135 136 137 138 139 13alfred 13th 14 140 141 142 143 144 145 146 147 148 149 14s 14th 15 150 151 152 153 154 1545 155 156 157 158");
//     dictionary.insert_sentence(1, 1, 1, 1, "1. A CONFESSION 1");
//     dictionary.insert_sentence(1, 1, 1, 1, "[1884] I wrote it on a slip of paper and handed it to him myself.");
//     dictionary.insert_sentence(1, 1, 1, 1, "In this note not only did I confess my guilt, but I asked adequate punishment for it, and closed with a request to him not to punish himself for my offence.");
//     dictionary.insert_sentence(1, 1, 1, 1, " I also pledged myself never to steal in future.");
//     dictionary.insert_sentence(1, 1, 1, 1, "An Autobiography, Pt. I, Ch. VIII");
//     dictionary.insert_sentence(1, 1, 1, 1, "2. SPEECH AT ALFRED HIGH SCHOOL, RAJKOT 3");

//     // dictionary.insert_sentence(1, 1, 1, 1, "VOL.1: 1884 30 NOVEMBER, 1896 1");
//     // dictionary.insert_sentence(1, 1, 1, 1, "VOL.1: 1884 30 NOVEMBER, 1896 1");
//     // dictionary.insert_sentence(1, 1, 1, 1, "VOL.1: 1884 30 NOVEMBER, 1896 1");

//     // dictionary.insert_sentence(1, 1, 1, 1, "VOL.1: 1884 30 NOVEMBER, 1896 1");
//     // dictionary.insert_sentence(1, 1, 1, 1, "VOL.1: 1884 30 NOVEMBER, 1896 1");
//     // dictionary.insert_sentence(1, 1, 1, 2, "Another test sentence.");
//     dictionary.insert_sentence(1, 2, 1, 1, "Yet another test sentence.");

//     // Dump the dictionary to a file
//     dictionary.dump_dictionary("dictionary.txt");

//     return 0;
// }
