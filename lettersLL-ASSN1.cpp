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
struct LIST{
  NODES* firstNODE;
  NODES* lastNODE;
};

void openFILE(ifstream& file);
string cleanUPIO(string word);
string upperCASE(string wordIN);
bool verifyIO(ifstream& file);
void insertEND(LIST** list, NODES** newNODE,string word);
void insertBEGIN(LIST** list, NODES** newNODE,int& index);
void insertAFTER(LIST** list, NODES** last, NODES** newNODE,int& index);
void insertBEFORE(LIST** list,NODES** next,NODES** newNODE,int& index);

int main(){
  NODES *newNODE[26] = {0};
  LIST *list[26] = {0};
  ifstream grabFILE;
  string word;
  bool ver = true;

  openFILE(grabFILE);
  if(grabFILE.is_open()){
    while(grabFILE && ver){
      grabFILE >> word;
      word = cleanUPIO(word);
      word = upperCASE(word);
      insertEND(list,newNODE,word);
      ver = verifyIO(grabFILE);
    }
  }
  cout << "END." << endl;
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
void insertEND(LIST** list, NODES** newNODE,string word){
  int index = 0, wordSIZE = 0;
  NODES *last[26] = {0};

  wordSIZE = word.length();
  if(wordSIZE > 0){
    index = word[0] - 'A';
    newNODE[index] = new NODES;
    list[index] = new LIST;
    newNODE[index]->word = word;
    if(list[index]->lastNODE == NULL){
      insertBEGIN(list,newNODE,index);
    }  
    else{
      *last = new NODES;
      last[index] = list[index]->lastNODE;
       insertAFTER(list,last,newNODE,index);
     }
   }
 }
 void insertBEGIN(LIST** list,NODES** newNODE,int& index){
   NODES *next[26] = {0};
   *next = new NODES;
  
   if(list[index]->firstNODE == 0){
     list[index]->firstNODE = newNODE[index];
     list[index]->lastNODE = newNODE[index];
     newNODE[index]->backwards = 0;
     newNODE[index]->forward = 0;
   }
   else{
     next[index] = list[index]->firstNODE;
     insertBEFORE(list,next,newNODE,index);
  }
}

void insertAFTER(LIST** list,NODES** last, NODES** newNODE,int& index){
  newNODE[index]->backwards = last[index];
  newNODE[index]->forward = last[index]->forward;
  if(last[index] == NULL){
    list[index]->lastNODE = newNODE[index];
  }
  else{
    last[index]->forward = newNODE[index];
  }
  last[index]->forward = newNODE[index];
}
void insertBEFORE(LIST** list,NODES** next,NODES** newNODE,int& index){
  next[index] = new NODES;
  newNODE[index]->backwards = next[index]->backwards;
  newNODE[index]->forward = next[index];
  if(next[index] == 0){
    list[index]->firstNODE = newNODE[index];
  }
  else{
    next[index]->forward = newNODE[index];
  }
   next[index]->backwards = newNODE[index];
}


