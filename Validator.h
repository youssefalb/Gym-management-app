#pragma once

#include "Database_manager.h"

class Validator {

public:
     bool Check_password_security(std::string user_password);
     bool check_if_member_login_is_unique(std::string login_to_check);
     bool check_if_trainer_login_is_unique(std::string login_to_check);
};

inline bool Validator::Check_password_security(std::string user_password)
{
    std::regex upper_case_expression{ "[A-Z]+" };
    std::regex lower_case_expression{ "[a-z]+" };
    std::regex digit_expression{ "[0-9]+" };
    std::regex eight_charachters{ ".{8,}" };
    std::regex special_charachters{ R"([!"\\$%&'()+,-./:;=#@?[\]^_`{|}~*])" };

    bool upper_case = std::regex_search(user_password, upper_case_expression);
    bool lower_case = std::regex_search(user_password, lower_case_expression);
    bool number_case = std::regex_search(user_password, digit_expression);
    bool eight_char = std::regex_search(user_password, eight_charachters);
    bool sp_char = std::regex_search(user_password, special_charachters);
    if (upper_case && lower_case && number_case && eight_char && sp_char)
        return true;
    else
        return false;
}

inline bool Validator::check_if_member_login_is_unique(std::string login_to_check)
{
    std::vector<std::string> logins_copy = Database_manager::getInstance()->get_member_logins();
    if (std::ranges::find(logins_copy.begin(), logins_copy.end(), login_to_check) != logins_copy.end()) {
        return false;
    }
    return true;
}

inline bool Validator::check_if_trainer_login_is_unique(std::string login_to_check)
{
    std::vector<std::string> logins_copy = Database_manager::getInstance()->get_trainers_logins();
    if (std::ranges::find(logins_copy.begin(), logins_copy.end(), login_to_check) != logins_copy.end()) {
        return false;
    }
    return true;
}
