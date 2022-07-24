#include "Admin_controller.h"



class Main_controller {
	
public:
	std::shared_ptr<Admin_controller> check_admin_login(std::string _username, std::string _password);
	std::shared_ptr<Trainer_win_controller> check_trainer_login(std::string _username, std::string _password);
	std::shared_ptr<Member_win_controller> check_member_login(std::string _username, std::string _password);

};




inline std::shared_ptr<Admin_controller> Main_controller::check_admin_login(std::string _username, std::string _password) {


	if (_username == Database_manager::getInstance()->get_admin_from_db()->getlogin() &&
		get_hash(_password) == Database_manager::getInstance()->get_admin_from_db()->get_hashed_password()) {
		return std::make_shared<Admin_controller>(Database_manager::getInstance()->get_admin_from_db());
	}
	return NULL;
}


inline std::shared_ptr<Trainer_win_controller> Main_controller::check_trainer_login(std::string _username, std::string _password)
{	
	size_t _hashed_password = get_hash(_password);
	auto trainers_map = Database_manager::getInstance()->get_trainers_from_db();
	auto it = std::ranges::find_if(trainers_map.begin(),
		trainers_map.end(),
		[&_username,_password](std::pair<int ,std::shared_ptr<Trainer>> const& trainer)
		{
			return (_username == trainer.second->getlogin() && get_hash(_password) == trainer.second->get_hashed_password());
		});

	if (trainers_map.end() != it) {
		return std::make_shared<Trainer_win_controller>(*it);
	}
	return NULL;
}



inline std::shared_ptr<Member_win_controller> Main_controller::check_member_login(std::string _username, std::string _password)
{
	size_t _hashed_password = get_hash(_password);
	auto members_map = Database_manager::getInstance()->get_members_from_db();
	auto it = std::ranges::find_if(members_map.begin(),
		members_map.end(),
		[&_username, _password](std::pair<int, std::shared_ptr<Member>> const& member)
		{
			return (_username == member.second->getlogin() && get_hash(_password) == member.second->get_hashed_password());
		});

	if (members_map.end() != it) {
		return std::make_shared<Member_win_controller>(*it);
	}
	return  NULL;
}


