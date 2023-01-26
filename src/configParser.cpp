#include "../includes/config.hpp"

//	************************************
//	********** CONSTRUCTORS ************
//	************************************

//Default constructor
Config::Config()
{
	_port = 80;
	_maxSize = 1;
}

//No dynamically allocated memmory in the class so destructor is empty
Config::~Config(){}


//(Deep copy only matters with pointers and references, 
//...since then the pointer gets coppied and points to the same block of memmory.
//...If the other class destructs, you are left with a pointer pointing to a freed block of memmory)
Config::Config(const Config &other)
{
	this->_port = other._port;
	this->_maxSize = other._maxSize;
	this->_serverNames = other._serverNames;
	this->_root = other._root;
	this->_cgi = other._cgi;
	this->_locations = other._locations;
	this->_errorPage = other._errorPage; 
}


//Copy assignent operator using the copy and swap idiom
//Note that the object 'other' is given as value instead of reference
//Therefore the object gets copied and it does not touch the original object
//The copy and swap idiom has multiple benifits (look up if interested)
Config& Config::operator=(Config other)
{
	std::swap(*this, other);
	return *this;
}

//	************************************
//	************ GETTERS ***************
//	************************************

const unsigned int							&Config::getPort() const 		{return (_port);}
const unsigned int							&Config::getMaxSize() const 	{return (_maxSize);}
const std::vector<std::string>				&Config::getServerNames() const {return (_serverNames);}
const std::string							&Config::getRoot() const 		{return (_root);}
const std::string							&Config::getCgi() const 		{return (_cgi);}
const std::map<std::string,std::string>		&Config::getLocations() const 	{return (_locations);}
const std::map<int,std::string>				&Config::getErrorPage() const 	{return (_errorPage);}


//	************************************
//	************ SETTERS ***************
//	************************************

void	Config::setPort(unsigned int &port) 								{_port = port;}
void	Config::setMaxSize(unsigned int &maxSize) 							{_maxSize = maxSize;}
void	Config::setServerNames(std::vector<std::string> &serverNames)		{_serverNames = serverNames;}
void	Config::setRoot(std::string &root) 									{_root = root;}
void	Config::setCgi(std::string &cgi) 									{_cgi = cgi;}
void	Config::setLocations(std::map<std::string,std::string> &locations) 	{_locations = locations;}
void	Config::setErrorPage(std::map<int,std::string> &errorPage) 			{_errorPage = errorPage;}






























