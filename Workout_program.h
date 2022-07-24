#pragma once

#include "User.h"


//MOVE to sperate files!!!
class Workout_program {
    std::vector <std::string> assigned_sessions;
    std::string level;

public:
    std::string get_program_level() { return level; }
    std::vector < std::string > get_program_sessions() { return assigned_sessions; }
    Workout_program(Json::Value _data) :level(_data["level"].asString()) {
        for (auto x : _data["sessions"]) {
            assigned_sessions.push_back(x["About"].asString());
        }
    }
};