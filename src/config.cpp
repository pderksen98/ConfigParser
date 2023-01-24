#include "config.hpp"
#include <stdexcept>
#include <fstream>
#include <iostream>

void	Config::setRoot(const ConfigParser &confP, int line)
{
	std::string root = confP.getValue("root", line);
	_root = root;
}


std::string	ConfigParser::getValue(std::string key, int line) const
{
	if (line == 0)
	{
		std::map<std::string,std::string>::const_iterator it = _configMap.find(key);
		if (it != _configMap.end())
			return (_configMap->second);
	}
	else
	{
		std::map<std::string, std::string>::const_iterator it = _configMap.find(key + std::to_string(line));
		if (it != _configMap.end())
			return (_configMap->second);
	}
	return "";
}


void    ConfigParser::parse(const std::string &fileName)
{
	std::ifstream configFile(fileName);
	if (!configFile)
	    std::cerr << ("Cannot open file: " + fileName);
	std::string	line;
	int			lineNumber = 0;
	while (getline(configFile, line))
	{
		lineNumber++;
		if (line.empty())
			continue ;
		if (line.at(0) == '#')
			continue ;
		size_t pos = line.find(' ');
		if (pos = std::string::npos)
			continue ;
		std::string	key = line.substr(0, pos);
		std::string	value = line.substr(pos + 1);
		_configMap[key + std::to_string(lineNumber)] = value;
	}
}



void	parse(const std::string	&fileName)
{
	std::ifstream configFile(fileName);
	if (!configFile)
		std::cerr << "Cannot open file: " << fileName << std::endl; //use throw maybe
	std::string	line;
	
	
}





// int foo(void) 
// {
// 	try {
// 		std::cout << "About to throw...\n";
// 		throw std::runtime_error("Gak!");
// 		std::cout << "Back from throw?!\n";
// 	}
// 	catch (std::exception &e) {
// 		std::cout << "Caught exception: "<< e.what() <<"\n";
// 	}
// 	return 0;
// }