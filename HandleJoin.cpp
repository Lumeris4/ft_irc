/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleJoin.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 13:48:24 by bfiquet           #+#    #+#             */
/*   Updated: 2025/08/20 11:40:26 by bfiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"
#include "Server.hpp"

std::vector<std::string> split(const std::string& input, char delimiter) {
	std::vector<std::string> tokens;
	std::stringstream ss(input);
	std::string token;

	while (std::getline(ss, token, delimiter)) {
		if (!token.empty())
			tokens.push_back(token);
	}
	return tokens;
}

void Server::handle_join(std::string argument, int socketfd, User &user)
{
	if (argument.empty())
	{
        std::string message = ":irc.example.net 461 " + user.getNickname() + " MODE :Not enough parameters\r\n";
        send(socketfd, message.c_str(), message.length(), 0);
        return;
    }
	size_t space_pos = argument.find(' ');
	std::string channels_str = argument;
	std::string keys_str = "";
	if (space_pos != std::string::npos)
	{
		channels_str = argument.substr(0, space_pos);
		keys_str = argument.substr(space_pos + 1);
	}
	std::vector<std::string> channels = split(channels_str, ',');
	std::vector<std::string> keys = split(keys_str, ',');
	if (keys.size() != 0)
	{
		for (size_t i = 0; i < channels.size(); i++)
			joinCanal(channels[i], keys[i], socketfd, user);
	}
	else
	{
		for (size_t i = 0; i < channels.size(); i++)
			joinCanal(channels[i], "", socketfd, user);
	}
}