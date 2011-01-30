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
NODES *insertNODE(LIST** list, NODES** newNODE,string word);

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
      insertNODE(list,newNODE,word);
      ver = verifyIO(grabFILE);
    }
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
NODES *insertNODE(LIST** list, NODES** newNODE,string word){
  int index = 0, wordSIZE = 0;
  wordSIZE = word.length();

  if(wordSIZE > 0){
    index = word[0] - 'A';
    newNODE[index] = new NODES;
    list[index] = new LIST;
    newNODE[index]->word = word;

    if(list[index]->lastNODE == NULL){
      list[index]->firstNODE = newNODE[index];
      list[index]->lastNODE = newNODE[index];
    }  
    else{
      list[index]->lastNODE->forward = newNODE[index];
      list[index]->lastNODE = newNODE[index];
    }
  }
  return list[index]->firstNODE;
}
