/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleInvite.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 12:50:42 by bfiquet           #+#    #+#             */
/*   Updated: 2025/08/12 14:38:17 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "User.hpp"

void Server::handle_invite(std::string argument, int socketfd)
{
	size_t index = argument.find('#');
	if (index == std::string::npos)
	{
		std::cout << "Invalid format" << std::endl;
		return;
	}
	size_t pos = argument.find(' ');
	std::string user = argument.substr(0, pos);
	if (pos == std::string::npos)
	{
		std::cout << "Invalid format" << std::endl;
		return;
	}
	std::string channel = argument.substr(index + 1);
	if (channel.empty())
	{
		std::cout << "Invalid format (bad channel)\n";
		return;
	}
	//setTopic(newTopic);
	std::cout << "user " << user << " got invited in " << channel << "]" << std::endl;
	this->invite(channel ,user, socketfd);
}
