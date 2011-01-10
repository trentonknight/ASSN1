#include <cstdlib>
#include <cstdio>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <fstream>
#include <cstring>

using namespace std;

struct NODES{
  string word;
  NODES* forward;
  NODES* backwards;
};

void openFILE(ifstream& file);

int main(){
  string word = "hi how are you.";
  ifstream grabFILE;  

  NODES *arrayOfPointers[26] = {0};
  arrayOfPointers[26] = new NODES;
  openFILE(grabFILE);
  if(grabFILE.is_open()){
    cout << "file opened..." << endl;
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
