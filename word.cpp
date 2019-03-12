/*
  part of freqWo - Parses texts and outputs the frequency of single words
  mldevw for public audience

  Definition of word class representing a {word, frequency} pair
*/

#include "word.hpp"

word::word(std::string eword) // initialize
{
  iword = eword;
  ifrequency = 1; // initialize with one, as a word will only get added if it has a prevalence
}

std::string word::getWord()
{
  return iword;
}

uint64_t word::getFrequency()
{
  return ifrequency;
}

void word::addOccurence()
{
  ifrequency++;
}
