#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

class CommandReader
{
private:
    std::vector<std::string> command;

    int NumberOfClosingSymbols(std::string string);
    std::string stringToLower(std::string string);
    void removeSpaces(std::string& string); 
    void removeEmptyArgs(std::vector<std::string>& arguments);

public:
    CommandReader(std::string command);
    
    int getNumberOfArgs() const;
    void CommandReaderFunction(std::string command);
    std::string& operator [] (std::size_t index);
    const std::string& operator [] (std::size_t index) const; 
};