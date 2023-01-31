#include "../includes/config.hpp"



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
	return (0);
}

