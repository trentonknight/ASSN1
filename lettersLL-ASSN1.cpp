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
void cleanUPIO(ifstream& file);
bool verifyIO(ifstream& file);

int main(){
  ifstream grabFILE;
  

  NODES *arrayOfPointers[26] = {0};
  *arrayOfPointers = new NODES;
  openFILE(grabFILE);
  if(grabFILE.is_open()){
    cleanUPIO(grabFILE);
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
void cleanUPIO(ifstream& file){
  string word;
  bool ver = true;
  size_t first, numbers;

    while(file && ver){
    file >> word;
    numbers=word.find("1234567890");
    while(numbers!=string::npos)
    {
      word.erase();
      file >> word;
      numbers=word.find("1234567890");
    }
    first=word.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
    while(first!=string::npos)
    {
      word.erase(first, 1);
      first=word.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
    }
    cout << word << endl;
    ver = verifyIO(file);
    }
   }


