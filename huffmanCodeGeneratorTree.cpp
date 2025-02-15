#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

// Huffman Tree Node
struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;

    Node(char c, int f) {
        ch = c;
        freq = f;
        left = right = nullptr;
    }
};

// Comparator for priority queue
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

Node* huffmanTree(vector<char>& inputStringChar, vector<int>& frequencyValues) {
    priority_queue<Node*, vector<Node*>, Compare> heapQueue;

    for (size_t i = 0; i < inputStringChar.size(); i++) {
        heapQueue.push(new Node(inputStringChar[i], frequencyValues[i]));
    }

    while (heapQueue.size() > 1) {
        Node* left = heapQueue.top(); heapQueue.pop();
        Node* right = heapQueue.top(); heapQueue.pop();

        Node* newNode = new Node('$', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;
        
        heapQueue.push(newNode);
    }

    return heapQueue.top();  
}


// This function is to create the huffman code for each of the node and store in a map.
void getHuffmanCodes(Node* root, string code, unordered_map<char, string>& codes) {
    if (!root) return;

    // If leaf node, store the code
    if (root->ch != '$') {
        codes[root->ch] = code;
    }

    getHuffmanCodes(root->left, code + "0", codes);
    getHuffmanCodes(root->right, code + "1", codes);
}

// Preorder traversal to print Huffman codes
void preorder(Node* root, unordered_map<char, string>& codes) {
    if (!root) return;

    if (root->ch != '$') {
        cout << root->ch << ": " << codes[root->ch] << endl;
    }

    preorder(root->left, codes);
    preorder(root->right, codes);
}

// Main function
int main() {
    
    string inputString;
    cout << "Enter the input string in all small case letters" << "\n";
    cin >> inputString; // get user input from the keyboard
    cout << "Input String is " << inputString << "\n";
    cout << "Enter the frequecy array for each char for the string" << "\n";
    
    int sizeofInput = inputString.length();

    std::vector<int> frequency(sizeofInput);
    for (int i = 0; i < sizeofInput; i++) {
        cin >> frequency[i];
    }
    
    std::vector<char> charVector(inputString.begin(), inputString.end());

    // vector<char> S = {'a', 'b', 'c', 'd', 'e', 'f'};
    // vector<int> f = {5, 9, 12, 13, 16, 45};

    Node* root = huffmanTree(charVector, frequency);

    unordered_map<char, string> codes;
    getHuffmanCodes(root, "", codes);

    // Print Huffman Codes in Preorder
    cout << "Huffman Codes in Preorder Traversal:\n";
    preorder(root, codes);

    return 0;
}
