/*
  freqWo - Parses texts and outputs the frequency of single words
  mldevw for public audience
*/

#include <stdio.h>
#include <fstream>
#include <list>
#include "word.hpp"
#include <string>

#include "libmldevw.h"


int   main(int argc, char **argv);
void  parseFile(const char* filename);
void  outputResults(const char* filename, const char* columnsep);
void  foundWord(std::string wrd, std::list<word> *wordlist);

char leaveOutChars[]{'.',',','!','?','-','[',']','{','}',';',':','$','\\','/','"','^','_',')','('};
std::list<word> words;

int main(int argc, char **argv)
{
  printf("############################################################\n");
  printf("### ");printfCenterText("freqWo",60-8); printf(" ###\n");
  printf("### ");printfCenterText("https://github.com/mldevw/freqWo",60-8); printf(" ###\n");
  printf("### ");printfCenterText("calculates frequency of words in text files",60-8); printf(" ###\n");
  printf("### ");printfCenterText("",60-8); printf(" ###\n");
  printf("### ");printfCenterText("mldevw for public audience",60-8); printf(" ###\n");
  printf("### ");printfCenterText(__DATE__,60-8); printf(" ###\n");
  printf("############################################################\n");

  if ((argc<2)||(argc>4)) // if arguments not sufficient...
  {
      printf("freqwo: missing file operand\n");
      printf("Usage: freqwo INPUT_FILE [CSV_OUTPUT_FILE] [CSV_COLUMN_SEPARATION_CHAR]\n");
      printf("Hint: when using CSV_COLUMN_SEPARATION_CHAR escape character may be necessary.\n");
      exit(1);
  }

  parseFile(argv[1]);
  outputResults(argc>2?argv[2]:NULL,argc>3?argv[3]:",");

  return 0;
}

void parseFile(const char* filename)
{
  // test if file is ok
  std::ifstream f; f.open(filename, std::ifstream::in);
  if (!f.is_open()) // file is not accessible -> exit!
  {
    printf("Error opening input file %s\n",filename);
    exit(1);
  }  // file seems accessible.

  // read document word wise
  std::string thisWord = "";
  std::locale iLocale; // for to lower
  while(f >> thisWord)
  {
      uint8_t stillCheck=1;
      uint16_t oldStringLength=0;
      while(stillCheck) // while there might be still some "bad" chars at the borders
        for (uint16_t i=0; i<sizeof(leaveOutChars)/sizeof(leaveOutChars[0]);i++)
        {
          oldStringLength = thisWord.length();

          if (thisWord[0]==leaveOutChars[i]) // get the starting chars
            thisWord.erase(0);

          if (thisWord[thisWord.length()-1]==leaveOutChars[i]) // get the ones at the end
            thisWord.erase(thisWord.length()-1);

          stillCheck=(thisWord.length()!=oldStringLength); // if something was found, check again
        }

      // word to lower case
      for (char &c:thisWord) c=std::tolower(c);
      if (thisWord.length())foundWord(thisWord,&words);
  }

  f.close();
}

void foundWord(std::string wrd, std::list<word> *wordlist)
{
  for (std::list<word>::iterator i = wordlist->begin(); i!= wordlist->end(); i++)
  {
    word &w = *i;
    if (w.getWord().compare(wrd)==0) // if word is already saved, add occurence
    {
      w.addOccurence();
      return;
    }
  }

  // Code only reaches this if word has not been foundWord
  // -> create new word
  word w = word(wrd);
  wordlist->push_back(w);
}

void outputResults(const char* filename, const char* columnsep)
{
  words.sort(); // Sort the list
  if (filename==NULL) // print to screen
  {
    printf("\nReport:\n");
    printf("%-50s %3s\n","Word","Frequency");
    printf("------------------------------------------------------------\n");

    for (word w:words) // Output words with descending frequency
      printf("%-56s %3" PRId64 "\n",w.getWord().c_str(),w.getFrequency());
  }
  else // file to be exported
  {
    printf("Output will be written to %s\n",filename);
    std::ofstream f; f.open(filename, std::ofstream::out);
    if (!f.is_open()) // file is not accessible -> exit!
    {
      printf("Error opening output file %s\n",filename);
      exit(1);
    }  // file seems accessible.

    f << "freqWo" << columnsep << "\n";
    f << "https://github.com/mldevw/freqWo" << columnsep << "\n";
    f << "Word" << columnsep << "Frequency" << columnsep << "\n";
    for (word w:words) // Output words with descending frequency
      f << w.getWord() << columnsep << w.getFrequency() << columnsep << "\n";

    f.close();
  }
}
