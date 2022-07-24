
#include"User_controller.h"

class Trainer_win_controller: public User_controller{

    std::pair<int, std::shared_ptr<Trainer>> current_tr;
public:
    Trainer_win_controller(std::pair<int, std::shared_ptr<Trainer>> _current_tr);

    std::shared_ptr<Trainer> get_trainer() { return current_tr.second;}
    void add_private_session(Specific_slot &s , std::shared_ptr<session> &ses);
    void delete_user();
    void clear_previous_reservation();
    std::vector<std::vector<std::string>> get_private_schedule();
    int get_id() { return current_tr.first;}
};

inline Trainer_win_controller::Trainer_win_controller(std::pair<int, std::shared_ptr<Trainer>> _current_tr) :current_tr(_current_tr),
User_controller(_current_tr.second)
{
}


inline void Trainer_win_controller::add_private_session(Specific_slot& s, std::shared_ptr<session>& ses)
{
    current_tr.second->add_private_reservation(s, ses);
}

inline void Trainer_win_controller::delete_user()
{
    Database_manager::getInstance()->delete_trainer(current_tr.first);
    clear_previous_reservation();
}

inline void Trainer_win_controller::clear_previous_reservation()
{
    //threads
    std::thread th_1(&User::clear_reservations, current_tr.second);
    std::thread th_2(&Database_manager::reservartion_cleanup_trainer, Database_manager::getInstance(),current_tr.first);
    th_1.join();
    th_2.join();
}


inline std::vector<std::vector<std::string>> Trainer_win_controller::get_private_schedule()
{
    std::vector<std::vector<std::string>> schedule_copy;
    for (auto [time, ses] : current_tr.second->get_private_schedule()) {
        std::string date = boost::gregorian::to_iso_extended_string(time.sample_date);
        schedule_copy.push_back({ ses->get_member_name(),date, MyMaps::slots_map[time.slot], ses->get_description() });
    }
    return schedule_copy;
}

