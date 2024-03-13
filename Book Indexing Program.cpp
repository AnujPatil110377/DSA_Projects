#include <bits/stdc++.h>
#include <regex>
#include <locale>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>
using namespace std;
vector<string> chapterslist;
void get_chapterlist() {
    ifstream inputfile("chapterNames.txt");

    if(!inputfile.is_open()) {
        cerr << "Unable to open file" << endl;
        return;
    }

    string line;
    while(getline(inputfile, line)){
        istringstream iss(line);
        string word;

        while(iss >> word){
            chapterslist.push_back(word);
            
        }
    }
}

class HybridNode
{
public:
    string key;                              
    string element;                        
    HybridNode *parent;                      
    HybridNode *left_child;                
    HybridNode *right_child;              
    HybridNode *next_node;                   
    string color = "black";                  
    vector<std::pair<string, int>> chapters; 

    HybridNode(string key_val, string element_val) : key(key_val), element(element_val), parent(nullptr), left_child(nullptr), right_child(nullptr), next_node(nullptr) {}
    void updateChapterCount(const string &chapterName)
    {

        for (auto &chapter : chapters)
        {
            if (chapter.first == chapterName)
            {
                chapter.second++;
                return;
            }
        }

        chapters.push_back(make_pair(chapterName, 1));
    }

   .
};

class RedBlackTree
{
private:
    HybridNode *root; 

public:
    RedBlackTree() : root(nullptr) {}

    HybridNode *getRoot()
    {
        return root; 
    }

    void setRoot(HybridNode *node)
    {
        root = node; 
    }

    HybridNode *insert(string key, string element)
    {
        
        HybridNode *newNode = new HybridNode(key, element);
        HybridNode *parent = nullptr;
        HybridNode *current = root;

       
        newNode->color = "red";

        while (current != nullptr)
        {
            parent = current;

            
            if (key < current->key)
            {
                current = current->left_child;
            }
            else if (key > current->key)
            {
                current = current->right_child;
            }
            else
            {
                
                current->updateChapterCount(element); 

                return current; 
            }
        }

        
        newNode->parent = parent;

       
        if (parent == nullptr)
        {
            root = newNode;
        }
        else if (key < parent->key)
        {
            parent->left_child = newNode;
        }
        else
        {
            parent->right_child = newNode;
        }
        newNode->chapters.push_back(make_pair(element, 1));
        
        insertFixup(newNode);

        return newNode;
        
    }

    void insertFixup(HybridNode *node)
    {
        while (node != root && node->parent != nullptr && node->parent->color == "red")
        {
           
            if (node->parent == node->parent->parent->left_child)
            {
                HybridNode *uncle = node->parent->parent->right_child;

                
                if (uncle != nullptr && uncle->color == "red")
                {
                    node->parent->color = "black";
                    uncle->color = "black";
                    node->parent->parent->color = "red";
                    node = node->parent->parent;
                }
                else
                {
                    
                    if (node == node->parent->right_child)
                    {
                        node = node->parent;
                        leftRotate(node);
                    }

                    
                    node->parent->color = "black";
                    node->parent->parent->color = "red";
                    rightRotate(node->parent->parent);
                }
            }
            else
            {
                
                HybridNode *uncle = node->parent->parent->left_child;

                
                if (uncle != nullptr && uncle->color == "red")
                {
                    node->parent->color = "black";
                    uncle->color = "black";
                    node->parent->parent->color = "red";
                    node = node->parent->parent;
                }
                else
                {
                    
                    if (node == node->parent->left_child)
                    {
                        node = node->parent;
                        rightRotate(node);
                    }

                    
                    node->parent->color = "black";
                    node->parent->parent->color = "red";
                    leftRotate(node->parent->parent);
                }
            }
        }

        root->color = "black"; 
    }

    void leftRotate(HybridNode *node)
    {
       
        HybridNode *y = node->right_child;
        node->right_child = y->left_child;
        if (y->left_child != nullptr)
        {
            y->left_child->parent = node;
        }
        y->parent = node->parent;
        if (node->parent == nullptr)
        {
          
            root = y;
        }
        else if (node == node->parent->left_child)
        {
            node->parent->left_child = y;
        }
        else
        {
            node->parent->right_child = y;
        }
        y->left_child = node;
        node->parent = y;
    }

    void rightRotate(HybridNode *node)
    {
        
        HybridNode *x = node->left_child;
        node->left_child = x->right_child;
        if (x->right_child != nullptr)
        {
            x->right_child->parent = node;
        }
        x->parent = node->parent;
        if (node->parent == nullptr)
        {
           
            root = x;
        }
        else if (node == node->parent->right_child)
        {
            node->parent->right_child = x;
        }
        else
        {
            node->parent->left_child = x;
        }
        x->right_child = node;
        node->parent = x;
    }

    bool deleteNode(string key)
    {
        HybridNode *nodeToDelete = search(key);

        if (nodeToDelete == nullptr)
        {
            
            return false;
        }

        HybridNode *y = nullptr; 
        HybridNode *x = nullptr; 
        string originalColor = nodeToDelete->color;

        if (nodeToDelete->left_child == nullptr || nodeToDelete->right_child == nullptr)
        {
            y = nodeToDelete;
        }
        else
        {
            y = getSuccessor(nodeToDelete);
        }

        if (y->left_child != nullptr)
        {
            x = y->left_child;
        }
        else
        {
            x = y->right_child;
        }

        if (y->parent == nullptr)
        {
            root = x;
        }
        else if (y == y->parent->left_child)
        {
            y->parent->left_child = x;
        }
        else
        {
            y->parent->right_child = x;
        }

        if (y != nodeToDelete)
        {
            nodeToDelete->key = y->key;
            
        }

        if (y->color == "black")
        {
            deleteFixup(x);
        }

        delete y;

        return true;
    }

    void deleteFixup(HybridNode *x)
    {
        if (x == nullptr)
        {
            return;
        }
        while (x != root && x->color == "black")
        {
            if (x == x->parent->left_child)
            {
                HybridNode *w = x->parent->right_child;

                if (w->color == "red")
                {
                    w->color = "black";        
                    x->parent->color = "red";   
                    leftRotate(x->parent);      
                    w = x->parent->right_child; 
                }

                if ((w->left_child == nullptr || w->left_child->color == "black") &&
                    (w->right_child == nullptr || w->right_child->color == "black"))
                {
                    w->color = "red"; 
                    x = x->parent;    
                }
                else
                {
                    if (w->right_child == nullptr || w->right_child->color == "black")
                    {
                        if (w->left_child != nullptr)
                            w->left_child->color = "black";
                        w->color = "red";                  
                        rightRotate(w);                    
                        w = x->parent->right_child;        
                    }

                    w->color = x->parent->color; 
                    x->parent->color = "black";  
                    if (w->right_child != nullptr)
                        w->right_child->color = "black"; 
                    leftRotate(x->parent);               
                    x = root;                            
                }
            }
            else
            {
               
                HybridNode *w = x->parent->left_child;

                if (w->color == "red")
                {
                    w->color = "black";        
                    x->parent->color = "red";  
                    rightRotate(x->parent);    
                    w = x->parent->left_child; 
                }

                if ((w->right_child == nullptr || w->right_child->color == "black") &&
                    (w->left_child == nullptr || w->left_child->color == "black"))
                {
                    w->color = "red"; 
                    x = x->parent;    
                }
                else
                {
                    if (w->left_child == nullptr || w->left_child->color == "black")
                    {
                        if (w->right_child != nullptr)
                            w->right_child->color = "black"; 
                        w->color = "red";                    
                        leftRotate(w);                       
                        w = x->parent->left_child;          
                    }

                    w->color = x->parent->color; 
                    x->parent->color = "black";  
                    if (w->left_child != nullptr)
                        w->left_child->color = "black"; 
                    rightRotate(x->parent);             
                    x = root;                          
                }
            }
        }

        if (x != nullptr)
        {
            x->color = "black";
        }
    }

    HybridNode *getSuccessor(HybridNode *node)
    {
        HybridNode *successor = node->right_child;
        while (successor->left_child != nullptr)
        {
            successor = successor->left_child;
        }
        return successor;
    }

    void transplant(HybridNode *u, HybridNode *v)
    {
        if (u == nullptr)
        {
            cout << "Invalid input" << endl;
        }

        if (u->parent == nullptr)
        {
            root = v;
        }
        else if (u == u->parent->left_child)
        {
            u->parent->left_child = v;
        }
        else
        {
            u->parent->right_child = v;
        }
        if (v != nullptr)
        {
            v->parent = u->parent;
        }
    }

    vector<HybridNode *> traverseUp(HybridNode *node)
    {
        vector<HybridNode *> path; 

       
        while (node != nullptr)
        {
            path.push_back(node); 
            node = node->parent;  
        }

        

        return path;
    }

    vector<HybridNode *> traverseDown(HybridNode *node, string bit_sequence)
    {
        vector<HybridNode *> path; 
        int index = 0;

        while (node != nullptr && index < bit_sequence.length())
        {
            path.push_back(node);

           
            char direction = bit_sequence[index];

            if (direction == '0')
            {
                if (node->right_child != nullptr)
                {
                    node = node->right_child;
                }
                else
                {
                    break; 
                }
            }
            else if (direction == '1')
            {
                if (node->left_child != nullptr)
                {
                    node = node->left_child;
                }
                else
                {
                    break; 
                }
            }

            index++; 
        }

        /

        return path;
    }

    vector<HybridNode *> preOrderTraversal(HybridNode *node, int targetDepth)
    {

        vector<HybridNode *> path;                           
        preOrderTraversalHelper(node, targetDepth, 0, path); 

        return path;
    }

    void preOrderTraversalHelper(HybridNode *node, int targetDepth, int currentDepth, vector<HybridNode *> &path)
    {

        if (node == nullptr || currentDepth > targetDepth)
        {
            return; 
        }

        
        path.push_back(node);

       
        preOrderTraversalHelper(node->left_child, targetDepth, currentDepth + 1, path);
        preOrderTraversalHelper(node->right_child, targetDepth, currentDepth + 1, path);
    }

    HybridNode *search(string key)
    {
        return searchHelper(root, key);
    }

    HybridNode *searchHelper(HybridNode *node, string key)
    {
        if (node == nullptr)
        {
            return nullptr; 
        }

        if (key == node->key)
        {
            return node; 
        }

        if (key < node->key)
        {
            if (node->left_child != nullptr)
            {
                return searchHelper(node->left_child, key); 
            }
        }
        else
        {
            if (node->right_child != nullptr)
            {
                return searchHelper(node->right_child, key); 
            }
        }

        return nullptr; 
    }

    int blackheight(HybridNode *node)
    {
        int blackHeight = 0;

        while (node != nullptr)
        {

            if (node->color == "black")
            {
                blackHeight++; 
            }
            node = node->left_child; 
        }

        return blackHeight;
    }
};

class IndexEntry
{
private:
    string word;
    vector<pair<string, int>> chapter_word_counts; 

public:
    IndexEntry(string word_val) : word(word_val) {}

    void setWord(string word_val)
    { 
        word = word_val;
    }

    string getWord()
    {
        std::string lowercaseWord = word;
        std::transform(lowercaseWord.begin(), lowercaseWord.end(), lowercaseWord.begin(), ::tolower);
        return lowercaseWord;
    }

    void setChapterWordCounts(vector<pair<string, int>> chapter_word_counts_val)
    { 
        chapter_word_counts = chapter_word_counts_val;
    }

    vector<pair<string, int>> getChapterWordCounts()
    {
        return chapter_word_counts;
    }
    void addOccurrence(string chapter, int word_count)
    {if (chapter.size() > 4 && chapter.substr(chapter.size() - 4) == ".txt") {
        chapter = chapter.substr(0, chapter.size() - 4);
    }

    
    chapter_word_counts.push_back(make_pair(chapter, word_count));
    }
};

class Lexicon
{
private:
    RedBlackTree red_black_tree; // Red-Black Tree

public:
    Lexicon() {}

    void setRedBlackTree(RedBlackTree tree)
    { 
        red_black_tree = tree;
    }

    RedBlackTree getRedBlackTree()
    { 
        return red_black_tree;
    }

    void readChapters(vector<string> chapter_names)
    {
        
        for (const string &chapter_name : chapter_names)
        {   
            
            string filename =chapter_name;
            

            vector<string> words = readWordsFromFile(filename);
            
            for (const string &word : words)
            {

                HybridNode *node = red_black_tree.insert(word, chapter_name);
                if (node != nullptr)
                {

                    string New_key = node->key;
                    IndexEntry indexEntry(New_key);
                    indexEntry.addOccurrence(chapter_name, 1); 
                }
            }
        }

        pruneRedBlackTree();
    }

    vector<IndexEntry> buildIndex()
    {
        get_chapterlist();
        vector<IndexEntry> indexEntries; 

       
        vector<HybridNode *> nodes = red_black_tree.preOrderTraversal(red_black_tree.getRoot(), getMaxDepth(red_black_tree.getRoot()));
        
        for (HybridNode *node : nodes)
        {
            
            IndexEntry indexEntry(node->key);

           
            for (const string &chapter : chapterslist)
            {
                int wordCount = 0;
                for (const pair<string, int> &chapterPair : node->chapters)
                {
                   
                    if (chapterPair.first == chapter)
                    {
                        wordCount = chapterPair.second;
                        break; 
                    }
                }

                indexEntry.addOccurrence(chapter, wordCount);
            }

            indexEntries.push_back(indexEntry);
        }

        return indexEntries;
    }

    void pruneRedBlackTree()
    {
        vector<string> wordsToDelete;

       
        vector<HybridNode *> words = getRedBlackTree().preOrderTraversal(getRedBlackTree().getRoot(), 10);

        for (HybridNode *word : words)
        {
           
            if (word != nullptr && word->chapters.size() == 3)
            {
                
                wordsToDelete.push_back(word->key);
            }
        }

        for (const string &word : wordsToDelete)
        {
            getRedBlackTree().deleteNode(word);
        }
    }
    int findMaxDepth(HybridNode *node)
    {
        if (node == nullptr)
        {
            return 0; 
        }

       
        int leftDepth = findMaxDepth(node->left_child);
        int rightDepth = findMaxDepth(node->right_child);

       
        return 1 + max(leftDepth, rightDepth);
    }

    int getMaxDepth(HybridNode *root)
    {
        return findMaxDepth(root);
    }

private:
    std::string replacePunctuation(const std::string &input)
    {
        
        std::regex pattern("[^\\w\\s']+");

        
        std::string result = std::regex_replace(input, pattern, " ");

        return result;
    }

    std::string toLowercase(const std::string &input)
    {
        std::string result = input;
        for (char &c : result)
        {
            c = std::tolower(c); 
        }
        return result;
    }

    std::vector<std::string> readWordsFromFile(const std::string &filename)
    {
        std::vector<std::string> words;
        std::ifstream file(filename);

        if (!file.is_open())
        {
            std::cerr << "Error: Unable to open file '" << filename << "'" << std::endl;
            return words;
        }

        std::string word;
        std::string buffer; 

        while (file >> word)
        {
            for (char &c : word)
            {
                if (std::ispunct(c) && c != '\'' && c != '-')
                {
                   
                    if (!buffer.empty())
                    {
                        words.push_back(buffer);
                        buffer.clear();
                    }
                }
                else
                {
                    buffer += c;
                }
            }

            if (!buffer.empty())
            {
                words.push_back(buffer);
                buffer.clear();
            }
        }

        if (file.eof())
        {
            
            file.close();
        }
        else
        {
            std::cerr << "Error: Failed to read the entire file '" << filename << "'" << std::endl;
            file.close();  
            words.clear(); 
        }

        return words;
    }
};
int COunt = 0;
int countNodes(HybridNode *node)
{

    if (node == nullptr)
    {
        return 0; 
    }

    
    int leftCount = countNodes(node->left_child);
    int rightCount = countNodes(node->right_child);

    return 1 + leftCount + rightCount;
}


