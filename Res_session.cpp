#include "Res_session.h"
#include<QMessageBox>
#include"Member_win.h"



Res_session::Res_session(QWidget *parent, std::shared_ptr<Member_win_controller> mb_controller, std::shared_ptr<Base_reservation_controller> res_controller)
	: QDialog(parent), member_controller(mb_controller), reservation_controller(res_controller)
{
	setupUi(this);
	parentWidget()->hide();
	setFixedSize(611,451);
	std::jthread th1(&Res_session::set_trainers, this);
	std::jthread th(&Res_session::set_possible_sessions, this);
	date_chosen->setMinimumDate(QDate::currentDate().addDays(1));
	date_chosen->setMaximumDate(QDate::currentDate().addDays(356));
	connect(confirm_button, SIGNAL(clicked()), this, SIGNAL(on_confirm_button_clicked()));

	connect(this, SIGNAL(sendSignalChanged()), parent, SLOT(receiveSignalChanged()));


	parentWidget()->hide();
}

void Res_session::set_trainers()
{
	/*OPSSSSS*/
	for (auto& trainer_name : reservation_controller->get_trainers_names())
		trainer_combo->addItem(QString::fromStdString(trainer_name));
}

void Res_session::set_possible_sessions()
{
	if (member_controller->getCategory() == MyConstants::BD_CATEGORY) {
		for (auto workout : MyQtConstants::POSSIBLE_BD_SESSIONS) {
			workout_combo->addItem(workout);
		}
	}
	else{
		for (auto workout : MyQtConstants::POSSIBLE_FIT_SESSIONS) {
			workout_combo->addItem(workout);
		}
	}
}

void Res_session::on_confirm_button_clicked()
{
	std::string current_trainer = trainer_combo->currentText().toStdString();
	std::string chosen_date_str = date_chosen->date().toString("yyyy-MM-dd").toStdString();
	std::string workout = workout_combo->currentText().toStdString();

	int day = date_chosen->date().dayOfWeek();
	std::string current_slot = slot_combo->currentText().toStdString();

	boost::gregorian::date chosen_date = boost::gregorian::from_string(chosen_date_str);

	Specific_slot sp_slot(chosen_date, MyMaps::reverse_slots_map[current_slot]);

	if (member_controller->check_private_availability(sp_slot)&& reservation_controller->get_trainer_controller(current_trainer)->check_private_availability(sp_slot)) {
		if (QMessageBox::information(this, "reservation", MyQtConstants::session_reservation_done)) {
			member_controller->reserve_private_session(reservation_controller->get_trainer_controller(current_trainer), workout,sp_slot);
			emit sendSignalChanged();
			this->hide();
			parentWidget()->show();
		}
	}
	else
	{
		QMessageBox::warning(this, "reservation", MyQtConstants::session_booked);
	}
}

void Res_session::closeEvent(QCloseEvent *bar)
{
	parentWidget()->update();
	parentWidget()->show();
}
