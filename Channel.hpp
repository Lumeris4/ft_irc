/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiquet <bfiquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:46:43 by lelanglo          #+#    #+#             */
/*   Updated: 2025/09/08 15:26:37 by bfiquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#define MAX_CLIENT 10
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
		bool						_access_topic;
		int							_members;
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
		void							remote(std::string nickname);
		void							demote(std::string nickname);
		void							adduser(std::string nickname);
		void							kickuser(std::string nickname);
		void							addinvitation(std::string nickname);
		void							baninvitation(std::string nickname);
		void							setAccessTopic(bool perm);
		bool							getAccessTopic() const;
		int								getMembers() const;
};
