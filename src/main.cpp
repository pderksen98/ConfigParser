#include "../includes/config.hpp"

std::string findFirstWord(std::string &line) 
{
    std::stringstream ss(line);
    std::string firstWord;
    ss >> firstWord;
    return firstWord;
}

//HIER GEBLEVEN		HIER GEBLEVEN 		HIER GEBLEVEN 		HIER GEBLEVEN
//HIER GEBLEVEN		HIER GEBLEVEN 		HIER GEBLEVEN 		HIER GEBLEVEN
//HIER GEBLEVEN		HIER GEBLEVEN 		HIER GEBLEVEN 		HIER GEBLEVEN
//HIER GEBLEVEN		HIER GEBLEVEN 		HIER GEBLEVEN 		HIER GEBLEVEN
//HIER GEBLEVEN		HIER GEBLEVEN 		HIER GEBLEVEN 		HIER GEBLEVEN

void	Config::determineKeyword(const std::string &word) //not sure of second const
{
	//checks if the word is {listen, server_name, root, location, client_max_body_size, error_page, cgi}
	//if yes: it calls the correct setter function
}

Config::Config(std::vector<std::string> &serverVector)
	: _port(80), _maxSize(1) //add errorpages
{
	for (size_t i = 0; i < serverVector.size(); i++)
	{
		std::string word = findFirstWord(serverVector[i]);
		determineKeyword(word);
	}

}

// For each server found in the server vector the 'fillConfigObject' function is called
// The Config object created on the heap is given as a reference parameter to this function
// After calling the function, all the values are set correctly and the Config class is added to the vector
std::vector<Config>	setConfigVector(std::vector<std::vector<std::string> > &serverVector)
{
	std::vector<Config>	configVector;

	for (size_t i = 0; !serverVector[i].empty(); i++)
	{
		Config	conf(serverVector[i]);
		configVector.push_back(conf);
	}
	return (configVector);
}


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

	std::string line1 = "			Hallo dit is wat tekst\n";
	std::string line2 = "			Hallo\n";
	std::string line3 = "	Hallo\n";
	std::string line4 = "ajkldsjfaksjfkasfj";
	std::string line5 = "     			";
	std::string line6 = "\n    	check";


	std::cout << findFirstWord(line1) << std::endl;
	std::cout << findFirstWord(line2) << std::endl;
	std::cout << findFirstWord(line3) << std::endl;
	std::cout << findFirstWord(line4) << std::endl;
	std::cout << findFirstWord(line5) << std::endl;
	std::cout << findFirstWord(line6) << std::endl;
	
	
	return (0);
}

