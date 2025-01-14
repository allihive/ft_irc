/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 13:05:45 by epolkhov          #+#    #+#             */
/*   Updated: 2025/01/14 15:04:54 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <algorithm>
#include <vector>

//#include "Client.hpp"
class Client;

class Channel
{
	private:
		std::string _name;
		std::string _password;
		std::vector<Client*> _users;
		std::vector<Client*> _operators;
		std::string _topic;
		int _userLimit;
		bool _exist;
		bool _inviteOnly;
		bool _topicRestricted;

	public:
		Channel(const std::string &name);
		~Channel();

		//Getters
		std::string getName() const;
		std::string getTopic() const;
		int getUserCount() const;
		std::string getPassword() const;
		std::vector<Client*> getUsers() const;

		bool doesExist() const;
		bool isInviteOnly() const;

		// User Management
		void addUser(Client* client);
		void removeUser(Client* client);
		bool isUserInChannel(Client* client) const;

		// Operator Management
		void addOperator(Client* client);
		void removeOperator(Client* client);
		bool isOperator(Client* client) const;
		void broadcastMessage(const std::string& sender, const std::string& message);

		// Channel Modes
		void setMode(char mode, bool enable, const std::string& param = "");
		void setTopic(const std::string& topic, Client* client);
		void setPassword(const std::string& password);
		bool checkPassword(const std::string& password) const;
};
