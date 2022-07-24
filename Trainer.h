
#include <utility>

#include "Member.h"


// special by category 
class Trainer: public User {

    std::string categrory{};

public:
    Trainer(int _id, std::string _name, std::string _surname, std::string _category, std::string _login, size_t _hashed_pass);
    Trainer(Json::Value _data);

    void update_full_name_sessions();

};

inline Trainer::Trainer(int _id, std::string _name, std::string _surname, std::string _category, std::string _login, size_t _hashed_pass)
    : User(_id,  _name, _surname,_category,_login, _hashed_pass)
{
}

inline Trainer::Trainer(Json::Value _data)
    :User(_data["id"].asInt(), _data["name"].asString(), _data["surname"].asString(), _data["Category"].asString(), _data["login"].asString(), _data["password"].asUInt64())
{

}

inline void Trainer::update_full_name_sessions()
{

    for (auto ses : get_private_schedule()) {
        ses.second->member_name = getFullName();
    }

}

