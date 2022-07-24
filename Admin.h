
#include "Trainer.h"



class Admin: public Loggable {


public:
	Admin(std::string login, std::string name,
		std::string surname,size_t _hashed_pass):
	Loggable(name , surname ,login, _hashed_pass){}

};