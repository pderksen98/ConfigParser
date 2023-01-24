#include "config.hpp"

void	failure(const char *message)
{
	perror(message);
	exit(errno);
}
