/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 13:10:28 by bfiquet           #+#    #+#             */
/*   Updated: 2025/08/07 10:51:39 by bfiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parsing.hpp"

Parsing::Parsing()
{
	_connected = false;
	
}

int Parsing::parsing (char *buf, std::string password)
{
	setInput(buf);
	std::string array[] = {"CAP", "PASS", "NICK", "KICK", "MODE", "TOPIC", "USER", "JOIN", "INVITE"};
	int			size = sizeof(array) / sizeof(array[0]);
	int			level;
	std::stringstream ss(getInput());
	std::string cmds;
	int			last_upper;

	setInput(buf);
	setServerPassword(password);
	while (std::getline(ss, cmds, '\n'))
	{
		last_upper = 0;
        setLine(cmds);
		if (_line[_line.size() - 1] == '\n')
			_line.erase(_line.size() - 1, 1);
		for (int i = 0; isupper(_line[i]) && i < (int)_line.size(); i++)
			last_upper = i + 1;
		setRawCmd(_line.substr(0, last_upper));
		if (last_upper < (int)_line.length())
			setArgument(_line.substr(last_upper + 1));
		else
			setArgument("");
		for (int i = 0; i < size; i++)
		{
			if (!getRawCmd().compare(array[i]))
				level = i;
		}
		if (level > 1 && getConnected() == false)
			std::cout << "you have to enter the password first" << std::endl;
		switch (level)
		{
			case 0:
				break;
			case 1:
			{
				if (check_password(getArgument()) == -1)
					return (-1);
				break;
			}
			case 2:
			{
				std::cout << "command NICK found" << std::endl;
				break;
			}
			case 3:
			{
				std::cout << "command KICK found" << std::endl;
				break;
			}
			case 4:
			{
				std::cout << "command MODE found" << std::endl;	
			break;
			}
			case 5:
			{
				std::cout <<  "command TOPIC found" << std::endl;
				break;
			}
			case 6:
			{
				std::cout << "command USER found" << std::endl;
				break;
			}
			case 7:
			{
				std::cout << "command JOIN found" << std::endl;
				break;
			}
			case 8:
			{
				std::cout << "command INVITE found" << std::endl;
				break;
			}
			default:
				std::cout << getLine() << " is not a valid command" <<std::endl;
				break;
		}
		level = 0;
	}
	return (0);
}

void	Parsing::setServerPassword(std::string password)
{
	this->_serverPassword = password;
}

const std::string	Parsing::getServerPassword() const
{
	return this->_serverPassword;
}

void	Parsing::setArgument(std::string argument)
{
	this->_argument = argument;
}

const std::string	Parsing::getArgument() const
{
	return this->_argument;
}

void	Parsing::setLine(std::string line)
{
	this->_line = line;
}

const std::string	Parsing::getLine() const
{
	return this->_line;
}

void	Parsing::setRawCmd(std::string cmd)
{
	this->_rawCmd = cmd;
}

const std::string	Parsing::getRawCmd() const
{
	return this->_rawCmd;
}

void	Parsing::setInput(std::string input)
{
	this->_input = input;
}

const std::string	Parsing::getInput() const
{
	return this->_input;
}

void	Parsing::setConnected(bool connect)
{
	this->_connected = connect;
}

bool	Parsing::getConnected() const
{
	return this->_connected;
}

Parsing::~Parsing()
{
	
}