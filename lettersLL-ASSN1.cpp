#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>
#include <stdio.h>
#include <string.h>
#include <cstring>

using namespace std;

struct NODES{
  string word;
  NODES* forward;
  NODES* backwards;
};

void openFILE(ifstream& file);
string cleanUPIO(string word);
string upperCASE(string wordIN);
bool verifyIO(ifstream& file);
NODES *addWordsToCorrectDoubleLinkedList(NODES **current,string wordDLL);
void printNODES(NODES *newNode);

int main(){
  NODES *nodeARRAY[26] = {0};
  *nodeARRAY = new NODES;
  ifstream grabFILE;
  string word;
  bool ver = true;

  openFILE(grabFILE);
  if(grabFILE.is_open()){
    while(grabFILE && ver){
      grabFILE >> word;
      word = cleanUPIO(word);
      word = upperCASE(word);
      *nodeARRAY = new NODES;
      addWordsToCorrectDoubleLinkedList(nodeARRAY,word);
      ver = verifyIO(grabFILE);
    }
    printNODES(*nodeARRAY);    
  }
  
}
void openFILE(ifstream& file){
  string filename;

  cout << "Enter file name: " << endl;
  cin >> filename;
  file.open(filename.c_str(), ios::binary);
  if(!file){
    cout << "Whoops! file not found? Try again." << endl;
    openFILE(file);
  }
}
bool verifyIO(ifstream& file){

  bool check = true;
  ios::iostate i;

  i = file.rdstate();
  
  if(i & ios::eofbit|| i & ios::failbit || i & ios::badbit){
    check = false;
  }

  return check;
}
string cleanUPIO(string word){
  size_t first, numbers;

    numbers=word.find_first_of("1234567890");
    while(numbers!=string::npos)
    {
      word.erase();
      numbers=word.find_first_of("1234567890");
    }
    first=word.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-'");
    while(first!=string::npos)
    {
      word.erase(first, 1);
      first=word.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-'");
    }
    return word;
  }
string upperCASE(string wordIN){
  int count = 0;
  int wordLENGTH = wordIN.length();

  while(wordLENGTH != 0){
  wordIN[count] = toupper(wordIN[count]);
  count++;
  --wordLENGTH;
  }
  return wordIN;
}

NODES *addWordsToCorrectDoubleLinkedList(NODES **current,string wordDLL){
  NODES *head[26] = {0};
  *head = new NODES;
  NODES *tail[26] = {0};

  *tail = new NODES;
  *head = *current;
  *tail = *current;  

  int wordSIZE = 0, letter = 0;
  wordSIZE = wordDLL.length();
  
  if(wordSIZE > 0){
    letter = wordDLL[0] - 'A';
    while(current[letter] != 0){
      current[letter] = current[letter]->forward;
    }
    current[letter] = new NODES;
    current[letter]->word = wordDLL;
    if(tail[letter] == 0){
    current[letter]->backwards = 0;
    current[letter]->forward = head[letter];
    head[letter] = current[letter];
    }

  }
  return *current;
}
void printNODES(NODES newNode[]){
 
 

}
