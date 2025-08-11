/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:33:16 by lelanglo          #+#    #+#             */
/*   Updated: 2025/08/11 14:33:30 by bfiquet          ###   ########.fr       */
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
		std::string _username;
		std::string _nickname;
		int			_socket;
		std::string	_hasNickname;
		std::string	_hasUser;
	
	public:
		User(int socket);
		User();
		User &operator=(User &other);
		User(int socketfd, std::string username, std::string nickname);
		~User();
		const std::string getUsername() const;
		const std::string getNickname() const;
		int 				getSocket() const;
};