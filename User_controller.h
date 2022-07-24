#pragma once
#include "Validator.h"
class User_controller {

    std::shared_ptr<User> current_user;
    Validator validator;

public:
    User_controller( std::shared_ptr<User> _current_user): current_user(_current_user) {}
    std::string getname() { return current_user->getname(); }
    std::string getlogin() { return  current_user->getlogin(); }
    std::string getsurname() { return current_user->getsurname(); }
    std::string getCategory() { return current_user->getCategory(); }
    std::string getFullName() { return current_user->getFullName(); }
    void reset_password() { current_user->reset_password(); }
    void change_password(std::string password) { current_user->change_password(get_hash(password)); }
    bool check_current_password(std::string password);
    bool Check_password_security(std::string user_password);
    bool check_private_availability(Specific_slot& s);
    virtual int get_id() = 0;
    virtual void delete_user() = 0;

};

inline bool User_controller::check_current_password(std::string password)
{
    size_t real_password_hash = get_hash(password);
    return  real_password_hash == current_user->get_hashed_password();
}
inline bool User_controller::Check_password_security(std::string user_password)
{
    return validator.Check_password_security(user_password);
}

inline bool User_controller::check_private_availability(Specific_slot& s)
{
    return current_user->private_sessions_check(s);
}




