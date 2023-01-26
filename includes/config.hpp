#include <stdlib.h>
#include <string>
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>

class Config
{
	private:
		unsigned int						_port;
		unsigned int						_maxSize;
		std::vector<std::string>			_serverNames;
		std::string							_root;
		std::string							_cgi;
		std::map<std::string,std::string>	_locations;
		std::map<int, std::string>			_errorPage;
	
	public:
		//constructors
		Config();
		~Config();
		Config(const Config &conf);
		Config& operator=(const Config &conf);

		//getters
		const unsigned int						&getPort() const;
		const unsigned int						&getMaxSize() const;
		const std::vector<std::string>			&getServerNames() const;
		const std::string						&getRoot() const;
		const std::string						&getCgi() const;
		const std::map<std::string,std::string>	&getLocations() const;
		const std::map<int,std::string>			&getErrorPage() const;

		//setters
		void	setPort(unsigned int &port);		//!References in setters may cause errors: be aware!
		void	setMaxSize(unsigned int &maxSize);
		void	setServerNames(std::vector<std::string> &serverNames);
		void	setRoot(std::string &root);
		void	setCgi(std::string &cgi);
		void	setLocations(std::map<std::string,std::string> &locations);
		void	setErrorPage(std::map<int,std::string> &errorPage);


};


//main.cpp
int	main(int argc, char const *argv[]);

//configUtils.cpp
void									failure(const char *message);
const std::vector<std::string>			getFileVector(const std::string &fileName);
bool									checkBrackets(const std::vector<std::string> &vec);
size_t									findServerBracket(const std::vector<std::string> &vec, size_t line);
std::vector<std::string>				findServerBlock(const std::vector<std::string> &vec);
std::vector<std::vector<std::string> >	createServerVector(const std::vector<std::string> &file);

//ConfigPrint.cpp
void	printStringVector(std::vector<std::string> &vec);
void	printServerVector(std::vector<std::vector<std::string> > &vec);
