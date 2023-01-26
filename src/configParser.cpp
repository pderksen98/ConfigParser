#include "../includes/config.hpp"

//	************************************
//	********** CONSTRUCTORS ************
//	************************************

Config::Config()
{
	_port = 80;
	_maxSize = 1;
}

Config::~Config()
{

}

//	************************************
//	************ GETTERS ***************
//	************************************

const unsigned int	&Config::getPort() const
{
	return (_port);
}

const unsigned int	&Config::getMaxSize() const
{
	return (_maxSize);
}

const std::vector<std::string>	&Config::getServerNames() const
{
	return (_serverNames);
}

const std::string	&Config::getRoot() const
{
	return (_root);
}

const std::string	&Config::getCgi() const
{
	return (_cgi);
}

const std::map<std::string,std::string>	&Config::getLocations() const
{
	return (_locations);
}

const std::map<int,std::string>	&Config::getErrorPage() const
{
	return (_errorPage);
}

//	************************************
//	************ SETTERS ***************
//	************************************

void	Config::setPort(unsigned int &port)
{
	_port = port;
}

void	Config::setMaxSize(unsigned int &maxSize)
{
	_maxSize = maxSize;
}

void	Config::setServerNames(std::vector<std::string> &serverNames)
{
	_serverNames = serverNames;
}

void	Config::setRoot(std::string &root)
{
	_root = root;
}

void	Config::setCgi(std::string &cgi)
{
	_cgi = cgi;
}

void	Config::setLocations(std::map<std::string,std::string> &locations)
{
	_locations = locations;
}

void	Config::setErrorPage(std::map<int,std::string> &errorPage)
{
	_errorPage = errorPage;
}






























