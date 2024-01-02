Document Word Search

## Dictionary Implementation (Part 1)

I have created a dictionary data structure for storing word counts in a document. I have implemented this using AVL Trees.

### Dict Class Functions (dict.cpp)

- **Dict():** Created a Dict instance. Initialized data structures for storing word counts.
- **void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string s):** Split the given sentence s into its words and increment word counts.
- **int get_word_count(string word):** Given a word, return its count in the document (case-insensitive).
- **void dump_dictionary(string filename):** Dump the dictionary into the given file, with words and counts.
- **~Dict():** Destroy the Dict instance.

## Pattern Search Implementation (Part 2)

Implement a search mechanism to find a string pattern in the document. Return a list of offsets where the pattern is present.

### SearchEngine Class Functions (search.cpp)

- **SearchEngine():** Created a SearchEngine instance. Initialized data structures for pattern search.
- **void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string s):** Pre-process the sentence for search queries.
- **Node* search(string pattern, int &n_matches):** Given a pattern, create a linked list of nodes containing match data. Return the head of the linked list and update the match count.
- **~SearchEngine():** Destroy the SearchEngine instance.


