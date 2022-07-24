#pragma once

#include"Base_reservation_controller.h"



class Special_program_controller : public Base_reservation_controller {
	std::vector<std::shared_ptr<Workout_program>> special_programs_found;
public: 
	Special_program_controller(std::string level);
	std::vector<std::vector< std::string>> get_sessions();
	bool search_for_programs(std::string _category, std::string level);
	std::shared_ptr<Workout_program> get_program() { return NULL; }
	bool days_duplicate_checking(std::vector <int> chosen_weeks);
	bool diferent_week_checking(std::vector <int> _chosen_days);
};


inline Special_program_controller::Special_program_controller(std::string _category): Base_reservation_controller(_category)
{

}
inline std::vector<std::vector<std::string>> Special_program_controller::get_sessions()
{
	std::vector<std::vector<std::string>> sessions;
	for (auto& program : special_programs_found) {
		sessions.push_back(program->get_program_sessions());
	}
	return sessions;

}
inline 	bool Special_program_controller::search_for_programs(std::string category, std::string level) {

	if (category == "Body_building") {//move to constants!!!
		if (!Database_manager::getInstance()->get_body_building_program(level).empty()) {
			special_programs_found = Database_manager::getInstance()->get_body_building_program(level);
			return true;
		}
		return false;
	}
	else {
		if (!Database_manager::getInstance()->get_fitnnes_program(level).empty()) {
			special_programs_found = Database_manager::getInstance()->get_fitnnes_program(level);
				return true;
			}
		}
	return false;
}


inline bool Special_program_controller::days_duplicate_checking(std::vector <int> _chosen_days)
{
	sort(_chosen_days.begin(), _chosen_days.end());
	auto it = std::unique(_chosen_days.begin(), _chosen_days.end());
	bool wasUnique = (it == _chosen_days.end());

	return wasUnique;
}

inline bool Special_program_controller::diferent_week_checking(std::vector<int> chosen_weeks)
{
	return std::ranges::adjacent_find(chosen_weeks.begin(), chosen_weeks.end(), std::not_equal_to<int>()) == chosen_weeks.end();
}


