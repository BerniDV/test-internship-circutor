#include <iostream>
#include <map>
#include "../headers/TextFormatter.h"

int main(){

    std::string input = "";

    std::string temp;

    //get all the lines from an input and replace the line break with spaces
    bool firstIteration = true;
    while(std::getline(std::cin, temp)){

        (firstIteration) ? input += temp : input += " " + temp;

        if(firstIteration){

            firstIteration = false;
        }
    }

    //Create text formatter object to encapsulate all the functionality to format the text and improve cohesion
    //Use move semantics introduced in c++11 to improve perfermance arround copying data and tell the programer that
    //the string input shall not be aveilable after introducing it in the object (best practices)
    TextFormatter* textFormatter = new TextFormatter(std::move(input));

    //Do all the format
    textFormatter->RemoveCharacterFromText(',');
    textFormatter->RemoveCharacterFromText('.');
    textFormatter->RemoveCharacterFromText('\n');
    textFormatter->RemoveCharacterFromText('\r');

    textFormatter->LowercaseAllWords();

    std::vector<std::string> words = textFormatter->GetAllWordsSeparated();

    std::map < char, std::vector<std::string> > sortedWords;

    //as the words are sorted with the first character and not with the whole word
    //a map is used to get all the words at the same order they appear in the sentence 
    //and sort them automatically following the standard algorithm in c++ for maps
    for(std::string word : words){

        sortedWords[word[0]].push_back(word);
    }

    //iterate sorted words to print them all in separate lines
    for(auto it = sortedWords.begin(); it != sortedWords.end(); it++){
        

        //check if the iterator is in the first element, if it is not go to the next line before we print the new line of words
        if(it != sortedWords.begin()){

            std::cout << std::endl;
        }

        auto key = it->first;
        auto val = it->second;

        firstIteration = true;

        //separate words with spaces
        for(std::string word : val){

            if(firstIteration){

                firstIteration = false;

                std::cout << word;

            }else{

                std::cout << " " << word;
            }
            
        }
        
    }

}