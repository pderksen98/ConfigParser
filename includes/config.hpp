#include <stdlib.h>
#include <string>
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <sstream> //stringstream

enum conf_parser {
	LISTEN = 1,
	SERVER_NAME,
	ROOT,
	LOCATION,
	MAX_SIZE,
	ERROR_PAGE,
	CGI
};

class Location
{
	private:
		std::string					_index;
		std::map<std::string, bool>	_requestMethods;
		std::string					_upload;
		bool						_autoIndex;

	public:
		Location();
		Location(std::vector<std::string> &locationBody);
		~Location();

		const std::string					&getIndex() const;
		const std::string					&getUpload() const;
		bool								getRequestMethods(const std::string &key) const;
		bool							 	getAutoIndex() const;

	
		void	printLocationClass();
};

class Config
{
	private:
		unsigned int						_port;
		unsigned int						_maxSize;
		std::vector<std::string>			_serverNames;
		std::string							_root;
		std::string							_cgi;
		std::map<std::string,Location>		_locations;
		std::map<int, std::string>			_errorPage;
	
	public:
		//constructors
		Config();
		~Config();
		Config(const Config &other);							//not needed yet
		Config& operator=(Config other); //copy and swap idiom 	//not needed yet
		Config(std::vector<std::string> &serverVector);

		//getters
		const unsigned int						&getPort() const;
		const unsigned int						&getMaxSize() const;
		const std::vector<std::string>			&getServerNames() const;
		const std::string						&getRoot() const;
		const std::string						&getCgi() const;
		const Location							&getLocation(const std::string& key) const;
		const std::map<int,std::string>			&getErrorPage() const;

		//setters
		void	setPort(unsigned int &port);
		void	setMaxSize(unsigned int &maxSize);
		void	setServerNames(std::vector<std::string> &serverNames);
		void	setRoot(std::string &root);
		void	setCgi(std::string &cgi);
		void	setLocations(const std::string &key, const Location &value);
		void	setErrorPage(std::map<int,std::string> &errorPage);

		size_t	determineIfKeyword(const std::string &word);
		void	callKeywordFunction(size_t &enumValue, std::string &line);
		void	printConfigClass();
};


//main.cpp
// size_t	Config::determineIfKeyword(const std::string &word);
void	valueToString(Config &object, std::string &line, size_t &enumValue);
void	valueToUnsigned(Config &object, std::string &line, size_t &enumValue);
void	valueToStringVector(Config &object, std::string &line);
// void	Config::callKeywordFunction(size_t &enumValue, std::string &line);
// Config::Config(std::vector<std::string> &serverVector);
std::vector<Config>	setConfigVector(std::vector<std::vector<std::string> > &serverVector);
int		main(int argc, char const *argv[]);


//configParser.cpp
// Config::Config();
// Config::~Config(){}
// Config::Config(const Config &other);
// Config& Config::operator=(Config other);
//(all getters and setters and constructors)
std::map<std::string, bool>	returnFalseMethodsMap(void);


//configUtils.cpp
void	failure(const char *message);
const std::vector<std::string>	getFileVector(const std::string &fileName);
bool	checkBrackets(const std::vector<std::string> &vec);
size_t	findClosingBracket(const std::vector<std::string> &vec, size_t line);
std::vector<std::string>	returnLocationBody(std::vector<std::string> &serverVector, size_t i, size_t end);
std::vector<std::string>	findServerBlock(const std::vector<std::string> &vec);
std::vector<std::vector<std::string> >	createServerVector(const std::vector<std::string> &file);
std::string	truncateString(const std::string &str, char c);
std::string findFirstWord(std::string &line) ;
unsigned int	stringToUnsigned(std::string &word);
std::string	getSecondWord(std::string &line);


//configPrint.cpp
void	printStringVector(std::vector<std::string> &vec);
void	printServerVector(std::vector<std::vector<std::string> > &vec);
// void	Location::printLocationClass(void);
// void	Config::printConfigClass(void);
