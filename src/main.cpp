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
	// size_t	i = 1;
	// for (std::vector<std::string>::iterator it=vec.begin(); it!=vec.end(); it++)
	// {
	// 	std::cout << i << ": " << *it << std::endl;
	// 	i++;
	// }
	
	size_t	line_number = 1;
	for (size_t i = 0; i < vec.size(); i++)
	{
		std::cout << line_number << ": " << vec[i] << std::endl;
		line_number++;
	}
}

//Puts all the lines from the config as strings in a vector
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
		confVector.push_back(line);
	}
	return (confVector);
}

//Function to check if each bracket '{' has a matching closing bracket '}' 
void	checkBrackets(std::vector<std::string> &vec)
{
	for (size_t i = 0; i < vec.size(); i++)
	{
		if (vec[i].empty())
			continue ;
		if (vec[i].at(0) == '#')
			continue ;
		// keep track of line & position of { 
	}
}

//Make function to find first and last bracket of the server
//Use this to make a seperate std::vector<std::string> for each server block

int	main(int argc, char const *argv[])
{
	if (argc != 2)
	{
		std::cerr << "Wrong amount of arguments: expected 1\n"; //hier throw gaan gebruiken
		exit(1);
	}
	std::vector<std::string> confVector;
	confVector = getConfVector(argv[1]);

	// printStringVector(confVector);
	checkBrackets(confVector);


	return (0);
}