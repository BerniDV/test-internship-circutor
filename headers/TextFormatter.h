#pragma once

#include <string>
#include <vector>

class TextFormatter{

    public:

        //Constructor
        TextFormatter();

        //Constructor overloading with the text to format
        TextFormatter(std::string&& textToFormat);

        //Remove the desired character from the text
        void RemoveCharacterFromText(char character);

        //Transform the text to lowercase
        void LowercaseAllWords();

        //Get all the words in the text
        std::vector<std::string> GetAllWordsSeparated();

        //Get the text that is being formated
        std::string GetText();

    private:

        //The text that is being formated
        std::string text;
};