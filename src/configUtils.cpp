#include "../includes/config.hpp"

//Prints error message and exits with errno exit code
void	failure(const char *message)
{
	perror(message);
	exit(errno);
}

//Puts all the lines from the config file as strings in a vector
//When a '#' character is found the rest of the line is seen as a comment, so the line gets truncated
//Empty lines are skipped and so do not get converted to a std::string in the vector
const std::vector<std::string>	getFileVector(const std::string &fileName)
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

//Searches the config file for 'server {'. If found it searches the matching closing bracket.
//Then it adds al these line into a 'server vector' and returns this vector.
//Linecount is a static variable that keeps track of the last line that is added to a server vector
//Servercount is a static variable that keeps track of the number of server blocks encountered
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

//Creates and returnes a vector of vector<string>'s: vector< vector<string> >
//In words: a vector of string vectors
//Where each vector<string> is the body of a server block in the config file
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
