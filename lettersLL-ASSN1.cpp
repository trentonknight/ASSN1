#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

struct NODES{
  string word;
  NODES* back;
  NODES* front;
};

const int ALPHA = 26;
void openFILE(ifstream& file,string filename);
string cleanUPIO(string word);
string upperCASE(string wordIN);
string lowerCASE(string wordIN);
bool noDUPLICATES(NODES** last,string word);
void PUSH(NODES** first, NODES** last,string word);
void outputLISTS(NODES** last,int unique,int duplicate,string filename);

int main(){
 NODES *first[ALPHA] = {0};
 NODES *last[ALPHA] = {0};

  ifstream grabFILE;
  string word = "\0",filename = "\0";
  bool dupWORD = true;
  int unique = 0, duplicate = 0;

  openFILE(grabFILE,filename);
  if(grabFILE.is_open()){
    while(grabFILE){
      grabFILE >> word;
      word = cleanUPIO(word);
      if(word.length() > 0){
      word = upperCASE(word);
      dupWORD = noDUPLICATES(last,word);
      if(dupWORD == true){
      PUSH(first,last,word);
      unique++;
      }
      else{
      duplicate++;
      }
      }
    }
  }
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
string lowerCASE(string wordIN){
  int count = 0;
  int wordLENGTH = wordIN.length();

  while(wordLENGTH != 0){
    wordIN[count] = tolower(wordIN[count]);
    count++;
    --wordLENGTH;
  }
  return wordIN;
}
bool noDUPLICATES(NODES** last,string word){
  bool nodup = true;
  int index = 0;
  NODES *dupNODE[ALPHA] = {0};
  index = word[0] - 'A';
  dupNODE[index] = new NODES;
  dupNODE[index] = last[index];
  ///traverse to bottom opf list forwards
  while(dupNODE[index] != 0 && nodup){ 
    if(dupNODE[index]->word == word){
      nodup = false;
      delete *dupNODE;
    }
    dupNODE[index] = dupNODE[index]->back;
  }
  if(nodup){
  delete *dupNODE;
  *dupNODE = *last;
  while(dupNODE[index] != 0 && nodup){ 
    if(dupNODE[index]->word == word){
      nodup = false;
    }
    dupNODE[index] = dupNODE[index]->front;
  }
  }
  return nodup;
}
void PUSH(NODES** first, NODES** last, string word){
  int index = 0;
  NODES *newNODE[ALPHA] = {0};
 

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
        ///now move forward one traversing backwards
	last[index] = last[index]->back;
      }
      ///pass new node with latest string to backwards pointer
      ///*first->back = "0x0" <-[newNODE]-> "0x0"
      first[index]->back = newNODE[index];     
      ///grab previously created and saved node with frontwards pointer
      ///from *first:
      /// prevNODE<-back<-*last->front->newNODE 
      /// |                             |
      /// [word]                        [word]
      last[index] = newNODE[index];  
      last[index]->front = first[index];
    }

}
void outputLISTS(NODES** last,int unique,int duplicate,string filename){

  int listLENGTH = 0,
      alphabet = 0,
      total = unique + duplicate,
      largest = 0;
  string  letter, largeLETTER;
  
  cout << "Results for " << filename << ":" << total << " total words processed." << "\n" << endl; 

  for(alphabet = 0; alphabet < 26; alphabet++){
    listLENGTH = 0;
    if(last[alphabet] != 0){
    while(last[alphabet]->front != 0){
       listLENGTH++;
       last[alphabet] = last[alphabet]->front;
    }
    letter = '"' + alphabet - 3 + '"';
    if(listLENGTH > 0){
      cout << setw(5) << listLENGTH << right <<" words begining with" << setw(7)
           << "'" + lowerCASE(letter) + "'/'" + letter << "':" << endl;
    while(last[alphabet]->back != 0){
       cout << last[alphabet]->word << " " << right;
       last[alphabet] = last[alphabet]->back;
    }
    cout << endl;
    if(listLENGTH > largest){
      largest = listLENGTH;
      largeLETTER = "'" + lowerCASE(letter) + "'/'" + letter;
    }
    else if(listLENGTH == largest){
      largeLETTER.append("\n");
      largeLETTER.append("'" + lowerCASE(letter) + "'/'" + letter);
    }
  }
  }
  }
  cout << "\nThere were " << unique << " unique words in the file."<< endl;
  cout << "The highest word count was " << largest << endl;
  cout << "\nLetter(s) that began words "<< largest <<" times were: " << endl;
  cout << setw(9) << right << largeLETTER << endl;
}
