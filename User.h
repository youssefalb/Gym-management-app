#pragma once

#include "Loggable.h"




class User : public Loggable {
    int id; 
    std::string category;
    std::map <Specific_slot, std::shared_ptr<session>> private_schedule;
public:
    User(int _id, std::string _name, std::string _surname, std::string _category, std::string _login, size_t _hashed_pass);
    std::string getCategory() { return category;}
        int get_id() { return id;}
    std::map < Specific_slot, std::shared_ptr<session>> get_private_schedule();
    bool private_sessions_check(Specific_slot& s);
    void add_private_reservation(Specific_slot s , std::shared_ptr<session> &ses);
    void erase_reservation(Specific_slot s);
    void clear_reservations(); //to change 
    virtual void update_full_name_sessions()= 0;
};




inline User::User(int _id, std::string _name, std::string _surname, std::string _category, std::string _login, size_t _hashed_pass): id(_id), category(_category),
Loggable(_name, _surname, _login, _hashed_pass)
{
   
}

inline std::map<Specific_slot, std::shared_ptr<session>> User::get_private_schedule()
{
    return private_schedule;
}



inline bool User::private_sessions_check(Specific_slot& s)
{
    if (private_schedule.contains(s))
        return false;
    else
        return true;
}


inline void User::add_private_reservation(Specific_slot s, std::shared_ptr<session>& ses)
{
    private_schedule[s] = ses;
}

inline void User::erase_reservation(Specific_slot  s)
{
    private_schedule.erase(s);
}



inline void User::clear_reservations()
{
    private_schedule.clear();
}

