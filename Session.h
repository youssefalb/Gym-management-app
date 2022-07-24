#pragma once
#include <fstream>
#include <memory>
#include <vector>
#include<algorithm>
#include<thread>
#include "Constants.h"
#include <regex>
#include <ranges>
#include <future>
#include "json.h"
#include <boost/date_time.hpp>


static std::hash<std::string> Myhasher;

static size_t get_hash(std::string password) {
    return Myhasher(password);
}


struct Specific_slot {
    boost::gregorian::date sample_date;
    int slot{};
    int get_day() { return sample_date.day_of_week(); }
    Specific_slot() = default;
    Specific_slot(boost::gregorian::date _date, int _slot) {
        sample_date = _date;
        slot = _slot;
    }
    friend bool operator ==(const Specific_slot& a, const Specific_slot& b) {
        if (a.sample_date == b.sample_date && a.slot == b.slot)
            return true;
        else
            return false;
    }
    bool operator<(const Specific_slot& a) const {
        if (a.sample_date == sample_date)
            return a.slot > slot;
        return a.sample_date > sample_date;
    }
};


struct session {

    std::string member_name;
    std::string trainer_name;
    std::string description;
    session(std::string _member_name, std::string _trainer_name, std::string _description) :
        member_name(_member_name), trainer_name(_trainer_name) , description(_description){}
    std::string get_description() { return description;}
    std::string get_trainer_name() { return trainer_name;}
    std::string get_member_name() { return member_name;}
};

class Main_session {

    std::map<std::pair<int, int>, std::shared_ptr <session>> current_sessions;
public:
    Main_session() = default;
    //to change pass it directly!!
    Main_session(Json::Value _data) {
        for (auto member_trainer : _data["member_trainer_ids"])
            current_sessions[{member_trainer["member_id"].asInt(), member_trainer["trainer_id"].asInt()}] = std::make_shared<session>(member_trainer["member_name"].asString(),
                member_trainer["trainer_name"].asString(), member_trainer["description"].asString());
    }
    std::map<std::pair<int, int>, std::shared_ptr <session>> get_current_sessions() {
        return current_sessions;
    }
    void erase_a_session(std::pair<int, int> id_pair) {
        current_sessions.erase(id_pair);
    }
    void add_a_session(int member_id, int trainer_id, std::shared_ptr<session> ses) {
        current_sessions[{member_id, trainer_id}] = ses;
    }
};