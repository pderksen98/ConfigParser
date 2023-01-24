#ifndef CONFIG_HPP
#define CONFIG_HPP
#include <string>
#include <vector>
#include <map>
#include <errno.h> //included for the failure() function
#include <fstream> //ifstream
#include <stdexcept> //runtime_error


class Location;
class ConfigParser;	

class Config
{
private:
	unsigned						_port;
	std::vector<std::string>		_serverName;
	std::string						_root;
	unsigned int					_maxSize; 
	std::map<std::string, Location>	_location;
	std::string						_cgi;
	std::map<int, std::string>		_errorPage;

public:
	//constructor
	Config(const Config &conf);
	Config(const ConfigParser &confP);
	Config& operator=(const Config &conf);
	~Config();

	//getters
	const unsigned int						&getPort() const;
	const std::vector<std::string>			&getServerName() const;
	const std::string						&getRoot() const;
	const unsigned long long				&getSize() const;
	const std::map<std::string, Location> 	&getLocation()const;
	const std::string						&getCgi() const;
	const std::map<int, std::string>		&getErrorPage() const;

	//setters
	void	setPort(const ConfigParser &confP, int line);
	void	setServerName(const ConfigParser &confP, int line);
	void	setRoot(const ConfigParser &confP, int line);
	void	setMaxSize(const ConfigParser &confP);


	void	determineCase(const std::string &word, const ConfigParser &conf, int line);

};

class Server
{
	private:
		unsigned int					_port;
		std::vector<std::string>		_serverName;
		std::string						_root;
		std::string						_cgi;
		std::map<std::string,Location>	_location;
		std::map<int,std::string>		_errorPage;
		unsigned int					_maxSize;

	public:
		Server(const Server &serv);
		Server& operator=(const Server &serv);
		~Server();

		const unsigned int						&getPort() const;
		const std::vector<std::string>			&getServerName() const;
		const std::string						&getRoot() const;
		const std::string						&getCgi() const;
		const std::map<std::string,Location>	&getLocation;
		const std::map<int,std::string>			&getErrorPage() const;
		const unsigned int						&getSize() const;

		void	setPort()
};


class ConfigParser
{
private:
	std::map<std::string, std::string> _configMap;
	std::vector<Server>	_serverVec;

public:
	ConfigParser();
	~ConfigParser();
	void	parse(const std::string &fileName);
	std::string	getValue(std::string key, int line) const;

};


class Location
{
	private:
		std::string					_locationFolder;
		std::string					_uploadFolder;
		std::string					_index;
		std::map<std::string, int>	_methods;
	public:
	//constructor
	//getters
	//setters
};


void	Config::determineCase(const std::string &word, const ConfigParser &confP, int line)
{
	
}


#endif