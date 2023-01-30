#include "../includes/config.hpp"


//Checks if the word found is one of the keywords
size_t	Config::determineIfKeyword(const std::string &word)
{
	if (word == "listen")
		return (LISTEN);
	else if (word == "server_name")
		return (SERVER_NAME);
	else if (word == "root")
		return (ROOT);
	else if (word == "location")
		return (LOCATION);
	else if (word == "client_max_body_size")
		return (MAX_SIZE);
	else if (word == "error_page")
		return (ERROR_PAGE);
	else if (word == "cgi")
		return (CGI);
	return (0);
}

void	valueToString(Config &object, std::string &line, size_t &enumValue)
{
	std::string	value = getSecondWord(line);
	if (!value.empty())
	{
		if (enumValue == ROOT)
			object.setRoot(value);
		else if (enumValue == CGI)
			object.setCgi(value);
	}
}

void	valueToUnsigned(Config &object, std::string &line, size_t &enumValue)
{
	std::string		word = getSecondWord(line);
	unsigned int	value = stringToUnsigned(word);
	if (value != 0)
	{
		if (enumValue == LISTEN)
			object.setPort(value);
		else if (enumValue == MAX_SIZE)
			object.setMaxSize(value);
	}
}

void	valueToStringVector(Config &object, std::string &line)
{
	std::vector<std::string>	serverNames;
	std::string					name;

	std::stringstream			ss(line);
	ss >> name; 				//first word
	while (ss >> name)
		serverNames.push_back(name);
	if (serverNames.empty())
		return ;
	object.setServerNames(serverNames);
}

void	Config::callKeywordFunction(size_t &enumValue, std::string &line)
{

	if (enumValue == LISTEN || enumValue == MAX_SIZE)
		valueToUnsigned(*this, line, enumValue);
	else if (enumValue == ROOT || enumValue == CGI)
		valueToString(*this, line, enumValue);
	else if (enumValue == SERVER_NAME)
		valueToStringVector(*this, line);



}

Config::Config(std::vector<std::string> &serverVector)
	: _port(80), _maxSize(1) //add errorpages
{
	size_t	enumValue;

	for (size_t i = 0; i < serverVector.size(); i++)
	{
		std::string word = findFirstWord(serverVector[i]);
		enumValue = determineIfKeyword(word);
		if (enumValue == 0)
			continue ;
		else if (enumValue == LOCATION)
		{
			std::string	locationName = getSecondWord(serverVector[i]);
			if (locationName.empty())
				continue ;
			size_t end = findClosingBracket(serverVector, i);
			std::vector<std::string> locationBody = returnLocationBody(serverVector, i, end);
			Location location(locationBody);
			this->setLocations(locationName, location);
			while (i < end)
				i++;
		}
		else
			callKeywordFunction(enumValue, serverVector[i]);
	}
}

// For each server found in the server vector the 'fillConfigObject' function is called
// The Config object created on the heap is given as a reference parameter to this function
// After calling the function, all the values are set correctly and the Config class is added to the vector
std::vector<Config>	setConfigVector(std::vector<std::vector<std::string> > &serverVector)
{
	std::vector<Config>	configVector;

	for (size_t i = 0; i < serverVector.size(); i++) //ITERATOR
	{
		Config	conf(serverVector[i]);
		configVector.push_back(conf);
	}
	return (configVector);
}


//fileVector = string vector; serverVector = vector<string> vector; configVector is Config vector
int	main(int argc, char const *argv[])
{
	if (argc != 2){
		std::cerr << "Wrong amount of arguments: expected 1\n"; //hier throw gaan gebruiken
		exit(1);
	}
	std::vector<std::string> fileVector;
	fileVector = getFileVector(argv[1]);
	// printStringVector(fileVector);

	if (!checkBrackets(fileVector)) {
		std::cerr << "Found non matching bracket(s) in '" << argv[1] << "' file" << std::endl; //throw
		exit(1);
	}

	std::vector<std::vector<std::string> >	serverVector;
	serverVector = createServerVector(fileVector);
	// printServerVector(serverVector);

	std::vector<Config>	configVector;
	configVector = setConfigVector(serverVector);
	
	for (size_t i = 0; i < configVector.size(); i++)
	{
		configVector[i].printConfigClass();
		std::cout << "-------------------------------------------" << std::endl;
	}

	// system("leaks config");
	return (0);
}

