#include "Server.hpp"
#include "User.hpp"

void Server::handle_privmsg(std::sring argument, int socketfd)
{
    bool is_channel = false;
    std::string content = "";
    std::string destination;

    if (argument[0] == '#')
        is_channel = true;
    size_t space_pos = argument.find(' ');
    if (space_pos != std::string::npos)
	{
		content = argument.substr(space_pos + 2);
        destination = argument.substr(0, space_pos);
	}
    else
    {
        std::cout << "invalid format" << std::endl;
        return ;
    }
    sendMessage(destination, content, is_channel, socketfd);
}