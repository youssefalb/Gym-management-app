#pragma once

#include "Main_controller.h"


class Csv_creator_controller {



public:
    Csv_creator_controller()= default;
	fs::path get_path(fs::path dir_path, std::string filename);
	int get_file_number(fs::path &_path);
	bool create_sessions_file(std::vector < std::vector < std::string>> &sessions);
	bool create_members_file(std::vector < std::vector < std::string>> &members);
	bool create_trainers_file(std::vector < std::vector < std::string>> &members);
};

inline fs::path Csv_creator_controller::get_path(fs::path dir_path, std::string filename)
{
	fs::path path_trial = dir_path /( filename + ".csv");
	if (!fs::exists(path_trial)) {
		return path_trial;
	}
	else {
		int file_number = get_file_number(dir_path);
        dir_path /= (filename + "("+std::to_string(file_number) + ").csv");
        return dir_path;
	}
}

inline int Csv_creator_controller::get_file_number(fs::path& _path)
{
    std::vector<int> file_numbers{ 1 };

    for (auto& entry : fs::recursive_directory_iterator(_path)) {
        std::string file_1 = entry.path().stem().string();
        std::smatch match;
        std::regex rgx("\\((.*?)\\)");
        for (std::sregex_iterator it = std::sregex_iterator(
            file_1.begin(), file_1.end(), rgx);
            it != std::sregex_iterator(); it++)
        {
            match = *it;
            file_numbers.push_back(stoi(match.str(1)) + 1);
        }
    }
    return  *std::max_element(file_numbers.begin(), file_numbers.end());
}

inline bool Csv_creator_controller::create_sessions_file(std::vector <std::vector<std::string>>& sessions) {
   fs::path created_path = get_path(SESSIONS_PATH, "gym_sessions");
   std::ofstream ofile(created_path);
   if (ofile.is_open()) {
       ofile << "Trainer" <<"," << "Day"<< "," << "Slot" <<"," << "Session"<<","<< "Member"<<"\n";
       for (auto row : sessions)
           ofile << row[0] << "," << row[1] << "," << row[2] << "," << row[3]<< "," << row[4]<< "\n";
       ofile.close();
       return true;
   }
   return false;

}

inline bool Csv_creator_controller::create_members_file(std::vector<std::vector<std::string>>& members)
{
    fs::path created_path = get_path(MEMBERS_PATH, "gym_members");
    std::ofstream ofile(created_path);
    if (ofile.is_open()) {
        ofile << "Name" << "," << "Surname" << "," << "Category" << "," << "Level" << "\n";
        for (auto row : members)
            ofile << row[0] << "," << row[1] << "," << row[2] << "," << row[3] << "\n";
        ofile.close();
        return true;
    }
    return false;
}

inline bool Csv_creator_controller::create_trainers_file(std::vector<std::vector<std::string>>& trainers)
{
    fs::path created_path = get_path(TRAINERS_PATH, "gym_trainers");
    std::ofstream ofile(created_path);
    if (ofile.is_open()) {
        ofile << "Name" << "," << "Surname" << "," << "Category"<< "\n";
        for (auto row : trainers)
            ofile << row[0] << "," << row[1] << "," << row[2]  << "\n";
        ofile.close();
        return true;
    }
    return false;
}
