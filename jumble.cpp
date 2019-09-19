//
//  main.cpp
//  jumble
//
//  Created by James Rainbolt on 4/22/19.
// jrainb2
//  Copyright © 2019 James Rainbolt. All rights reserved.
//
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iomanip>

/**
 This file contains some toy code which illustrate example
 usage of the standard template library unordered_map class
 among other things.  Some other C++ concepts illustrated
 include:
 
 the std::sort function
 command-line arguments
 opening and reading from files
 the "foreach" construct to iterate over elements
 in an STL "container"
 
 The program itself reads a text file and builds a
 "frequency-count" data structure using an unordered_map.
 
 For each ditsinct string in the input file, the map
 keeps track of the number of time that string appears
 in the file.
 **/


/*
 *  this function rearranged the characters in a string
 *    so that they are sorted (according to their ASCII
 *    value).
 *
 *  Resource:  https://en.cppreference.com/w/cpp/algorithm/sort
 *
 *  Note:  this function is not actually used the the program
 *    in this file.  But you might find it useful... :)
 */
void ssort(std::string &s) {
    
    /*
     strings are "iterable" objects and so have the begin()
     and end() functions.  These functions (in a pretty
     abstract way) return "iterators" which specify the
     "beginning" and "end" of the associated object).
     
     Thus, this call is asking the sort function to sort
     the entire string s.
     */
    std::sort(s.begin(), s.end());
}


/*
 *   usage:   ./jumble <filename>
 *
 *   example:  ./jumble words.txt
 *
 */
int main(int argc, char *argv[]){
    /*
     the variable word2jumble is an unordered_map
     from strings to integers.
     */
    std::unordered_map<std::string, std::vector <std::string> > word2jumble;
    std::ifstream file;
    std::string word;
    int numWords = 0;
    int numClasses = 0;
    int largestClass = 0;
    std::string largestKey = " ";
    std::vector <std::string> largestKeyVec;
    
    if(argc != 2) {
        std::cout << "usage:  ./jumble <filename>\n";
        std::cout << "goodbye\n";
        return 1;
    }
    
    /*
     *  argv[1] is a C-string which is the filname specified
     *    by the user.  Let's try to open it.
     */
    
    file.open(argv[1], std::ios::in);
    
    if(!file.is_open()){
        std::cout << "Error: could not open file '" <<
        argv[1] << "'\n";
        std::cout << "goodbye\n";
        return 1;
    }
    
    std::cout << "reading input file...\n";
    
    while(file >> word) {
        // file >> word;
        //copies the string word into string key
        std::string key(word);
        //sorts the letters of key into ascending alphabetical order.
        ssort(key);
        
        //if the key is not found in the jumble map, then create a new vector v
        //put the word into vector v, and then set the word2jumble at the position "key" to the vector v.
        
        if(word2jumble.count(key)==0){
            std::vector<std::string> v;
            v.push_back(word);
            word2jumble[key] = v;
            numWords++;//increment the total number of workds in word2jumble.
        }
        //if the key is found in the jumble map, then push the word onto the vector at the position of "key" in the word2jumble map.
        else{
            word2jumble[key].push_back(word);
            numWords++;
        }
        //If if largestClass is less than the size of the word at position "key" in the word2jumble mapp, then
        if(largestClass < word2jumble[key].size()){
            largestClass = word2jumble[key].size();
            largestKey = key;
            largestKeyVec = word2jumble[key];
        }
    }
    
    std::cout <<
    "enter a word and I will tell you what I know about it\n";
    std::cout <<
    "  when you are done, type ctrl-d (ctrl-z on windows)\n\n";
    std::cout << "> ";
    
    
    while(std::cin >> word) {
        //each word that is read in from user is copied into a string "key" and then sorted. If the word is not found
        //then a cout statement says it is not found.
        std::string key(word);
        ssort(key);
        if(word2jumble.count(key)==0){
            std::cout << "Not found..." << std::endl;
        }
        //If the word is found, then the vector at the position of "key" in the word2jumble map is printed.
        else{
            std::cout << "English Anagrams Found: " << std::endl;
            for(auto& s : word2jumble[key]){
                //std::cout << "Found:" << std::endl;
                std::cout << s << std::endl;
            }
        }
    }
    // user has quit.  Let's dump the map contents
    //numClasses equals the size of the word2jumble vector
    numClasses = word2jumble.size();
    
    
    //statements that print out the information of the jumble2word unordered map.
    std::cout << "num_words" << std::setw(10) << " : " << numWords << std::endl;
    std::cout << "num_classes" << std::setw(10) << " : " << numClasses << std::endl;
    std::cout << "size-of-largest-class" << std::setw(10) << " : " << largestClass << std::endl;
    std::cout << "largest-class key" << std::setw(10) << " : " << largestKey << std::endl;
    
    std::cout << "contents of the largest key Vector: " << std::endl;
    for(auto& w : word2jumble[largestKey]){
        //std::cout << "Found:" << std::endl;
        std::cout << w << std::endl;
    }
    
    return 0;
}

