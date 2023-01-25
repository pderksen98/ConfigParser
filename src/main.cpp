#include <stdlib.h>
#include <string>
#include <iostream>
// #include "config.hpp"
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <vector>


//prints a std::vector<std::string> string by string
void	printStringVector(std::vector<std::string> &vec)
{
	size_t	line_number = 1;
	for (size_t i = 0; i < vec.size(); i++)
	{
		std::cout << line_number << ": " << vec[i] << std::endl;
		line_number++;
	}
}

void	printServerVector(std::vector<std::vector<std::string> > &vec)
{
	for (size_t i = 0; i < vec.size(); i++)
	{
		std::cout << "	*** SERVER " << i << " ***" << std::endl;
		printStringVector(vec[i]);
		std::cout << std::endl;
	}
}

//Puts all the lines from the config as strings in a vector
//When a '#' character is found the rest of the line is seen as a comment, so the line gets truncated
//Empty lines are skipped and so do not get converted to a std::string in the vector
const std::vector<std::string>	getConfVector(const std::string &fileName)
{
	std::ifstream	configFile(fileName);
	if (!configFile) {
		std::cerr << "Cannot open file: " << fileName << std::endl; //hier throw gaan gebruiken
		exit(1);
	}
	std::vector<std::string>	confVector;
	std::string	line;
	while (getline(configFile, line))
	{
		if (line.empty())
			continue;
		if (line.at(0) == '#')
			continue;
		for (size_t pos = 0; pos < line.length(); pos++)
		{
			if (line.at(pos) == '#'){
				line = line.substr(0, pos);
				break ;
			}
		}
		confVector.push_back(line);
	}
	return (confVector);
}

// Function to check if each bracket '{' has a matching closing bracket '}'
bool	checkBrackets(const std::vector<std::string> &vec)
{
	int	openBrackets = 0;
	for (size_t line = 0; line < vec.size(); line++)
	{
		for (size_t pos = 0; pos < vec[line].length(); pos++)
		{
			if (vec[line].at(pos) == '{')
				openBrackets++;
			else if (vec[line].at(pos) == '}'){
				if (openBrackets == 0)
					return (false);
				openBrackets--;
			}
		}
	}
	if (openBrackets != 0)
		return (false);
	return (true);
}

//Searches on which line number the closing bracket '}' for the server block is and returns this value
size_t	findServerBracket(const std::vector<std::string> &vec, size_t line)
{
	line++;
	int	openBrackets = 1;
	int	check = 0;
	for (; line < vec.size(); line++)
	{
		for (size_t pos = 0; pos < vec[line].length(); pos++)
		{
			if (vec[line].at(pos) == '{')
				openBrackets++;
			else if (vec[line].at(pos) == '}')
				openBrackets--;
			if (openBrackets == 0){
				check = 1;
				break ;
			}
		}
		if (check == 1)
			break ;
	}
	return (line);
}

std::vector<std::string>	findServerBlock(const std::vector<std::string> &vec)
{
	static size_t				lineCount = 0;
	static size_t				serverCount = 0;
	std::vector<std::string>	serverBlock;
	size_t						begin;
	size_t						end;
	int							found = 0;

	for (; lineCount < vec.size(); lineCount++)
	{
		if (vec[lineCount].find("server {") != std::string::npos)
		{
			begin = lineCount;
			end = findServerBracket(vec, begin);
			lineCount = end + 1;
			serverCount++;
			found = 1;
			break ;
		}
	}
	if (found == 0 && serverCount == 0){
		std::cerr << "No server block found in the provided file" << std::endl; //throw
		exit (1);
	}
	if (found == 0)
		return (std::vector<std::string>());
	for (size_t line = begin; line <= end; line++)
		serverBlock.push_back(vec[line]);
	return (serverBlock);
}

std::vector<std::vector<std::string> >	createServerVector(const std::vector<std::string> &file)
{
	std::vector<std::vector<std::string> >	serverVector;
	std::vector<std::string>				serverBlock;

	serverBlock = findServerBlock(file);
	while (!serverBlock.empty())
	{
		serverVector.push_back(serverBlock);
		serverBlock = findServerBlock(file);
	}
	if (serverVector.empty()){
		std::cerr << "hallo: No server block found in the provided file" << std::endl; //overbodig wsl en throw
		exit(1);
	}
	return (serverVector);
}


//Make function to find first and last bracket of the server
//Use this to make a seperate std::vector<std::string> for each server block

int	main(int argc, char const *argv[])
{
	if (argc != 2){
		std::cerr << "Wrong amount of arguments: expected 1\n"; //hier throw gaan gebruiken
		exit(1);
	}
	std::vector<std::string> confVector;
	confVector = getConfVector(argv[1]);
	// printStringVector(confVector);

	if (!checkBrackets(confVector)) {
		std::cerr << "Found non matching bracket(s) in '" << argv[1] << "' file" << std::endl; //throw
		exit(1);
	}
	std::vector<std::vector<std::string> >	serverVector;
	serverVector = createServerVector(confVector);
	printServerVector(serverVector);
	return (0);
}

