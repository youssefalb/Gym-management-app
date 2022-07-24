#pragma once
#include"Member_win_controller.h"

class Admin_controller {

	std::unordered_map<int, std::shared_ptr<Member_win_controller>> member_controllers_map;
	std::unordered_map<int, std::shared_ptr<Trainer_win_controller>> trainer_controllers_map;
	std::shared_ptr<Admin> admin;

public:
	Admin_controller(std::shared_ptr<Admin> _admin):admin(_admin) {}
	std::string getname() { return admin->getname(); }
	std::string getsurname() { return admin->getsurname(); }
	std::map<int, std::vector<std::string>> get_trainers_data();
	std::vector<std::vector<std::string>> get_sessions();
	std::map<int, std::vector<std::string>> get_members_data();
	std::shared_ptr<Member_win_controller> get_member_controller(int _id);
	std::shared_ptr<Trainer_win_controller> get_trainer_controller(int _id);
	void delete_member_from_gym(int id);
	void delete_trainer_from_gym (int id);
};

inline std::map<int, std::vector<std::string>> Admin_controller::get_trainers_data() {
	std::map<int, std::vector<std::string>> trainers_data_copy;
	for (auto trainer : Database_manager::getInstance()->get_trainers_from_db()) {
		trainer_controllers_map[trainer.first] = std::make_shared<Trainer_win_controller>(trainer);
		trainers_data_copy[trainer.first] = { trainer.second->getname(),trainer.second->getsurname(), trainer.second->getCategory() };
	}
	return trainers_data_copy;
}

inline std::vector<std::vector<std::string>> Admin_controller::get_sessions()
{
	std::vector<std::vector<std::string>> schedule_copy{};

	for (auto main_session : Database_manager::getInstance()->get_private_sessions_from_db()) {
		std::string date = boost::gregorian::to_iso_extended_string(main_session.first.sample_date);
		for (auto [time, ses] : main_session.second->get_current_sessions()) {
			schedule_copy.push_back({ ses->get_trainer_name(),date, MyMaps::slots_map[main_session.first.slot],ses->get_member_name(), ses->get_description() });
		}
	}
	return schedule_copy;
}
inline std::map<int , std::vector<std::string>> Admin_controller::get_members_data()
{
	std::map<int, std::vector<std::string>> members_data_copy;

	for (auto member : Database_manager::getInstance()->get_members_from_db()) {
		member_controllers_map[member.first] = std::make_shared<Member_win_controller>(member);
		members_data_copy[member.first] = { member.second->getname(), member.second->getsurname(), member.second->getCategory(), member.second->get_level() }; 
	}
	return members_data_copy;
}

inline std::shared_ptr<Member_win_controller> Admin_controller::get_member_controller(int _id)
{
	return member_controllers_map[_id];
}

inline std::shared_ptr<Trainer_win_controller> Admin_controller::get_trainer_controller(int _id)
{
	return  trainer_controllers_map[_id];
}

inline void Admin_controller::delete_member_from_gym(int id)
{
	member_controllers_map[id]->delete_user();
}

inline void Admin_controller::delete_trainer_from_gym(int id)
{
	trainer_controllers_map[id]->delete_user();

}
