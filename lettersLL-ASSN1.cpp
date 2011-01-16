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
  string word;
  ifstream grabFILE; 
  bool removeNUM = true; 

  NODES *arrayOfPointers[26] = {0};
  arrayOfPointers[26] = new NODES;
  openFILE(grabFILE);
  if(grabFILE.is_open()){
    while(!grabFILE.eof()){
     grabFILE >> word;
     cout << "word:" << word << endl;
     word.clear();
    }
    grabFILE.close();
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

