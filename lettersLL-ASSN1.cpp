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
  NODES* back;
  NODES* front;
};

const int ALPHA = 25;
void openFILE(ifstream& file,string filename);
string cleanUPIO(string word);
string upperCASE(string wordIN);
bool verifyIO(ifstream& file);
bool noDUPLICATES(NODES** last,string word);
void PUSH(NODES** first, NODES** last,string word);
void outputLISTS(NODES** last,int unique,int duplicate,string filename);

int main(){
 NODES *first[ALPHA] = {0};
 NODES *last[ALPHA] = {0};
 first[ALPHA] = new NODES;
 last[ALPHA] = new NODES; 
  
  ifstream grabFILE;
  string word,filename;
  bool ver = true;
  bool dupWORD = true;
  int unique = 0, duplicate = 0;

  openFILE(grabFILE,filename);
  if(grabFILE.is_open()){
    while(grabFILE && ver){
      grabFILE >> word;
      word = cleanUPIO(word);
      word = upperCASE(word);
      ///*last is will contain the final list
      ///*first will be staggered front one NODE after completing the list
      ///and should not be used for other functions
      dupWORD = noDUPLICATES(last,word);
      if(dupWORD == true){
      PUSH(first,last,word);
      unique++;
      }
      else{
      duplicate++;
      }
      ver = verifyIO(grabFILE);
    }
  }
  cout << "test." << endl;
  outputLISTS(last,unique,duplicate,filename);
  
  
}
  
void openFILE(ifstream& file,string filename){

  cout << "Enter file name: " << endl;
  cin >> filename;
  file.open(filename.c_str(), ios::binary);
  if(!file){
    cout << "Whoops! file not found? Try again." << endl;
    openFILE(file,filename);
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
bool noDUPLICATES(NODES** last,string word){
  bool nodup = true;
  int index = 0;
  NODES *dupNODE[ALPHA] = {0};
  NODES *dupNODEbk[ALPHA] = {0};
  index = word[0] - 'A';
  *dupNODE = *last;
  *dupNODEbk = *last;
  ///traverse to bottom opf list forwards
  while(dupNODE[index] != 0){ 
    if(dupNODE[index]->word == word){
      nodup = false;
    }
    dupNODE[index] = new NODES;
    dupNODE[index] = dupNODE[index]->back;
  }
  return nodup;

}
void PUSH(NODES** first, NODES** last, string word){
  int index = 0, wordSIZE = 0;
  wordSIZE = word.length();
  NODES *newNODE[ALPHA] = {0};
 

  if(wordSIZE > 0){
    index = word[0] - 'A';
    ///create fresh node to add to chosen indexed list
    newNODE[index] = new NODES;
    newNODE[index]->word = word;
    newNODE[index]->front = 0;
    newNODE[index]->back = 0;

    if(first[index] == NULL){
      ///kickoff this particular index with both pointers to same node
      first[index] = newNODE[index];
      last[index] = newNODE[index];
    }
    else{ 
      ///begin expanding this indexed letter's list 
      while(last[index] != 0){
        ///secure the previous node before moving pointer forward
        first[index] = last[index];
        ///move forward one
	last[index] = last[index]->back;
      }
      ///get some memory for node
      last[index] = new NODES;
      ///pass new node with latest string to *first forward pointer
      ///and *last:  "0x0" <-["new"]-> "new"
      first[index]->back = newNODE[index];     
      last[index] = newNODE[index];
      ///grab previous node with *last frontwards pointer:
      ///"old" <-["new"]-> "new"
      last[index]->front = first[index];
    }
  }
}
void outputLISTS(NODES** last,int unique,int duplicate,string filename){

  int listLENGTH = 0;
  int alphabet = 0;
  int total = unique + duplicate;
  char letter;
  
  cout << "Results for " << filename << ":" << total << " total words processed." << endl; 

  for(alphabet = 0; alphabet < 26; alphabet++){
    listLENGTH = 0;
    if(last[alphabet] != 0){
    letter = last[alphabet]->word[0];
    while(last[alphabet] != 0){
       listLENGTH++;
       last[alphabet] = last[alphabet]->front;
    }
    if(letter > 0){
    cout << listLENGTH << " words begining with " << letter << endl;
    letter = '\0';
    }
    }
  }
}
