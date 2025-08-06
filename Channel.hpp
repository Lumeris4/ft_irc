/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelanglo <lelanglo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:46:43 by lelanglo          #+#    #+#             */
/*   Updated: 2025/08/06 13:43:09 by lelanglo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "include.hpp"

class Channel;

class Channel
{
	private:
		std::string					_password;
		std::string					_name;
		int							_limit;
		std::string					_topic;
		bool						_access;
		std::vector<std::string>	_chef_usernames;
		std::vector<std::string>	_list_user;
		std::vector<std::string>	_invitate;

	public:
		Channel(std::string name, std::string creator);
		~Channel();
		void							setPassword(std::string pass);
		const std::string				getPassword() const;
		void							setLimit(int l);
		int								getLimit() const;
		void							setTopic(std::string topic);
		const std::string				getTopic() const;
		void							setAccess(bool n);
		bool							getAccess() const;
		const std::vector<std::string>	&getListUser() const;
		const std::vector<std::string>	&getListChef() const;
		const std::vector<std::string>	&getListInvitation() const;
		void							remote(std::string name);
		void							demote(std::string name);
		void							adduser(std::string name);
		void							addinvitation(std::string name);
};