/*
    stripAndlower.h
    Emmett Stein
 
    houses function to convert to alpha_numeric and lowercase 
 */



#include <string>
#include <sstream>


/*
 * Argument: string
 * Deletes anything besides middle alphanumerics
 * Returns: new string
 */
inline std::string stripNonAlphaNum(std::string string) {
  if (string == "" or string == "\n") {
    return "";
  }

  int size = string.size();
  std::stringstream s;
  int start = 0;
  
  while (start < size) {
    if ((string[start] > 47 and string[start] < 58) or 
        (string[start] > 64 and string[start] < 91) or 
        (string[start] > 96 and string[start] < 123)) {
      break;
    }
    start++;
  }
  
  int end = size;
  
  while (end > 0) {
    if ((string[end] > 47 and string[end] < 58) or 
        (string[end] > 64 and string[end] < 91) or 
        (string[end] > 96 and string[end] < 123)) {
      break;
    }
    end--;
  }
  
  for (int i = start; i < end + 1; i++) {
    s << string[i];
  }
  
  std::string str = s.str();
  
  return str;
}

/*
 * Argument: string
 * Iterates through and makes lower case
 * Returns: lowercase string
 */
inline std::string makeLowerCase(std::string string) {
  if (string == "") {
    return "";
  }
  std::stringstream s;
  char letter;
  
  for (int i = 0; i < string.size(); i++) {
    if (string[i] > 64 and string[i] < 91) {
      letter = string[i] + 32;
      s << letter;
    } else {
      s << string[i];
    }
  }
  
  std::string str = s.str();
  
  return str;
}