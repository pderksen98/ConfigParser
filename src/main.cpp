#include "../includes/config.hpp"

std::vector<Config>	setConfigVector(std::vector<std::vector<std::string> > &serverVector)
{
	std::vector<Config>	configVector;

	for (size_t i = 0; !serverVector[i].empty(), i++)
	{
		new int	x = 
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
	// fileVector = getFileVector(argv[1]);
	printStringVector(fileVector);
	if (!checkBrackets(fileVector)) {
		std::cerr << "Found non matching bracket(s) in '" << argv[1] << "' file" << std::endl; //throw
		exit(1);
	}
	std::vector<std::vector<std::string> >	serverVector;
	serverVector = createServerVector(fileVector);
	// printServerVector(serverVector);
	
	
	return (0);
}

