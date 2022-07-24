#pragma once
#include "Member_registration_controller.h"
class Member_win_controller : public User_controller{
    std::pair <int, std::shared_ptr<Member>> current_mb;
    std::map<int, Specific_slot> scheduleMapTrack;
public:
    Member_win_controller(std::pair <int, std::shared_ptr<Member>> _current_mb);
    std::string get_level() { return current_mb.second->get_level();}
    void clear_previous_reservation();
    void delete_user();
    bool reserve_private_session(std::shared_ptr<Trainer_win_controller> tr, std::string description, Specific_slot& sp_slot);
    std::vector < std::pair<int, std::vector<std::string>>> get_private_schedule();
    int get_id() { return current_mb.first; }
    void update_member_data(std::string& _name, std::string& _surname, std::string& _level);
  
    bool delete_session_by_slot_id(int session_id);
};

inline Member_win_controller::Member_win_controller(std::pair<int, std::shared_ptr<Member>> _current_mb) :current_mb(_current_mb), 
User_controller(_current_mb.second)
{
}


inline void Member_win_controller::delete_user()
{
    Database_manager::getInstance()->delete_member(current_mb.first);
    clear_previous_reservation();
}


inline void Member_win_controller::clear_previous_reservation()
{
    //threads
    current_mb.second->clear_reservations();
    Database_manager::getInstance()->reservartion_cleanup_member(current_mb.first);
}


inline bool Member_win_controller::reserve_private_session(std::shared_ptr<Trainer_win_controller> tr, std::string description, Specific_slot &sp_slot)
{

    std::shared_ptr<session>  session_to_reserve = Database_manager::getInstance()->add_ids_to_private_sessions(sp_slot, current_mb.first, tr->get_id(), description);
    tr->add_private_session( sp_slot,session_to_reserve);
    current_mb.second->add_private_reservation(sp_slot, session_to_reserve);
    return true;
}




inline std::vector<std::pair<int, std::vector<std::string>>> Member_win_controller::get_private_schedule()
{
    scheduleMapTrack.clear();
    std::vector < std::pair<int, std::vector<std::string>>> schedule_copy;
    int  session_id = 0;
    for (auto &[time, ses] : current_mb.second->get_private_schedule()) {
        std::string date = boost::gregorian::to_iso_extended_string(time.sample_date);
        schedule_copy.push_back({session_id, { ses->get_trainer_name(),date, MyMaps::slots_map[time.slot], ses->get_description() } });
        scheduleMapTrack[session_id] = time;
        session_id++;
    }
    return schedule_copy;
}

inline void Member_win_controller::update_member_data(std::string& _name, std::string& _surname, std::string& _level)
{
    current_mb.second->update_data(_name, _surname, _level);
}

inline bool Member_win_controller::delete_session_by_slot_id(int session_id)
{ 
    if (scheduleMapTrack[session_id].sample_date == boost::gregorian::day_clock::local_day()){
        return false;
    }   
    current_mb.second->erase_reservation(scheduleMapTrack[session_id]);
    Database_manager::getInstance()->delete_ids_from_sessions(scheduleMapTrack[session_id],current_mb.first);
    return true;
}
