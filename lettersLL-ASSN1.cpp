#include <cstdlib>
#include <cstdio>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <fstream>
#include <cstring>
#include <cctype>

using namespace std;

struct NODES{
  string word;
  NODES* forward;
  NODES* backwards;
};

void openFILE(ifstream& file);
string formatWORDS(string wordIN);

int main(){
  string word;
  ifstream grabFILE;  

  NODES *arrayOfPointers[26] = {0};
  arrayOfPointers[26] = new NODES;
  openFILE(grabFILE);
  if(grabFILE.is_open()){
    while(grabFILE){
      grabFILE >> word;
      formatWORDS(word);
      cout << "NEXT WORD:" << endl;
    }
    
  }
  
}
void openFILE(ifstream& file){
  string filename;

  cout << "Enter file name: " << endl;
  cin >> filename;
  file.open(filename.c_str());
  if(!file){
    cout << "Whoops! file not found? Try again." << endl;
    openFILE(file);
  }
}
string formatWORDS(string wordIN){
  string wordOUT;
  int count = 0;
  int wordLENGTH = wordIN.length();
  while(wordLENGTH != 0){
  wordIN[count] = toupper(wordIN[count]);
  cout << wordIN[count];
  count++;
  --wordLENGTH;
  }
  cout << endl;
  return wordOUT;
}
