#pragma once
#include"DB.h"





class Database_manager {
	static Database_manager* s_instance;
	std::shared_ptr<Database> database;

protected:
	Database_manager() {
		database = std::make_shared<Database>();
		std::thread th_read_data(&Database::read_data, database);
		std::thread th_read_programs(&Database::read_workout_programs, database);
		th_read_data.join();
		th_read_programs.join();
	}
public:

	std::unordered_map<int, std::shared_ptr<Trainer>> get_trainers_from_db();
	std::unordered_map<int, std::shared_ptr<Member>> get_members_from_db();
	std::shared_ptr<Admin> get_admin_from_db();
	std::vector < std::string > get_member_logins();
	std::vector < std::string > get_trainers_logins();
	std::unordered_map<std::string, int > get_trainers_names_ids();
	std::unordered_map<int, std::shared_ptr<Trainer>> get_trainers_by_category(std::string category);
	static Database_manager* getInstance();

	void create_new_member(std::string name, std::string surname, std::string category, std::string login, size_t password, std::string level);
	void create_new_trainer(std::string name, std::string surname, std::string category, std::string login, size_t password);

	void delete_member(int _id);
	void delete_trainer(int _id);

	bool update_data();

	std::map<Specific_slot, std::shared_ptr<Main_session>> get_private_sessions_from_db() { return database->get_sessions();};

	std::shared_ptr<session> add_ids_to_private_sessions(Specific_slot &s, int member_id, int trainer_id, std::string description);
	void delete_ids_from_sessions(Specific_slot& s, int member_id);

	std::pair<int, int> total_members_trainers();

	std::vector<std::shared_ptr<Workout_program>> get_body_building_program(std::string _level);

	std::vector<std::shared_ptr<Workout_program>> get_fitnnes_program(std::string _level);

	void reservartion_cleanup_member(int id);
	void reservartion_cleanup_trainer(int id);
};


inline std::unordered_map<int, std::shared_ptr<Trainer>> Database_manager::get_trainers_from_db()
{
	return database->get_trainers();
}

inline std::unordered_map<int, std::shared_ptr<Member>> Database_manager::get_members_from_db()
{
	return database->get_members();
}
inline std::shared_ptr<Admin> Database_manager::get_admin_from_db()
{
	return database->get_admin();
}
inline std::vector<std::string> Database_manager::get_member_logins()
{
	std::vector<std::string> logins;
	for (auto member : database->get_members()) {
		logins.push_back(member.second->getlogin());
	}
	return logins;
}

inline std::vector<std::string> Database_manager::get_trainers_logins()
{
	std::vector<std::string> logins;
	for (auto trainer : database->get_trainers()) {
		logins.push_back(trainer.second->getlogin());
	}
	return logins;
}


inline std::unordered_map<std::string, int> Database_manager::get_trainers_names_ids()
{
	std::unordered_map<std::string, int> trainers_data_copy;
	for (auto& tr : database->get_trainers()) {
		trainers_data_copy[tr.second->getname()] = tr.first;
	}
	return trainers_data_copy;
}

inline std::unordered_map<int, std::shared_ptr<Trainer>> Database_manager::get_trainers_by_category(std::string category)
{
	auto mapa = database->get_trainers();
	std::unordered_map<int, std::shared_ptr<Trainer>> trainer_map;

	std::ranges::copy_if(mapa.begin(), mapa.end(), std::inserter(trainer_map, trainer_map.end()), [&](std::pair<int, std::shared_ptr<Trainer>> const& trainer) {
		return trainer.second->getCategory() == category;
		});
	return  trainer_map;
}


inline Database_manager* Database_manager::getInstance()
{
	if (!s_instance)
		s_instance =  new Database_manager;
	return s_instance;
}

inline void Database_manager::create_new_member(std::string name, std::string surname, std::string category, std::string login, size_t password,std::string level)
{
	database->add_member_record(name, surname, category, login, password, level);
}

inline void Database_manager::create_new_trainer(std::string name, std::string surname, std::string category, std::string login, size_t password)
{
	database->add_trainer_record(name, surname, category, login, password);
}



inline void Database_manager::delete_member(int _id)
{
	database->erase_member(_id);
}

inline void Database_manager::delete_trainer(int _id)
{
	database->erase_trainer(_id);

}


inline bool Database_manager::update_data()
{
	return database->update_data();
}



inline std::shared_ptr<session> Database_manager::add_ids_to_private_sessions(Specific_slot &s, int member_id, int trainer_id, std::string description)
{
	return database->add_private_session(s, member_id, trainer_id, description);
}

inline void Database_manager::delete_ids_from_sessions(Specific_slot& s, int member_id)
{
	database->delete_ids_from_session(s, member_id);
}


inline std::pair<int, int> Database_manager::total_members_trainers()
{
	return std::pair<int, int>(database->trainers_size(), database->members_size());
}

inline std::vector<std::shared_ptr<Workout_program>> Database_manager::get_body_building_program(std::string _level)
{
	std::vector<std::shared_ptr<Workout_program>> bd_programs{};
	auto existing_programs = database->get_body_building_programs();
	std::ranges::copy_if(existing_programs.begin(), existing_programs.end(),
		std::back_inserter(bd_programs), [&_level](std::shared_ptr<Workout_program> &program) {
			return program->get_program_level() == _level;
		}
	);
	return bd_programs;
}
inline std::vector<std::shared_ptr<Workout_program>> Database_manager::get_fitnnes_program(std::string _level)
{
	std::vector<std::shared_ptr<Workout_program>> fit_programs{};
	auto existing_programs = database->get_fitnnes_programs();
	std::ranges::copy_if(existing_programs.begin(), existing_programs.end(),
		std::back_inserter(fit_programs), [&_level](std::shared_ptr<Workout_program> &program) {
			return program->get_program_level() == _level;
		}
	);
	return fit_programs;
}


inline void Database_manager::reservartion_cleanup_member(int id)
{
	database->clear_sessions_by_mb_id(id);
}

inline void Database_manager::reservartion_cleanup_trainer(int id)
{
	database->clear_sessions_by_tr_id(id);
}


