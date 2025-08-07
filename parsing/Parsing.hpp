/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 13:11:37 by bfiquet           #+#    #+#             */
/*   Updated: 2025/08/07 11:23:42 by bfiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include.hpp"

class Parsing
{
	protected:
		std::string _input;
		std::string _serverPassword;
		bool		_connected;
		std::string _line;
		std::string _rawCmd;
		std::string _argument;
	
	public:
		Parsing();
		~Parsing();

		int 				check_password(std::string password);
		int 				parsing (char *buf, std::string password);
		void				setServerPassword(std::string password);
		const std::string	getServerPassword() const;
		void				setArgument(std::string argument);
		const std::string	getArgument() const;
		void				setLine(std::string line);
		const std::string	getLine() const;
		void				setCmds(std::string cmds);
		const std::string	getCmds() const;
		void				setRawCmd(std::string cmds);
		const std::string	getRawCmd() const;
		void				setInput(std::string input);
		const std::string	getInput() const;
		void				setConnected(bool connect);
		bool				getConnected() const;
};	