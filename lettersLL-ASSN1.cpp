#include <iostream>
#include <fstream>
#include <cctype>
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
  char ch;
  char word[15];
  string wordSTRING;
  bool ver = true;
  int index = 0;

    while(file && ver){
      file.get(ch);
      if(isalpha(ch)){
        index++;
        ch = toupper(ch);
        cout << ch;
       
      }
      else if(ch == ' ' || ch == '\n'){
       
	cout << endl;
      }
      ver = verifyIO(file);
    }
}
