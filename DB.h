

#include"Admin.h"


class Database {
    std::shared_ptr<Admin> admin;
    std::vector<std::shared_ptr<Workout_program>> fitnnes_programs;
    std::vector<std::shared_ptr<Workout_program>> body_building_programs;
    std::unordered_map<int, std::shared_ptr<Member> > members_map;
    std::unordered_map<int, std::shared_ptr<Trainer> >trainers_map;
    std::map<Specific_slot, std::shared_ptr<Main_session>> sessions;
    std::vector<int> ids;
public:
    Database() { ids.reserve(100); };
    std::unordered_map<int, std::shared_ptr<Member> > get_members(){ return members_map;};
    std::unordered_map<int, std::shared_ptr<Trainer> > get_trainers() { return trainers_map;};
    std::map<Specific_slot, std::shared_ptr<Main_session>>get_sessions() { return sessions; };
    std::shared_ptr<Admin> get_admin() { return admin; };
    int trainers_size();
    int members_size();
    void add_member_record(std::string name, std::string surname, std::string category, std::string login, size_t password, std::string level);
    bool update_data();
    void add_trainer_record(std::string name, std::string surname, std::string category, std::string login, size_t password);
    bool read_data();
    void read_members(bool &ember_read);
    void read_trainers(bool &trainers_read);
    void read_admin_data(bool &admin_read);
    void read_private_sessions(bool &sessions_read);
    void update_private_sessions(bool &sessions_updated);
    void update_members(bool &members_updated);
    void update_trainers(bool &trainers_updated);
    void update_admin(bool &admin_updated);
    void filter_sessions();
    std::shared_ptr<session> add_private_session(Specific_slot date, int member_id, int trainer_id, std::string description);
    void assign_sessions();
    void clear_sessions_by_mb_id(int mb_id);
    void clear_sessions_by_tr_id(int tr_id);
    void delete_ids_from_session(Specific_slot& s, int member_id);
    bool read_workout_programs();
    std::vector<std::shared_ptr<Workout_program>>  get_body_building_programs() { return body_building_programs; };
    std::vector<std::shared_ptr<Workout_program>> get_fitnnes_programs() { return fitnnes_programs; };
    void erase_member(int _id);
    void erase_trainer(int _id);
};


inline int Database::trainers_size()
{
    return trainers_map.size();
}

inline int Database::members_size()
{
    return members_map.size();
}


//change to map and increment the id counter
inline void Database::add_member_record(std::string name, std::string surname, std::string category, std::string login, size_t password, std::string level)
{
    int max_id = *std::max_element(ids.begin(), ids.end());
    members_map.insert({ max_id + 1, std::make_shared<Member>(max_id + 1,name, surname, category, login, password, level) });
    ids.push_back(max_id + 1);
}


inline bool Database::update_data()
{
    bool members_updated, trainers_updated, admin_updated, sessions_updated;
    std::thread th_mbs_upd(&Database::update_members, this, std::ref(members_updated));
    std::thread th_tr_upd(&Database::update_trainers, this, std::ref(trainers_updated));
    std::thread th_ad_upd(&Database::update_admin, this, std::ref(admin_updated));
    std::thread th_ses_upd(&Database::update_private_sessions, this, std::ref(sessions_updated));
    th_mbs_upd.join();
    th_tr_upd.join();
    th_ad_upd.join();
    th_ses_upd.join();
    if (members_updated && trainers_updated && admin_updated && sessions_updated) {
        return true;
    }
    return false;
}

inline void Database::add_trainer_record(std::string name, std::string surname, std::string category, std::string login, size_t password)
{
    int max_id = *std::max_element(ids.begin(), ids.end());
    trainers_map.insert({ max_id + 1, std::make_shared<Trainer>(max_id + 1,name, surname, category, login, password) });
    ids.push_back(max_id + 1);
}

inline bool Database::read_data()
{
    bool members_read, trainers_read, admin_read, sessions_read;
    std::thread th_mbs_rd(&Database::read_members, this, std::ref(members_read));
    std::thread th_tr_rd(&Database::read_trainers, this, std::ref(trainers_read));
    std::thread th_ad_rd(&Database::read_admin_data, this, std::ref(admin_read));
    std::thread th_ses_rd(&Database::read_private_sessions, this, std::ref(sessions_read));
    th_mbs_rd.join();
    th_tr_rd.join();
    th_ad_rd.join();
    th_ses_rd.join();
    if (members_read && trainers_read && admin_read && sessions_read) {
        assign_sessions();
        return true;
    }
    return false;
 
}

inline void Database::read_members(bool &member_read)
{
    Json::Value JsonData;
    Json::Reader reader;
    std::ifstream Infile(MEMBERS_FILE_PATH, std::ios::binary);
    if (Infile.is_open()) {
        reader.parse(Infile, JsonData);
        for (auto member : JsonData["Members"]) {
            int id = member["id"].asInt();
            members_map.insert({ id,std::make_shared<Member>(member) });
             ids.push_back(id);
        }
        Infile.close();
        member_read = true;
    }
    else member_read = false;
}

inline void Database::read_trainers(bool &trainers_read)
{
    Json::Value JsonData;
    Json::Reader reader;
    std::ifstream Infile(TRAINERS_FILE_PATH, std::ios::binary);
    if (Infile.is_open()) {
        reader.parse(Infile, JsonData);
        for (auto trainer : JsonData["Trainers"]) {
            int id = trainer["id"].asInt();
            trainers_map.insert({id,std::make_shared<Trainer>(trainer) });
            ids.push_back(id);
        }
        Infile.close();
        trainers_read= true;
       
    }
    else trainers_read = false;
}

inline void Database::read_admin_data(bool& admin_read)
{
    Json::Value JsonData;
    Json::Reader reader;
    std::ifstream Infile(ADMIN_FILE_PATH, std::ios::binary);
    if (Infile.is_open()) {
        reader.parse(Infile, JsonData);
        admin = std::make_shared<Admin>(JsonData["login"].asString(), JsonData["name"].asString(), JsonData["surname"].asString(), JsonData["password"].asUInt64());
        Infile.close();
        admin_read= true;
       
    }
    else admin_read = false;
}


inline void Database::read_private_sessions(bool &sessions_read)
{
    Json::Value JsonData;
    Json::Reader reader;
    std::ifstream Infile(SESSIONS_FILE_PATH, std::ios::binary);
    if (Infile.is_open()) {
        reader.parse(Infile, JsonData);
        for (auto session : JsonData["Private_sessions"]) {
            boost::gregorian::date date = boost::gregorian::from_string(session["Date"].asString());
            int slot = session["Slot"].asInt64();
            sessions[Specific_slot(date, slot)] = std::make_shared<Main_session>(session);
        }
        Infile.close();
        filter_sessions();
        sessions_read = true;
    }
    else sessions_read = false;
}

inline void Database::update_private_sessions(bool& sessions_updated)
{

    Json::Value JsonData;
    std::fstream Ofile(SESSIONS_FILE_PATH , std::ofstream::out | std::ofstream::trunc);
    if (Ofile.is_open()) {
        int i = 0, j ;
            for (auto main_session : sessions) {
                JsonData["Private_sessions"][i]["Date"] = boost::gregorian::to_iso_extended_string(main_session.first.sample_date);
                JsonData["Private_sessions"][i]["Slot"] = main_session.first.slot;
            
                j = 0;
                for (auto ses : main_session.second->get_current_sessions()){
                    JsonData["Private_sessions"][i]["member_trainer_ids"][j]["member_id"] = ses.first.first;
                    JsonData["Private_sessions"][i]["member_trainer_ids"][j]["trainer_id"] = ses.first.second;
                    JsonData["Private_sessions"][i]["member_trainer_ids"][j]["trainer_name"] = ses.second->get_trainer_name();
                    JsonData["Private_sessions"][i]["member_trainer_ids"][j]["member_name"] = ses.second->get_member_name();
                    JsonData["Private_sessions"][i]["member_trainer_ids"][j]["description"] = ses.second->get_description();
                    j++;
                }
                i++;
            }
        Ofile << JsonData;
        Ofile.close();
        sessions_updated = true;
    }
    else sessions_updated = false;
}

inline void Database::update_members(bool& members_updated)
{
    Json::Value JsonData;
    std::fstream Ofile(MEMBERS_FILE_PATH, std::ofstream::out | std::ofstream::trunc);
    if (Ofile.is_open()) {
        int i = 0;
        for (auto member : members_map) {
            JsonData["Members"][i]["id"] = member.first;
            JsonData["Members"][i]["surname"] = member.second->getsurname();
            JsonData["Members"][i]["name"] = member.second->getname();
            JsonData["Members"][i]["login"] = member.second->getlogin();
            JsonData["Members"][i]["password"] = member.second->get_hashed_password();
            JsonData["Members"][i]["Sport_option"] = member.second->getCategory();
            JsonData["Members"][i]["Level"] = member.second->get_level();
            i++;
        }
        Ofile << JsonData;
        Ofile.close();
        members_updated = true;
    }
    else members_updated = false;

}

inline void Database::update_trainers(bool& trainers_updated)
{
    Json::Value JsonData;
    std::fstream Ofile(TRAINERS_FILE_PATH, std::ofstream::out | std::ofstream::trunc);
    if (Ofile.is_open()) {
        int i = 0;
            for (auto trainer : trainers_map) {
                JsonData["Trainers"][i]["id"] = trainer.first;
                JsonData["Trainers"][i]["name"] = trainer.second->getname();
                JsonData["Trainers"][i]["surname"] = trainer.second->getsurname();
                JsonData["Trainers"][i]["login"] = trainer.second->getlogin();
                JsonData["Trainers"][i]["password"] = trainer.second->get_hashed_password();
                JsonData["Trainers"][i]["Category"] = trainer.second->getCategory();
                i++;
            }
        Ofile << JsonData;
        Ofile.close();
        trainers_updated = true;
    }
    else  trainers_updated = false;

}

inline void Database::update_admin(bool& admin_updated)
{

    Json::Value JsonData;
    std::fstream Ofile(ADMIN_FILE_PATH, std::ofstream::out | std::ofstream::trunc);
    if (Ofile.is_open()) {
        JsonData["login"] = admin->getlogin();
        JsonData["name"] = admin->getname();
        JsonData["surname"] = admin->getsurname();
        JsonData["password"] = admin->get_hashed_password();
        Ofile << JsonData;
        Ofile.close();
        admin_updated = true;
    }
    else admin_updated = false;
}

inline void Database::filter_sessions()
{
  boost::gregorian::date current_date(boost::gregorian::day_clock::local_day());
  std::erase_if(sessions, [&current_date](std::pair<Specific_slot, std::shared_ptr<Main_session>> session_pair) {return session_pair.first.sample_date < current_date; });
}


inline std::shared_ptr<session> Database::add_private_session(Specific_slot session_slot, int member_id, int trainer_id, std::string description)
{
    std::shared_ptr<session> ses;

    ses = std::make_shared<session>(members_map[member_id]->getFullName(), trainers_map[trainer_id]->getFullName(), description);
    if (sessions.contains(session_slot)) {
        sessions[session_slot]->add_a_session(member_id, trainer_id, ses);
    }
    else {
        sessions[session_slot] = std::make_shared<Main_session>();
        sessions[session_slot]->add_a_session(member_id, trainer_id, ses);
    }
    return ses;
}




inline void Database::assign_sessions()
{
    for (auto ses : sessions) {
        for (auto current_session : ses.second->get_current_sessions()) {
            members_map[current_session.first.first]->add_private_reservation(ses.first,current_session.second);
            trainers_map[current_session.first.second]->add_private_reservation(ses.first,current_session.second);
        }
    }

}

inline void Database::clear_sessions_by_mb_id(int mb_id)
{   

    for (auto [time, ses] : sessions) {
        for (auto pairs : ses->get_current_sessions())
            if (pairs.first.first == mb_id){
                ses->erase_a_session(pairs.first);
                trainers_map[pairs.first.second]->erase_reservation(time);
             }
   }
}

inline void Database::clear_sessions_by_tr_id(int tr_id)
{
    //to change to private ones
    for (auto [time, ses] : sessions) {
        for (auto pairs : ses->get_current_sessions())
            if (pairs.first.second == tr_id) {
                ses->erase_a_session(pairs.first);
                members_map[pairs.first.first]->erase_reservation(time);
            }
    }

}

inline void Database::delete_ids_from_session(Specific_slot& s, int member_id)
{
 
        for (auto pairs: sessions[s]->get_current_sessions()){
            if (pairs.first.first == member_id) {
                sessions[s]->erase_a_session(pairs.first);
                trainers_map[pairs.first.second]->erase_reservation(s);
            }
    }
}

inline bool Database::read_workout_programs()
{
    Json::Value JsonData;
    Json::Reader reader;
    std::ifstream Infile(PROGRAMS_FILE_PATH);
    reader.parse(Infile, JsonData);

    std::async(std::launch::async, [&]() {
     for (auto bd_program : JsonData["Body_building_programs"])
         body_building_programs.push_back(std::make_shared<Workout_program>(bd_program));
        });

    std::async(std::launch::async, [&]() {
        for (auto fit_program : JsonData["Fitnnes_programs"])
            fitnnes_programs.push_back(std::make_shared<Workout_program>(fit_program));
        });
    return true;

};

inline void Database::erase_member(int _id)
{
    members_map.erase(_id);
}

inline void Database::erase_trainer(int _id)
{
    trainers_map.erase(_id);
}

