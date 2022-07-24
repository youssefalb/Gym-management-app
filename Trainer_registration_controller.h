#pragma once
#include"special_program_controller.h"
class Trainer_registration_controller {

	Validator validator;
public:

	bool Check_password_security(std::string user_password);
	bool check_if_member_login_is_unique(std::string login_to_check);
	void register_trainer(std::string name, std::string surname, std::string category, std::string login, std::string password);

};

inline bool Trainer_registration_controller::Check_password_security(std::string user_password)
{
	return validator.Check_password_security(user_password);
}

inline bool Trainer_registration_controller::check_if_member_login_is_unique(std::string login_to_check)
{
	return validator.check_if_trainer_login_is_unique(login_to_check);
}

inline void Trainer_registration_controller::register_trainer(std::string name, std::string surname, std::string category, std::string login, std::string password)
{
	Database_manager::getInstance()->create_new_trainer(name, surname, category, login, get_hash(password));
}