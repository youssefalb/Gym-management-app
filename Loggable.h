#pragma once
#include "Session.h"


class Loggable {
	std::string login;
	size_t hashed_password;
	std::string surname;
	std::string name;
public:
	Loggable( std::string _name, std::string _surname, std::string _login, size_t _hashed_pass) :
		 name(_name), surname(_surname),  login(_login), hashed_password(_hashed_pass) {}
	std::string getFullName() { return name + " " + surname; }
	std::string getlogin() { return login; }
	std::string getname() { return name; }
	std::string get_surname() { return surname; }

	size_t get_hashed_password() { return hashed_password; }
	std::string getsurname() { return surname; }
	void change_name(std::string _name);
	void change_surname(std::string _surname);
	void change_password(size_t _hashed_password);
	void reset_password();
};

inline void Loggable::change_name(std::string _name)
{
	name = _name;
}

inline void Loggable::change_surname(std::string _surname)
{
	surname = _surname;
}

inline void Loggable::change_password(size_t _hashed_password)
{
	hashed_password = _hashed_password;
}

inline void Loggable::reset_password()
{
	hashed_password = get_hash("");
}