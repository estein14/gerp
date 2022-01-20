/*
    hash.cpp
    Emmett Stein
    
    Class type: Hash Table Class used to index millions of words from a large 
                file database for quick searches and printing. User inputs word 
                and all the lines in which it appears are printed.
    Holds functions for Hash class
 */
 
 #include "stripAndlower.h"
 #include "hash.h"
 #include "index_dir.h"
 
 
 /* 
  * Line constructor
  * Passes in word and index in file store
  * Only used once per word, if already created, adds word to lines vector
  */
 hash::Line::Line(std::string word, int place) {
   this->word = word;
   this->placement = place;
 }
 
 
 /*
  * Hash function
  * Input string, output index/value
  */
 int hash::inputKey(std::string input) {
   int result = std::hash<std::string>{}(input);
   return abs(result % 20000);
 }
 
 
 /*
  * Arguments: word and index in file_holder
  * At index in hashtable, add word and its index in file vector
  * Return: none
  */
 void hash::add_line(std::string word, int place) {
   int value = inputKey(word);
   int x     = 0;

   Line to_add(word, place);
   this->vec.at(value).push_back(to_add);
 }
 
 
 /*
  * Argument: word to print out lines
  * Goes to hashtable at key/value, iterates through lines until word matches
  * struct word. Once found, prints out all lines with index from word struct
  * Return: all lines from word as string.
  */
 std::string hash::print_line(std::string key) {

   std::stringstream s;
   int value = inputKey(key);
   int p;
   
   if (vec.at(value).size() == 0) {
     return "";
   } else {
     for (int i = 0; i < vec.at(value).size(); i++) {
       if (vec.at(value).at(i).word == key) {
            p = vec.at(value).at(i).placement;
            s << line_storage.at(p) << "\n";
       }
     }
  std::string str = s.str();
  return str;
   }
 }
 
 
 /*
 * Constructor for index
 * Argument: Directory to pass in
 * Reads through directory, assigning keys to words and then adding in 
 * full sentence (once per word, no repeats)
 * Depending on bool, either case sensative or not.
 * Returns: none (Fills array in hash & subsequent vectors)
 */
hash::hash(const std::string &dir, bool sensative) {
 
  //keeps place in vector of actual lines 
  this->storage_index = 0;
  
  //create array of file names
  std::vector<std::string> files;
  files = index_dir(dir);
  
  std::stringstream  s;
  int                line_num;
  std::string        word;
  std::istringstream line_stream;

  std::vector<std::string> adding;
  bool in_line = false;
  
  
  //iterate through files
  for (int i = 0; i < files.size(); i++) {
    std::ifstream file(files.at(i).c_str());
    std::string   line;
    line_num = 0;
    
    //get the line and splice it up
    while (getline(file, line)) {
      line_num++;
      
      //if not blank line 
      if (stripNonAlphaNum(line) != "") {
        s << files.at(i);
        s << ":" << line_num << ": " << line;
        std::string str = s.str();
        
        // put line in vector for lines, and then uses index to get line
        line_storage.push_back(str);
        storage_index++;
        
        line_stream.str(line);
        while (line_stream >> word) {
          
          std::string add_word = stripNonAlphaNum(word);
          in_line = false;
          
         //different case for sensative or insensitive
         if (sensative) {
           for (int i = 0; i < adding.size(); i++) {
             if (makeLowerCase(adding.at(i)) == makeLowerCase(add_word)) {
               in_line = true;
             }
           }
         } else {
              for (int i = 0; i < adding.size(); i++) {
                if (adding.at(i) == add_word) {
                  in_line = true;
                }
              }
           }
         if (!in_line) {
           adding.push_back(add_word);
         }
           in_line = false;
        }
          // adds word and the index of that line in file_holder
          for (int i = 0; i < adding.size(); i++) {
             if (sensative) {
               std::string lower = makeLowerCase(adding.at(i));
               this->add_line(lower, storage_index - 1);
             } else {
               this->add_line(adding.at(i), storage_index - 1);
             }
          }
      }
     //clear before new line
     adding.clear();
     s.str(std::string());
     line_stream.clear();
    }
   file.close();
  }
}
 