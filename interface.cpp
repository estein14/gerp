/*
    Emmett Stein
    interface.cpp 
    
    Main interface for user for gerp
*/

#include "hash.h"
#include "stripAndlower.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

const std::string CASE_SENS = "@i";
const std::string QUIT = "@q";


int main(int argc, char *argv[]) {
  
  if (argc < 2) {
      std::cerr << "ERROR: Expecting another file." << std::endl;
      exit(EXIT_FAILURE);
  }
  
  //create index for case/non sens in HASH table
  hash regular(argv[1], false);
  hash sensative(argv[1], true);
    
  std::cout << "Query? ";
  std::string query;
  
  // while user inputs query
  while (std::cin >> query) {
    
    if (query == CASE_SENS) {
      std::string word;
      std::cin >> word;
      
      std::string full_word = stripNonAlphaNum(word);
      std::string to_search = makeLowerCase(full_word);
      std::string printer = sensative.print_line(to_search);
      
      if (printer != "") {
        std::cout << printer;
        std::cout << std::endl;
      
      } else {
        std::cout << to_search;
        std::cout << " Not Found.";
        std::cout << std::endl;
      }
      
    } else if (query == QUIT) {
      std::cout << "Goodbye! Thank you and have a nice day.\n";
      return 0;
      
    } else if (query == "\n") {
      std::cout << " Not Found. Try case insensitive search with @i.";
      std::cout << std::endl;
      
    } else {
      std::string search = stripNonAlphaNum(query);
      std::string to_print = regular.print_line(search);
      
      if (to_print != "") {
        std::cout << to_print;
        std::cout << std::endl;
        
      } else {
        std::cout << search;
        std::cout << " Not Found. Try case insensitive search with @i.";
        std::cout << std::endl;
      }
    }
    std::cout << "Query? ";
  }
  return 0;
}



