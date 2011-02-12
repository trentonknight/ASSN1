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
  NODES* fore;
  NODES* back;
};

const int ALPHA = 25;
void openFILE(ifstream& file);
string cleanUPIO(string word);
string upperCASE(string wordIN);
bool verifyIO(ifstream& file);
void PUSH(NODES** first, NODES** last,string word);
void makeNULL(NODES **newNode);

int main(){
 NODES *first[ALPHA] = {0};
 NODES *last[ALPHA] = {0};
 first[ALPHA] = new NODES;
 last[ALPHA] = new NODES; 
  
  ifstream grabFILE;
  string word;
  bool ver = true;

  openFILE(grabFILE);
  if(grabFILE.is_open()){
    while(grabFILE && ver){
      grabFILE >> word;
      word = cleanUPIO(word);
      word = upperCASE(word);
      PUSH(first,last,word);
      ver = verifyIO(grabFILE);
    }
  }
  cout << "test." << endl;
  
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
void PUSH(NODES** first, NODES** last, string word){
  int index = 0, wordSIZE = 0;
  wordSIZE = word.length();
  NODES *newNODE[ALPHA] = {0};
 

  if(wordSIZE > 0){
    index = word[0] - 'A';
    ///create fresh node to add to chosen indexed list
    newNODE[index] = new NODES;
    newNODE[index]->word = word;
    newNODE[index]->back = 0;
    newNODE[index]->fore = 0;

    if(first[index] == NULL){
      ///kickoff this particular index with both pointers to same node
      first[index] = newNODE[index];
      last[index] = newNODE[index];
    }
    else{ 
      ///begin expanding this indexed letter's list 
      while(last[index] != 0){
        ///secure the previous node before moving pointer forward
        first[index] = last[index];
        ///move forward one
	last[index] = last[index]->fore;
      }
      ///get some memory for node
      last[index] = new NODES;
      ///pass new node with latest string to last
      first[index]->fore = newNODE[index];     
      last[index] = newNODE[index];
      ///grab previous node with first
      last[index]->back = first[index];
    }
  }
}

