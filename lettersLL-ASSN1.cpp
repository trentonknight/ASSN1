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
bool verifyIO(ifstream& file);

int main(){
  char ch;
  ifstream grabFILE;
  bool ver = true; 

  NODES *arrayOfPointers[26] = {0};
  *arrayOfPointers = new NODES;
  openFILE(grabFILE);
  if(grabFILE.is_open()){
    while(grabFILE && ver){
      grabFILE.get(ch);
      if(isalpha(ch)){
      ch = toupper(ch);
      cout << ch << endl;
      }
      else if(ch == ' '){
       cout << ch << endl;
      }
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
