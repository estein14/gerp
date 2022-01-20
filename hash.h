/*
    hash.h
    Emmett Stein
    
    House class for Hash functionality
 
 */
 
#ifndef HASH_H
#define HASH_H
 
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

 
class hash{
  
  struct Line{
    std::string word;
    int placement;
  public:
    //to use to manually construct new line in hash
    Line(std::string word, int place);
  };
   
   
public:
    hash(const std::string &dir, bool sensative);
    int inputKey(std::string input);
    void add_line(std::string word, int place);
    std::string print_line(std::string key);
   
private:
   std::vector<std::vector<Line>> vec = std::vector<std::vector<Line>>(20000);
   std::vector<std::string> line_storage;
   int storage_index;
};
 

#endif