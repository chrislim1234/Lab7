// wscramble.cpp
// Word Scramble guessing game
// Illustrates string library functions, character arrays,
//  arrays of pointers, etc.
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <fstream>

using namespace std;

// Scramble the letters of this string randomly
void permute(char items[], int len);

/* Delete the array below and replace by reading in words from a file 
   in main() */


int main(int argc, char* argv[]) {
 
  //declare numwords
  int numWords;
  srand(time(0));
  char guess[80];

  bool wordGuessed = false;
  int numTurns = 10;
    
    
    ifstream ifile(argv[1]);
    if(argc != 2){
        //return false if there are less or more than 2 arguments inputted
        cout << "false"<<endl;
        return 1;
    }
    if(ifile.fail()){
       cout<<"Could not open file."<<endl;
       return 1;
    }
        
    ifile >> numWords;
    if(ifile.fail()){
            //check if file can be opened
            cout << "Couldn't open file" << endl;
            return -1;
    }
    
    char** wordBank = new char*[numWords];
    char buffer[41];
    for(int i = 0; i < numWords;i++){
        ifile>>buffer;
        int len = strlen(buffer);
        wordBank[i] = new char[len+1];
        strcpy(wordBank[i], buffer);
    }
    
         
   
    
    ifile.close();
    
  /* Add code to declare the wordBank array, read in each word
     and store it */

    
  // Pick a random word from the wordBank
  int target = rand() % numWords;
  int targetLen = strlen(wordBank[target]);

  // Make a dynamically-allocated copy of the word and scramble it
  char* word = new char[targetLen+1];
  strcpy(word, wordBank[target]);
  permute(word, targetLen);
  
  // An individual game continues until a word
  //  is guessed correctly or 10 turns have elapsed
  while (!wordGuessed && numTurns > 0) {
    cout << "Scrambled word: " << word << endl;
    cout << "What do you guess the original word is? ";
    cin >> guess;
    /* Complete the next line of code */
      
    wordGuessed = false;// ADD code to check if the guess is equal to the chosen word.
                  // wordGuessed should be true if they are equal, and false otherwise
      int compare = strcmp(guess, wordBank[target]);
      
      if(compare==0){
           wordGuessed = true;   
      }
        
    numTurns--;   // Every guess counts as a turn
  }
  if (wordGuessed) {
    cout << "You win!" << endl;
  }
  else {
    cout << "Too many turns...You lose!" << endl;
  }
  /* Free up any necessary memory */
  for(int i = 0; i<numWords; i++){
      delete [] wordBank[i];   
  }
  delete [] wordBank;
    
  delete [] word;
  return 0;
}

// Scramble the letters. See "Knuth shuffle".
void permute(char items[], int len) {
  for (int i = len-1; i > 0; --i) {
    int r = rand() % i;
    char temp = items[i];
    items[i] = items[r];
    items[r] = temp;
  }
}


