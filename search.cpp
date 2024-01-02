// Do NOT add any other includes
#include "search.h"

// #define d 256

SearchEngine::SearchEngine(){
    // Implement your function here  
}

SearchEngine::~SearchEngine(){
    // Implement your function here 
    // delete [] corpus; 
}

void SearchEngine::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    // Implement your function here 
    for (char &c : sentence) {
        if (std::isupper(c)) {
            c = std::tolower(c);
        }
    }
    vector<int> details ={book_code,page,paragraph,sentence_no};
    corpus.push_back(make_pair(sentence,details)); 
    return;
}



// int hash(std::string id) {
//     long long int hash_ans = 0;
//     for (int i = 0; i < id.length(); i++) {
//         hash_ans += static_cast<int>(id[i]) * (i + 1); // Multiply by position (1-based)
//     }
//     int hash_value = hash_ans % 100019;
//     return hash_value;
// }









// Node* SearchEngine::search(string pattern, int& n_matches) {
//     int p = 31;
//     n_matches = 0;
//     const int N = 1e5 + 7, m = 1e9 + 7;
//     int S = pattern.size();
//     int T = 0;
//     vector<long long> power(N);

//     // Calculate the hash of the pattern
//     long long h_s = 0;
//     for (int i = 0; i < S; i++) {
//         h_s = (h_s * p + (pattern[i] - 'a' + 1)) % m;
//     }

//     for (int k = 0; k < corpus.size(); k++) {
//         T = corpus[k].first.size();
//         power[0] = 1;
//         for (int i = 0; i < N; i++) {
//             power[i] = (power[i - 1] * p) % m;
//         }

//         vector<long long> h(T + 1, 0);
//         for (int i = 0; i < T; i++) {
//             h[i + 1] = (h[i] * p + (corpus[k].first[i] - 'a' + 1)) % m;
//         }

//         for (int i = 0; i + S - 1 < T; i++) {
//             long long curr_h = (h[i + S] - (h[i] * power[S]) % m + m) % m;
//             cout<<"i am here "<<endl;
//             cout<<"curr_h"<<curr_h<<endl;
//             cout<<"h_s"<<h_s<<endl;
//             if (curr_h == h_s) {
//                 cout<<"i am here1  "<<endl;
//                 if (corpus[k].first.substr(i, S) == pattern) {
//                     cout<<"found a match "<<endl;
//                     // Insert into linked list
//                     n_matches++;
//                     cout << "String found is " << corpus[k].first.substr(i, S) << endl;
//                 }
//             }
//         }
//     }

//     return nullptr;
// }







// Node* SearchEngine::search(string pattern, int& n_matches) {
//     int p = 31;
//     const int N = 1e5 + 7, m = 1e9 + 7;
//     int S = pattern.size();
//     n_matches = 0;

//     // Calculate the hash of the pattern
//     long long h_s = 0;
//     for (int i = 0; i < S; i++) {
//         h_s = (h_s * p + (pattern[i] - 'a' + 1)) % m;
//     }

//     Node * nill = new Node ();
//     Node * temp = nill;


//     for (int k = 0; k < corpus.size(); k++) {
//         string text = corpus[k].first;
//         int T = text.size();

//         long long h_text = 0;
//         long long power = 1;
//         for (int i = 0; i < S; i++) {
//             h_text = (h_text * p + (text[i] - 'a' + 1)) % m;
//             if (i > 0) {
//                 power = (power * p) % m;
//             }
//         }

//         for (int i = 0; i <= T - S; i++) {
//             if (h_text == h_s && text.substr(i, S) == pattern) {
//                 n_matches++;
//                 Node* n = new Node(corpus[k].second[0],corpus[k].second[1],corpus[k].second[2],corpus[k].second[3],i);
//                 temp->right= n ;
//                 n->left = temp;
//                 temp = temp->right;
//                 // cout<<temp->book_code<<"  ;  "<<temp->offset<<"  ;  "<<temp->page<<"  ;  "<<temp->paragraph<<"  ;  "<<temp->sentence_no<<endl;
//                 }
//                 // Insert into a linked list or perform any other necessary actions
//                 // cout << "String found: " << pattern << endl;
//                 // cout << "Book Code: " << corpus[k].second[0] << ", Page: " << corpus[k].second[1]
//                 //      << ", Paragraph: " << corpus[k].second[2] << ", Sentence No: " << corpus[k].second[3]
//                 //      << ", Position: " << i << endl;
            

//             // Update the rolling hash for the next substring
//             if (i < T - S) {
//                 h_text = (h_text - (text[i] - 'a' + 1) * power) % m;
//                 if (h_text < 0) {
//                     h_text += m;
//                 }
//                 h_text = (h_text * p + (text[i + S] - 'a' + 1)) % m;
//             }
//         }
//     }

//     return nill->right;
// }





vector<int> prefix_function(string s){
    int n=s.size();
    vector<int>pi(n,0);
    for(int i=1;i<n;i++){
        int j=pi[i-1];

        while(j>0 && s[i]!=s[j]){
            j=pi[j-1];
        }
        if ( s[i]==s[j]){
            j++;
        }
        pi[i]=j;
    }
    return pi;
}


Node* SearchEngine::search(string pattern, int& n_matches){
    Node * nill = new Node ();
    Node * temp = nill;
    n_matches=0;
    for (int k = 0; k < corpus.size(); k++){
        string text = corpus[k].first;
        vector<int>prefix = prefix_function(pattern);
        int pos=-1;
        int i=0;
        int j=0;
        while(i<text.size()){
            if(text[i]==pattern[j]){
                j++;
                i++;
            }
            else{
                if(j!=0)
                    j=prefix[j-1];
                else
                    i++;
            }  
            if(j==pattern.size()){
                pos=i-pattern.size();
                n_matches++;
                Node* n = new Node(corpus[k].second[0],corpus[k].second[1],corpus[k].second[2],corpus[k].second[3],pos);
                 temp->right= n ;
                 n->left = temp;
                 temp = temp->right;
            }
        }
    }
    return nill->right;
}