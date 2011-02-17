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
void outputLISTS(NODES** last,int unique,int duplicate,string filename);
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
///  FUNCTION:    Name of function
///  DESCRIPTION:    Description of purpose of function
///  INPUT:
///      Parameters: Name and description of each input parameter
///      File:      Brief description of data read from file
///  OUTPUT:   
///      Return Val: Description of data returned by a function
///      Parameters: Name and description of the output parameters
///      File:    Brief description of data written to file
///  CALLS TO:  List of programmer-written functions called (names only)
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
///  FUNCTION:    Name of function
///  DESCRIPTION:    Description of purpose of function
///  INPUT:
///      Parameters: Name and description of each input parameter
///      File:      Brief description of data read from file
///  OUTPUT:   
///      Return Val: Description of data returned by a function
///      Parameters: Name and description of the output parameters
///      File:    Brief description of data written to file
///  CALLS TO:  List of programmer-written functions called (names only)
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
///  FUNCTION:    Name of function
///  DESCRIPTION:    Description of purpose of function
///  INPUT:
///      Parameters: Name and description of each input parameter
///      File:      Brief description of data read from file
///  OUTPUT:   
///      Return Val: Description of data returned by a function
///      Parameters: Name and description of the output parameters
///      File:    Brief description of data written to file
///  CALLS TO:  List of programmer-written functions called (names only)
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
///////////////////////////////////////////////////////////////////////////
///  FUNCTION:    Name of function
///  DESCRIPTION:    Description of purpose of function
///  INPUT:
///      Parameters: Name and description of each input parameter
///      File:      Brief description of data read from file
///  OUTPUT:   
///      Return Val: Description of data returned by a function
///      Parameters: Name and description of the output parameters
///      File:    Brief description of data written to file
///  CALLS TO:  List of programmer-written functions called (names only)
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
        ///now move forward one traversing backwards
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
      last[index]->front = first[index];
    }

}
///////////////////////////////////////////////////////////////////////////
///  FUNCTION:    Name of function
///  DESCRIPTION:    Description of purpose of function
///  INPUT:
///      Parameters: Name and description of each input parameter
///      File:      Brief description of data read from file
///  OUTPUT:   
///      Return Val: Description of data returned by a function
///      Parameters: Name and description of the output parameters
///      File:    Brief description of data written to file
///  CALLS TO:  List of programmer-written functions called (names only)
//////////////////////////////////////////////////////////////////////////
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
