/////////////////////////////////////////////////////////////////////////
///CODE FILENAME: Name of file
///DESCRIPTION:   Simple Doubly Linked list which reads and counts the amount
///               of unique words found.
///  DATE:        Date to be turned in
///  DESIGNER:    Jason N Mansfield
///  FUNCTIONS:   openFILE(),cleanUPIO(),upperCASE(),lowerCASE(),noDUPLICATES(),
///               PUSH(),outputLISTS().
/////////////////////////////////////////////////////////////////////////
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
void outputLISTS(NODES** last,string filename,int parsed);
///////////////////////////////////////////////////////////////////////////
///  FUNCTION:   main()
///  DESCRIPTION:  main driver program for all functions
///  INPUT:
///      Parameters:string word is used to hold all words streamed from grabFILE.
///                 dupWORD is boolean and will negate a word from entering any list
///                 due to its being a duplicate.
///                 pointers to arrays *first and *last are used to maintain list of words
///                 *first becomes staggered one node behind *last so *last is used for final 
///                 traversal at the final function used for counting and displaying all full lists.
///                 *first is staggered for holding previous node.
///      File:      ifstream grabFILE streams one word per loop cycle from chosen
///                 document.
///  OUTPUT:   
///      Return Val: returns 0 if run without error
///  CALLS TO: openFILE(),cleanUPIO(),upperCASE(),noDUPLICATES(),
///            PUSH(),outputLISTS().
//////////////////////////////////////////////////////////////////////////
int main(){
 NODES *first[ALPHA] = {0};
 NODES *last[ALPHA] = {0};

  ifstream grabFILE;
  string word = "\0",filename = "\0";
  bool dupWORD = true;
  int parsed = 0;

  openFILE(grabFILE,filename);
  if(grabFILE.is_open()){
    while(grabFILE){
      ///stream new word
      grabFILE >> word;
      ///clean up word
      word = cleanUPIO(word);
      ///if word was not erased continue
      ///towards adding to list
      if(word.length() > 0){
      word = upperCASE(word);
      ///counts total words parsed
      parsed++;
      ///if dupWORD becomes false word will not be added
      ///to list
      dupWORD = noDUPLICATES(last,word);
      if(dupWORD == true){
      ///if word passed all the previous verifications
      ///and clean up add to list
      PUSH(first,last,word);
      }
      }
    }
  }
  ///close document
  grabFILE.close();
  ///count and output info to user
  outputLISTS(last,filename,parsed); 
  return 0;
}
///////////////////////////////////////////////////////////////////////////
///  FUNCTION:   openFILE
///  DESCRIPTION:   simple function which recieves users requested file name and then 
///                 verifies file actually exists.
///  INPUT:
///      Parameters: string filename input from user.
///      File:    nothing is streaming from file function only verifies file name.
///  OUTPUT:   
///      Return Val: returns filename to main otherwise alerts user file
///                  is not found.
///      Parameters: open filename.c_str() returned to main() 
///  CALLS TO:  recursivly calls on itself if filename is wrong openFILE().
//////////////////////////////////////////////////////////////////////////
void openFILE(ifstream& file,string filename){

  cout << "Enter file name: " << endl;
  cin >> filename;
  file.open(filename.c_str(), ios::binary);
  if(!file){
    cout << "Whoops! file not found? Try again." << endl;
    openFILE(file,filename);
  }
}
///////////////////////////////////////////////////////////////////////////
///  FUNCTION:    cleanUPIO
///  DESCRIPTION: will either erase word for containing numbers or will trim off 
///               unwanted special characters by looping through word.
///  INPUT:
///      Parameters: string word 
///  OUTPUT:   
///      Return Val: function will return either an erased string or a cleaned up 
///                  string without unwanted characters
///      Parameters: string word
//////////////////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////////////////
///  FUNCTION:    upperCASE
///  DESCRIPTION: simple loop which goes through string making all characters
///               uppercase
///  INPUT:
///      Parameters: wordIN[] 
///  OUTPUT:   
///      Return Val: wordIN
///      Parameters: wordIN[] now all uppercase via toupper()
//////////////////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////////////////
///  FUNCTION:    lowerCASE
///  DESCRIPTION: simple loop which goes through string making all characters
///               lowercase
///  INPUT:
///      Parameters: wordIN[] 
///  OUTPUT:   
///      Return Val: wordIN
///      Parameters: wordIN[] now all lowercase via tolower()
//////////////////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////////////////
///  FUNCTION:    noDUPLICATES
///  DESCRIPTION: this function traverses through existing list looking for any
///               strings that match the current new string. If a match is found then
///               a boolean false is returned to reject this duplicate string as it would
///               create an undesired duplicate word for this particular program.
///  INPUT:
///      Parameters: NODES** last and string word
///  OUTPUT:   
///      Return Val: true or false boolean value
///      Parameters: boolean nodup
//////////////////////////////////////////////////////////////////////////
bool noDUPLICATES(NODES** last,string word){
  bool nodup = true;
  int index = 0;
  NODES *dupNODE[ALPHA] = {0};
  index = word[0] - 'A';
  dupNODE[index] = new NODES;
  dupNODE[index] = last[index];
  ///traverse to bottom of list forwards
  while(dupNODE[index] != 0 && nodup){ 
    if(dupNODE[index]->word == word){
      nodup = false;
    }
    dupNODE[index] = dupNODE[index]->back;
  }
  if(nodup){
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
///////////////////////////////////////////////////////////////////////////
///  FUNCTION:    PUSH
///  DESCRIPTION: function creates a new NODE and adds new word to it. It then pushes
///               each new NODE to list while maintaining previous NODES forming a doubly linked list.
///               Each list is placed in the appropriate array by finding the first letter of this particular string.
///               For example A = 0, B = 1, C = 2, etc...
///               int index reflects the proper array for this particular list.
///  INPUT:
///      Parameters: NODES** first, last and string word
///                  first: previous node
///                  last: current node
///                  word: current incomming word
///  OUTPUT:   
///      Return Val: NODES** first, last
///      Parameters: first: previous node
///                  last: current node
//////////////////////////////////////////////////////////////////////////
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
        ///traverse backwards
	last[index] = last[index]->back;
      }
      ///pass new node with latest string to backwards pointer
      ///*first->back = "0x0" <-[newNODE]-> "0x0" and 
      ///*first = previous NODE from while loop above
      first[index]->back = newNODE[index];     
      ///grab previously created and saved node with frontwards pointer
      ///from *first:
      /// prevNODE<-back<-*last->front->newNODE 
      /// |                             |
      /// [word]                        [word]
      last[index] = newNODE[index];
      ///after allocating memory grab backwards node from first
      ///which was secured in above while loop.  
      last[index]->front = first[index];
    }

}
///////////////////////////////////////////////////////////////////////////
///  FUNCTION:    outputLISTS
///  DESCRIPTION: function double checks list and counts each node forwards. 
///               After verifying list length; list is traversed once again 
///               backwards for printout of each found word.
///  INPUT:
///      Parameters: NODES** last: contain's all arrays of lists
///                  int parsed: total words parsed
///                  string filename: simply for printing file used to user 
///  OUTPUT:   
///      Return Val: prints information to user.
///      Parameters: string filename: name of file used.
///                  int parsed: number of words actually parsed.
///                  listLENGTH: length of each array of letters.
///                  total: total amount of unique words found.
///                  largest: the largest list or lists found.
///                  letter: the letter of current list being shown.
///                  largeLETTER: the letter or letters with the largest 
///                  count found in document.
///  CALLS TO: lowerCASE()
//////////////////////////////////////////////////////////////////////////
void outputLISTS(NODES** last,string filename,int parsed){

  int listLENGTH = 0,
      alphabet = 0,
      total = 0,
      largest = 0;
  string  letter, largeLETTER;
  
  cout << "Results for " << filename << ":" << parsed << " total words processed." << "\n" << endl; 

  for(alphabet = 0; alphabet < 26; alphabet++){
    listLENGTH = 0;
    if(last[alphabet] != 0){
    while(last[alphabet] != 0){
       listLENGTH++;
       last[alphabet] = last[alphabet]->front;
       total++;    
}
    letter = '"' + alphabet - 3 + '"';
    if(listLENGTH > 0){
      cout << setw(5) << listLENGTH << right <<" words begining with" << setw(7)
           << "'" + lowerCASE(letter) + "'/'" + letter << "':" << endl;
    while(last[alphabet] != 0){
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
  cout << "\nThere were " << total << " unique words in the file."<< endl;
  cout << "The highest word count was " << largest << endl;
  cout << "\nLetter(s) that began words "<< largest <<" times were: " << endl;
  cout << setw(9) << right << largeLETTER << endl;
}
