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
const std::map<int,std::string>				&Config::getErrorPage() const 	{return (_errorPage);}
const Location								&Config::getLocation(const std::string& key) const 
{
	 std::map<std::string,Location>::const_iterator it = _locations.find(key);
	if (it == _locations.end())
		std::cerr << "Location not found" << std::endl; //throw gaan gebruiken
		// throw std::out_of_range("Location not found");
	return (it->second);
}

const std::string					&Location::getIndex() const 			{return (_index);}
const std::string					&Location::getUpload() const 			{return (_upload);}
bool							 	Location::getAutoIndex() const 			{return (_autoIndex);}
// const std::map<std::string,bool>	&Location::getRequestMethods() const 	{return (_requestMethods);}
bool								Location::getRequestMethods(const std::string &key) const
{
	if (_requestMethods.count(key)) // returns 1 if the key is found otherwise 0 is returned
		return (_requestMethods.at(key)); //if the key is found the value at that key is returned
	return (false);
}

//	************************************
//	************ SETTERS ***************
//	************************************

void	Config::setPort(unsigned int &port) 								{_port = port;}
void	Config::setMaxSize(unsigned int &maxSize) 							{_maxSize = maxSize;}
void	Config::setServerNames(std::vector<std::string> &serverNames)		{_serverNames = serverNames;}
void	Config::setRoot(std::string &root) 									{_root = root;}
void	Config::setCgi(std::string &cgi) 									{_cgi = cgi;}
void	Config::setLocations(const std::string &key, const Location &value) {_locations[key] = value;}
void	Config::setErrorPage(std::map<int,std::string> &errorPage) 			{_errorPage = errorPage;}

// void	Location::setIndex(std::string &index)								{_index = index;}
// void	Location::setRequestMethods(std::map<std::string,bool> &methods)	{_requestMethods = methods;}
// void	Location::setUpload(std::string &upload)							{_upload = upload;}
// void	Location::setAutoIndex(bool autoIndex)								{_autoIndex = autoIndex;}


std::map<std::string, bool>	returnFalseMethodsMap(void)
{
	std::map<std::string, bool>	methods;
	methods["GET"] = false;
	methods["POST"] = false;
	methods["DELETE"] = false;
	methods["PUT"] = false;
	methods["DELETE"] = false;
	return (methods);
}

Location::Location()
	: _requestMethods(returnFalseMethodsMap()), _autoIndex(false)
{
}

Location::~Location(){}

Location::Location(std::vector<std::string> &locationBody)
	: _requestMethods(returnFalseMethodsMap()), _autoIndex(false)
{
	for (size_t i = 0; i < locationBody.size(); i++)
	{
		std::string word = findFirstWord(locationBody[i]);
		if (word.empty())
			continue;
		else if (word == "autoindex"){
			std::string second = getSecondWord(locationBody[i]);
			if (second == "ON")
				_autoIndex = true;
		}
		else if (word == "upload" || word == "index"){
			std::string second = getSecondWord(locationBody[i]);
			if (second.empty())
				continue ;
			if (word == "upload")
				_upload = second;
			else if (word == "index")
				_index = second;
		}
		else if (word == "request_method")
		{
			std::stringstream	ss(locationBody[i]);
			std::string			name;
			ss >> name;
			while (ss >> name)
			{
				if (_requestMethods.find("name") != _requestMethods.end())
					_requestMethods["name"] = true;
			}
		}
	}
}


