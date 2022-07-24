#pragma once

#include "Trainer_win_controller.h"

class Base_reservation_controller {

	std::unordered_map < std::string, std::shared_ptr<Trainer_win_controller>> trainers_controllers_map;
	std::vector < std::string> trainers_names; // there will be category ofr each trainer later so it should proabably be changeed
public:
	Base_reservation_controller(std::string _category);
	std::shared_ptr<Trainer_win_controller> get_trainer_controller(std::string trainer_fullname) { return trainers_controllers_map[trainer_fullname];}
	std::vector <std::string> get_trainers_names();
};



inline Base_reservation_controller::Base_reservation_controller(std::string _category)
{
	for (auto& tr_name_id : Database_manager::getInstance()->get_trainers_by_category(_category)) {
		trainers_controllers_map[tr_name_id.second->getFullName()] = std::make_shared<Trainer_win_controller>(tr_name_id);
		trainers_names.push_back(tr_name_id.second->getFullName());
	}
}

inline std::vector<std::string> Base_reservation_controller::get_trainers_names()
{
	return trainers_names;
}







