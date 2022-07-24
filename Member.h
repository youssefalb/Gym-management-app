
#include "Workout_program.h"

class Member: public User{
     
    std::string level{};
public:
    Member(int id, std::string _name, std::string _surname, std::string _category, std::string _login, size_t _pass, std::string _level);
    Member(Json::Value _data);

    std::string get_level();
    void update_data(std::string& name, std::string &surname, std::string &level);
    void update_full_name_sessions();
};


inline Member::Member(int id, std::string _name, std::string _surname, std::string _category, std::string _login, size_t _pass, std::string _level)
    : User(id ,_name, _surname, _category, _login, _pass) 
{
    level = _level;
}


inline Member::Member(Json::Value _data) : User(_data["id"].asInt(),_data["name"].asString(), _data["surname"].asString(),
    _data["Sport_option"].asString(), _data["login"].asString(), _data["password"].asUInt64())
{
    level = _data["Level"].asString();
}

inline std::string Member::get_level()
{
    return level;
}

inline void Member::update_data(std::string& _name, std::string& _surname, std::string& _level)
{
    change_name(_name);
    change_surname(_surname);
    level = _level;
    update_full_name_sessions();
}



inline void Member::update_full_name_sessions()
{
    for (auto ses : get_private_schedule()) {
        ses.second->member_name = getFullName();
    }

}

