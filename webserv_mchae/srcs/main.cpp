#include "Config.hpp"
#include <signal.h>

void	signalhandler(int sigint)
{
	if (sigint == 2)
	{
		Config::get_m_config()->get_m_webserv()->signalExit();
	}
	exit(1);
}

int	main(int argc, char** argv)
{
	Config*	config;

	config = Config::get_m_config();
	try 
	{
		if (argc < 2)
			config->parseConfig(std::string("./configs/default.conf"));
		if (argc >= 2)
			config->parseConfig(std::string(argv[1]));
	}	
	catch(const char* e)
	{
		exit(1);
	}

	Webserv	webserv;

	signal(SIGINT, signalhandler);
	config->set_m_webserv(&webserv);
	webserv.initServer();
	webserv.startServer();
}