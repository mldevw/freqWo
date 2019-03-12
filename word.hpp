/*
  part of freqWo - Parses texts and outputs the frequency of single words
  mldevw for public audience

  Definition of word class representing a {word, frequency} pair
*/

#include <string>

class word
{
public:
              word(std::string eword);
  std::string getWord();
  uint64_t    getFrequency();
  void        addOccurence();
  bool        operator<(word & w2){return getFrequency()>w2.getFrequency();}
private:
  std::string iword;
  uint64_t    ifrequency;
};
