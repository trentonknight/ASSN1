#include <iostream>
#include <fstream>
#include <cctype>

using namespace std;

struct NODES{
  string word;
  NODES* forward;
  NODES* backwards;
};

void openFILE(ifstream& file);

int main(){
  char ch;
  ifstream grabFILE; 

  NODES *arrayOfPointers[26] = {0};
  *arrayOfPointers = new NODES;
  openFILE(grabFILE);
  if(grabFILE.is_open()){
    while(grabFILE){
      grabFILE.get(ch);
      if(isalpha(ch)){
      ch = toupper(ch);
      cout << "Approved letter: " << ch << endl;
      }
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
