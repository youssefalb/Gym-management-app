#include <iostream>
#include<map>
#include<QString>
#include <experimental/filesystem>  
#include <filesystem>  
namespace fs = std::filesystem;



static const  fs::path MY_PATH = (LR"(.\Database)");
static const fs::path ADMIN_PATH = (LR"(.\Admin_files)");
static const fs::path SESSIONS_PATH = ADMIN_PATH /"sessions_files";
static const fs::path TRAINERS_PATH = ADMIN_PATH /"trainers_files";
static const fs::path MEMBERS_PATH = ADMIN_PATH /"members_files";
static const fs::path TRAINERS_FILE_PATH = MY_PATH / "trainers.json";
static const fs::path MEMBERS_FILE_PATH = MY_PATH / "members.json";
static const fs::path SESSIONS_FILE_PATH = MY_PATH / "sessions.json";
static const fs::path ADMIN_FILE_PATH = MY_PATH / "admin.json";
static const fs::path PROGRAMS_FILE_PATH = MY_PATH / "gym_programs.json";


namespace MyConstants {
	static const std::string NO_LEVEL_STRING = "There is no level for you bro";
	//static std::string Data_file = "Data.json";
	static const std::string TEST_FILE = "test.json";
	static const std::string FITNNES_CATEGORY = "Fitnnes";
	static const std::string BD_CATEGORY = "Body_building";

}
namespace MyQtConstants {
	static const QString DAYS_DUPLICATE_FOUND = "According to the Gym policy, you can not have two sesssions in the same day!!";
	static const QString PROGRAM_RES_ALMOST_DONE = "Please note that all your workouts schedules will get removed since you signed for a special workout\nbut you stil can add additional sessions from the reservation window";
	static const QString UNSUCCESFUL_LOGIN = "Username or password are incorrect! \nPlease try Again";
	static const QString session_reservation_done = "Session reserved succefully \nPlease be at the exact time";
	static const QString session_booked = "Session already booked \nPlease choose another time slot";
	static const QString different_weeks_found = "Please choose the same starting week!";
	static const QString PASSWORD_RESET_CONFIRMATION = "Are you sure you want to reset this member's password";
	static const QString PORHIBITED_SESSION_DELETION = "The session is scheduled for today you can not delete it!";
	static const QString PASSWORD_SECURITY_REQUIREMNETS = "Password doesn't meet the security requirements\n"
														" - at least 8 characters\n"
														" - at least 1 capital letter\n"
														" - at least 1 lower letter\n"
														" - at least 1 number\n"
														" -special charachter";
	static const QString LOGIN_UNIQUE_REQUIREMNET = "Login is not unique, choose another one please";
	static const QString USER_DELETION_CONFIRMATION = "Are you sure you want to delete this user from the gym ?";
	static const QString USER_UPDATE_CONFIRMATION = "Are you sure you want to update this user";
	static const QString UPDATE_DATA_FAILED = "Your data was not updated, somthing went wrong";
	static const QString REGISTRATION_DONE = "Registration done successfully";
	static const QString WARNING_IMAGE_SOURCE = " < img src = 'warning.png' / > ";
	static const QString PROGRAM_NOT_FOUND = "We couldn't find a program for you";
	static const QString ADD_ICON_IMAGE = "Add_icon(2).png";
	static const QString PROGRAM_FOUND{ "We found a program for you, Click yes to confirm!\n" };
	static const QString BUTTON_DELETE_STYLE = "#bt_delete{ \nborder-style: outset; \nborder-radius: 10px; \nborder-color:#7D43E2; \nborder-width: 1px;\nfont: bold 12px; \npadding: 5px; \nbackground-color: #FFFFFF; \ncolor: #000000 }";
	static const QString BUTTON_UPDATE_STYLE = "#btn_update {\nborder-style: outset;\nborder-radius: 10px;\nborder-color:#7D43E2;\nborder-width: 1px;\nfont: bold 12px;\npadding: 5px;\nbackground-color: #7D43E2;\ncolor: #FFFFFF}";
	static const std::vector<QString> POSSIBLE_BD_SESSIONS = { "Lower Body + Core","Arms + Abs","Back + shoulders","Legs","Chest + abs",
		"Arms + Shoulders","Back + legs","Back(calisthenics)","Full Legs","Shoulders","Back + triceps"};
	static const std::vector<QString> POSSIBLE_FIT_SESSIONS = { "Full body workout","Cardio + stairs","Abs + running" };
}


namespace MyMaps {
	static std::map<std::string, int> MONTHS_TO_WEEKS{ {"1 month", 4} ,{"2 months", 8},{"3 months", 12} };
	//static std::map<int, std::string > days_map{ {1,"Monday"},{2, "Tuesday"},{3 ,"Wednesday"},
	//	{4, "Thursday"},{5, "Friday"}};
	//static std::map < std::string, int> reverse_days_map{ { "Monday", 1}, { "Tuesday" ,2 },
	//	{ "Wednesday", 3 }, { "Thursday", 4 }, {  "Friday",5 } };
	static std::map<int, std::string > slots_map{ {1,"8:00 - 10:00"},{2, "10:00 - 12:00"},
		{3 ,"14:00 - 16:00"},{4, "16:00 - 18:00"},{5, "18:00 - 20:00"} };
	static std::map< std::string, int > reverse_slots_map{ {"8:00 - 10:00",1},{ "10:00 - 12:00",2 }
	,{"14:00 - 16:00",3},{ "16:00 - 18:00",4},{ "18:00 - 20:00",5} };
}

