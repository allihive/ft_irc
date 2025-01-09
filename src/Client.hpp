/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alli <alli@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:17:13 by alli              #+#    #+#             */
/*   Updated: 2025/01/09 13:40:55 by alli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <vector>
#include <iostream>
#include <string>

class Client {
	private:
		std::string _username;
		std::string _nickname;
		std::string _password;
		std::string _hostname;
		std::string _servername;
		std::vector<std::string> _realname;
		
		int _fd;
	public:
		Client();
		~Client();
		std::string getUsername();
		std::string getNickname();
		std::string getPassword();
		std::string getHostName();
		int 		getFd();
		bool allSet = false;
		
		//setters
		void setFd(int fd);
		void setNickname(std::string nickname);
		void setUsername(std::string username);
		void setHostName(std::string hostname);
		void setServername(std::string servername);
		void setRealname(std::string names);
		
		// std::vector<std::string> getServerInfo();
};

#endif
