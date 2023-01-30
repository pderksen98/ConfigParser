#include "../includes/config.hpp"

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

//Prints out a server vector
//in other words a vector of string vectors: vector< vector<string> >
void	printServerVector(std::vector<std::vector<std::string> > &vec)
{
	for (size_t i = 0; i < vec.size(); i++)
	{
		std::cout << "	*** SERVER " << i + 1 << " ***" << std::endl;
		printStringVector(vec[i]);
		std::cout << std::endl;
	}
}

void	Location::printLocationClass(void)
{
	std::cout << "index : " << this->getIndex() << std::endl;
	if (this->getAutoIndex())
		std::cout << "autoindex : on" << std::endl;
	else
		std::cout << "autoindex : off" << std::endl;

	// std::cout << "GET : " << _requestMethods["GET"] << std::endl;
	std::cout << "GET : " << this->getRequestMethods("GET") << std::endl;

	std::cout << "POST : " << _requestMethods["POST"] << std::endl;
	std::cout << "DELETE : " << _requestMethods["DELETE"] << std::endl;
	std::cout << "PUT : " << _requestMethods["PUT"] << std::endl;
	std::cout << "PATCH : " << _requestMethods["PATCH"] << std::endl;

	std::cout << "upload : " << this->getUpload() << std::endl;

}

void	Config::printConfigClass(void)
{
	std::cout << "address : " << this->getPort() << std::endl << std::endl;
	
	std::vector<std::string> serverNames = this->getServerNames();
	std::cout << "server name(s) :" << std::endl;
	for (size_t i = 0; i < serverNames.size(); i++)
		std::cout << serverNames[i] << std::endl;
	std::cout << std::endl;
	std::cout << "root : " << this->getRoot() << std::endl << std::endl;
	std::cout << "max_size : " << this->getMaxSize() << std::endl << std::endl;
	std::cout << "cgi : " << this->getCgi() << std::endl << std::endl;
	for (std::map<std::string, Location>::const_iterator it = _locations.begin(); it != _locations.end(); it++)
	{
		std::cout << "Location : " << it->first << std::endl;
		Location object = it->second;
		object.printLocationClass();
		std::cout << std::endl;
	}
	
}

