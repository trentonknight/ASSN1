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
void addWordsToCorrectDoubleLinkedList(string wordDLL);

int main(){
  ifstream grabFILE;
  string word;
  bool ver = true;

  NODES *arrayOfPointers[26] = {0};
  *arrayOfPointers = new NODES;
  openFILE(grabFILE);
  if(grabFILE.is_open()){
    while(grabFILE && ver){
      grabFILE >> word;
      word = cleanUPIO(word);
      word = upperCASE(word);
      addWordsToCorrectDoubleLinkedList(word);
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

void addWordsToCorrectDoubleLinkedList(string wordDLL){
  ///dont forget to check length of each string words = 0
  ///do not get added to a list

}
