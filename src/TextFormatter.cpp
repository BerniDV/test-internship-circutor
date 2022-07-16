
#include "../headers/TextFormatter.h"
#include <algorithm>
#include <cctype>
#include <sstream>


TextFormatter::TextFormatter(){

    text = "";
}

TextFormatter::TextFormatter(std::string&& text) : text(text)     
{

}

std::string TextFormatter::GetText(){

    return text;
}

void TextFormatter::RemoveCharacterFromText(char characterToRemove){

    //remove character from all the string
    text.erase(std::remove(text.begin(), text.end(), characterToRemove), text.end());
}

void TextFormatter::LowercaseAllWords(){

    //use of the std function tolower inside of a lambda to simulate the pointer to a function that lowercase the characters
    std::transform(text.begin(), text.end(), text.begin(), [](unsigned char c){ return std::tolower(c); });
}

std::vector<std::string> TextFormatter::GetAllWordsSeparated(){

    std::vector<std::string> words;

    std::istringstream ss(text);
    
    // for storing each word
    std::string word; 
  
    // Traverse through all words and store it in the vector words
    while (ss >> word) 
    {
        
        words.push_back(word);
    }

    return words;
}

