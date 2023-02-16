#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords){

		std::set<std::string> newset;
		std::string curword;
		//a container and a string
		 for (int i = 0; i <= rawWords.length(); i++) {
			 //iterate through the word to see if every letter is valid
			 //if so add it to our string
			 if (i < rawWords.length() && isalpha(rawWords[i])) {
            curword = curward+ rawWords[i];
        } else {
					//when i acives to the end, check if we have two letters
					//if so add it to our set
            if (curword.length() >= 2)
                newset.insert(curword);
            curword.clear();
        }
    }
    return newset;


{










}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
