#pragma once


#include"Trainer_registration_controller.h"
class Member_registration_controller {

	Validator validator;
public:

	bool Check_password_security(std::string user_password);
	bool check_if_member_login_is_unique(std::string login_to_check);
	void register_member(std::string name, std::string surname, std::string category, std::string login, std::string password, std::string level);

};

inline bool Member_registration_controller::Check_password_security(std::string user_password)
{
	return validator.Check_password_security(user_password);
}

inline bool Member_registration_controller::check_if_member_login_is_unique(std::string login_to_check)
{
	return validator.check_if_member_login_is_unique(login_to_check);
}

inline void Member_registration_controller::register_member(std::string name, std::string surname, std::string category, std::string login, std::string password, std::string level)
{
	Database_manager::getInstance()->create_new_member(name, surname, category, login,get_hash(password), level);
}
