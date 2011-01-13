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
bool antiNUMBERS(string wordIN);
string characterCHECK(string wordIN);
string formatWORDS(string wordIN);


int main(){
  string word;
  ifstream grabFILE; 
  bool removeNUM = true; 

  NODES *arrayOfPointers[26] = {0};
  arrayOfPointers[26] = new NODES;
  openFILE(grabFILE);
  if(grabFILE.is_open()){
    while(grabFILE){
      grabFILE >> word;
      removeNUM = antiNUMBERS(word);
      if(removeNUM){
      word = characterCHECK(word);
      word =  formatWORDS(word);
      cout << "Approved word: " << word << endl;
      }
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
bool antiNUMBERS(string wordIN){
 int count = 0;
 bool noNUMBERS = true;
 int wordLENGTH = wordIN.length();///get length of individual words
  while(wordLENGTH != 0){///set for end of word halt
    if(isdigit(wordIN[count])){
      noNUMBERS = false;
    }
  count++;///increment to count through each character in the array
  --wordLENGTH;///halts when end of word is reached
  } 
  return noNUMBERS;
}
string characterCHECK(string wordIN){
  int count = 0, index = 0;
 int wordLENGTH = wordIN.length();///get length of individual words
 string *pt = 0;
 char wordOUT[wordLENGTH];
  
  while(wordLENGTH != 0){///set for end of word halt
    if(isalpha(wordIN[count])){
      wordOUT[index] = wordIN[count];
      index++;
    }
    else{
      pt = new string[1];
      *pt = wordIN[count];
      wordIN[count] = wordIN[count + 1];
      delete [] pt;
    }
  count++;///increment to count through each character in the array
  --wordLENGTH;///halts when end of word is reached
  } 
  wordIN((LPCTSTR)wordOUT);
  wordIN(wordLENGTH, index)
  return wordIN;
}
string formatWORDS(string wordIN){
  int count = 0;
  int wordLENGTH = wordIN.length();///get length of individual words
  while(wordLENGTH != 0){///set for end of word halt
  wordIN[count] = toupper(wordIN[count]);///set each character in array to uppercase
  count++;///increment to count through each character in the array
  --wordLENGTH;///halts when end of word is reached
  }
  return wordIN;
}



