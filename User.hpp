/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:33:16 by lelanglo          #+#    #+#             */
/*   Updated: 2025/08/19 13:08:49 by bfiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "include.hpp"
#include "Channel.hpp"
#include "Server.hpp"

class User;

class User
{
	private:
		std::string 			 _username;
		std::string 			 _nickname;
		int						 _socket;
		std::string				 _leftover;
		bool					 first_mode;
		bool					 connected;
		bool					 capDone;
	
	public:
		User(int socket);
		User();
		User &operator=(User &other);
		User(int socketfd, std::string username, std::string nickname);
		~User();
		const std::string	getUsername() const;
		const std::string	getNickname() const;
		void				setNickname(std::string nickname);
		void				setUsername(std::string username);
		void				setCap(bool cap);
		bool				getCap();
		void				setConnected(bool cap);
		bool				getFirstmode();
		void				setFirstmode(bool first);
		bool				getConnected();
		void 				clearHistory();
		void				setLeftover(std::string leftover);
		std::string			getLeftover();
		int 				getSocket() const;
};