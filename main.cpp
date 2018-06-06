#include <iostream>
#include <string.h>
#include <fstream>
#include <map>
#include <queue>
#include <stdlib.h>

using namespace std;


int sizeMap = 0;
 
struct MinHeapNode
{
    char word[100];          
    unsigned freq;           
    MinHeapNode *left, *right; 
 
    MinHeapNode(char word[100], unsigned freq)
    {
        left = right = NULL;
        strcpy(this->word, word);
        this->freq = freq;
    }
};
 
struct compare
{
    bool operator()(MinHeapNode* l, MinHeapNode* r)
    {
        return (l->freq > r->freq);
    }
};
 
void printTree(struct MinHeapNode* root, string str, ofstream &outFile, ofstream &outFile1)
{
    if (!root)
        return;
 
    if ( strcmp(root->word, "$") != 0 && root->word[0] != '$')
    {
        outFile << root->word << ": " << str << " " << strlen(str.c_str()) << "\n";
        outFile1 << str << "\n";
    }
 
    printTree(root->left, str + "0", outFile, outFile1);
    printTree(root->right, str + "1", outFile, outFile1);
}
 
void HuffmanCodes(char word[][100], int freq[], int size, ofstream &outFile, ofstream &outFile1)
{
    struct MinHeapNode *left, *right, *top;
 
    priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;
    for (int i = 0; i < size; ++i)
        minHeap.push(new MinHeapNode(word[i], freq[i]));
 
    while (minHeap.size() != 1)
    {
        left = minHeap.top();
        minHeap.pop();
 
        right = minHeap.top();
        minHeap.pop();
 
        char a = '$'; 
        top = new MinHeapNode(&a, left->freq + right->freq);
        top->left = left;
        top->right = right;
        minHeap.push(top);
    }
 
    printTree(minHeap.top(), "", outFile, outFile1);
}
 
int main()
{
    ifstream inFile("input");
    ofstream outFile1("encoded", ios::app);
    map<string, int> maps;
    string word;
    map<string, int>::iterator it;
    ofstream outFile("output", ios::app); 
    while (inFile >> word)
    {
        if ( maps.count( word ) == 0 )
        {
            maps[word] = 1;
        }
        else
            maps[word] = maps[word] + 1;
    }
    sizeMap = maps.size();

    for ( it = maps.begin(); it != maps.end(); ++it )
    {
        outFile << it->first << "  " << it->second << "\n";
    }

    char arr[sizeMap][100];
    int freq[sizeMap];
    int count = 0;
    for ( it = maps.begin(); it != maps.end(); ++it )
    {
        const char *charTmp = (it->first).c_str();
        char *charTmp1 = strdup(charTmp);
        strcpy(arr[count], charTmp1);
        freq[count] = it->second;
        count++;
        free(charTmp1);
    }

    int size = sizeof(arr) / sizeof(arr[0]);
    HuffmanCodes(arr, freq, size, outFile, outFile1);
    outFile1.close(); 
    inFile.close();
    outFile.close();
    string tmpWord, tmpBinary, tmpLength, tmpFreq;
    count = 0;
    string encoded;
    ifstream inFileE("encoded");
    ifstream inFileD("output");
    ofstream outFile_("decoded", ios::app);
    // Dear Prof. Part D - Commented - it will generate the correct message but not in the form of input because the input has been modified by the huffman tree.
    /*while ( inFileE >> encoded )
    {
        while ( !inFileD.eof() )
        {
            if ( count != size )
            {
                inFileD >> tmpWord >> tmpFreq;;
                count++;
                continue;
            }
            inFileD >> tmpWord >> tmpBinary >> tmpLength;
            cout << tmpWord << " " << tmpBinary << " " << tmpLength << " " << "\n";
            if (tmpBinary == encoded)
                outfile_ << tmpWord << "\n";
        }
    }*/
    return 0;
}
