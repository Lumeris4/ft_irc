/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleNick.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 09:51:17 by bfiquet           #+#    #+#             */
/*   Updated: 2025/09/15 14:45:08 by bfiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "User.hpp"

bool isValidName(std::string nick)
{
	for (size_t i = 0; i < nick.length(); i++)
	{
		if (nick[i] == ' ' || nick[i] == '\t' || nick[i] ==',' || nick[i] == ':')
			return false;
	}
	char c = nick[0];
	return std::isalpha(c) || c == '[' || c == '\\' || c == ']' || c == '`' || c == '_' || c == '{' || c == '}';
}

int Server::setNickname(std::string nick, int socket, User &user)
{
	std::string former_nick = user.getNickname();
	if (nick.empty())
	{
		std::string message = ":" + _servername + " 431 * :No nickname given\r\n";
		send(socket, message.c_str(), message.size(), 0);
		return (-1);
	}
	if (nick.length() > 9 || !isValidName(nick))
	{	
		std::string message = ":" + _servername + "432 * " + nick + " :Erroneous nickname\r\n";
		send(socket, message.c_str(), message.size(), 0);
		return (-1);
	}
	std::map<std::string, User>::iterator it = _list_user.find(nick);
	if (it != _list_user.end())
	{
		std::string message = ":" + _servername + " 433 * " + nick + " :Nickname is already in use\r\n";
		send(socket, message.c_str(), message.size(), 0);
		return (-1);
	}
	user.setNickname(nick);
	if (!user.getUsername().empty() && !user.getRegistered())
    {
        sendWelcome(user);
        user.setRegistered(true);
    }
	if (!former_nick.empty())
	{
		std::map<std::string, User>::iterator it2 = _list_user.find(former_nick);
		if (it2 != _list_user.end())
			_list_user.erase(it2);
		_list_user.insert(std::make_pair(nick, user));
	}
	std::map<std::string, Channel>::iterator ito;
	for (ito = _list_channel.begin(); ito != _list_channel.end() ; ito++)
	{
		std::vector<std::string> copy2 = ito->second.getListChef();
		std::vector<std::string>::iterator ito2 = std::find(copy2.begin(), copy2.end(), former_nick);
		if (ito2 != copy2.end())
		{
			ito->second.kickuser(former_nick);
			ito->second.adduser(user.getNickname());
			ito->second.remote(user.getNickname());
		}
		std::vector<std::string> copy = ito->second.getListUser();
		std::vector<std::string>::iterator ito1 = std::find(copy.begin(), copy.end(), former_nick);
		if (ito1 != copy.end())
		{
			ito->second.kickuser(former_nick);
			ito->second.adduser(user.getNickname());
		}
		std::vector<std::string> copy3 = ito->second.getListInvitation();
		std::vector<std::string>::iterator ito3 = std::find(copy3.begin(), copy3.end(), former_nick);
		if (ito3 != copy.end())
		{
			ito->second.baninvitation(former_nick);
			ito->second.addinvitation(user.getNickname());
		}
	}
	std::string message = ":" + former_nick + "!ident@host NICK :" + nick + "\r\n";
	send(socket, message.c_str(), message.size(), 0);
	return (0);
}
