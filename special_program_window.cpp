#include "special_program_window.h"
#include <QMessageBox>
#include <QStandardItemModel>
#include <QItemDelegate>
#include <QHBoxLayout>


special_program_window::special_program_window(QWidget* parent, std::shared_ptr<Member_win_controller> mb_controller)
	: QDialog(parent), member_controller(mb_controller)
{
	setupUi(this);
	setFixedSize(850,559);
	parentWidget()->hide();
	connect(this, SIGNAL(reservation_added()), parent, SLOT(receiveSignalChanged()));
	program_controller = std::make_shared<Special_program_controller>(member_controller->getCategory());
	for (auto& trainer_name : program_controller->get_trainers_names())
		trainer_combo->addItem(QString::fromStdString(trainer_name));
}



void special_program_window::on_search_button_clicked()
{
	program_sessions_table->clear();
	program_sessions_table->setRowCount(0);

	std::string current_trainer = trainer_combo->currentText().toStdString();
	if (program_controller->search_for_programs(member_controller->getCategory(), member_controller->get_level())) {
		program_found();
	}
	else {
		QMessageBox::Yes == QMessageBox::question(this, "Workout program",MyQtConstants::PROGRAM_NOT_FOUND , QMessageBox::Yes );
	}

}

void special_program_window::program_found()
{

	if (QMessageBox::Yes == QMessageBox::question(this, "Workout program", MyQtConstants::PROGRAM_FOUND, QMessageBox::Yes | QMessageBox::No)) {
		selection_window = std::make_shared<Program_selection_window>(this, program_controller);
		selection_window->show();
	}
}

void special_program_window::set_sessions_table(const std::vector<std::string>& sessions)
{
	for (auto const session : sessions) {
		int id = program_sessions_table->rowCount();
		program_sessions_table->insertRow(id);
		program_sessions_table->setItem(id, 0, new QTableWidgetItem(QString::fromStdString(session)));
		setup_combo_cells(id);
	}

}

void special_program_window::setup_combo_cells(int id) {

	QDateEdit* date_edit = new QDateEdit();
	date_edit->setCalendarPopup(true);
	date_edit->setObjectName("date_edit");
	date_edit->setMinimumDate(QDate::currentDate().addDays(1));
	date_edit->setMaximumDate(QDate::currentDate().addDays(356));
	//date_edit->setStyleSheet("#date_edit {border-radius: 10px;min-width: 50px ; min_height: 15px}");


	QComboBox* slot_combo = new QComboBox();
	slot_combo->setObjectName("slot_combo");
	slot_combo->setStyleSheet("#slot_combo {border-radius: 10px;min-width: 50px ; min_height: 15px;background-color: #FFFFFF}");
	// Move constants to another file "My_strings.h"


	//Hmm maybe concurency here also 
	for (int i = 1; i <= 5; i++)
		slot_combo->addItem(QString::fromStdString(MyMaps::slots_map[i]));

	program_sessions_table->setIndexWidget(program_sessions_table->model()->index(id, 1), date_edit);
	program_sessions_table->setIndexWidget(program_sessions_table->model()->index(id, 2), slot_combo);
	is_available[id] = false; //Uslees

}

bool special_program_window::check_availability(int id, int weeks,std::string trainer, Specific_slot sp_slot)
{
	if (!program_controller->get_trainer_controller(trainer)) {
		return false;
	}
	for (int i = 0; i < weeks - 1; i++) {
		sp_slot.sample_date += boost::gregorian::days(7); //move to the time class itself
		if (!program_controller->get_trainer_controller(trainer)->check_private_availability(sp_slot)) {
			program_sessions_table->setItem(id, 3, new QTableWidgetItem("Not available"));
			return false;
		}
	}
	program_sessions_table->setItem(id, 3, new QTableWidgetItem("Available"));
	return true;

}

//that's a long ass function xD
//should be changed 
void special_program_window::on_reserve_program_button_clicked() {

	int cases = 0;
	std::string current_trainer = trainer_combo->currentText().toStdString();
	int weeks_number = MyMaps::MONTHS_TO_WEEKS[period_combo->currentText().toStdString()];
	std::vector<int> chosen_days;
	std::vector<int> chosen_weeks;
	std::vector < std::pair<Specific_slot, std::string>> sessions_to_reserve; // date - slot
	sessions_to_reserve.clear();
	for (auto const& [id, status] : is_available) {
		std::vector <std::string> row_data = read_row_data(id);
		boost::gregorian::date chosen_date = boost::gregorian::from_string(row_data[0]);
		chosen_days.push_back(chosen_date.day_of_week());
		chosen_weeks.push_back(chosen_date.week_number());
		Specific_slot sp_slot(chosen_date, MyMaps::reverse_slots_map[row_data[1]]);
		if (check_availability(id, weeks_number,current_trainer, sp_slot)) {
			sessions_to_reserve.emplace_back(sp_slot, row_data[2]);//description is missing vector of vectors would be better and more flexible
		}
		else {
			cases++;
		}

	}
	if (!program_controller->diferent_week_checking(chosen_weeks))
	{
		status->clear();
		status->setText(MyQtConstants::different_weeks_found);

	}
	else if (!program_controller->days_duplicate_checking(chosen_days)) {
		status->setText(MyQtConstants::DAYS_DUPLICATE_FOUND);
		return;
	}

	else if (cases == 0){
		if (QMessageBox::Yes == QMessageBox::question(this, "Workout program", MyQtConstants::session_reservation_done, QMessageBox::Yes | QMessageBox::No)) {
			status->clear();
			reserve_sessions(current_trainer, weeks_number, sessions_to_reserve);
			this->hide();
			parentWidget()->show();
			emit reservation_added();
			}
		}

}

std::vector <std::string> special_program_window::read_row_data(int id)
{
	QDateEdit* day_cb = qobject_cast<QDateEdit*>(program_sessions_table->cellWidget(id, 1));
	QComboBox* time_cb = qobject_cast<QComboBox*>(program_sessions_table->cellWidget(id, 2));
	std::string chosen_date_str = day_cb->date().toString("yyyy-MM-dd").toStdString();
	std::string current_slot = time_cb->currentText().toStdString(); //slot chosen
	std::string workout = program_sessions_table->model()->data(program_sessions_table->model()->index(id, 0)).toString().toStdString();
	return { chosen_date_str, current_slot , workout};

}



void special_program_window::reserve_sessions(std::string trainer, int weeks_number,
	std::vector <std::pair<Specific_slot, std::string>> sessions_to_reserve)
{
	member_controller->clear_previous_reservation();
	for (auto& [ses, des] : sessions_to_reserve) {
		member_controller->reserve_private_session( program_controller->get_trainer_controller(trainer), des, ses);
		for (int i = 0; i < weeks_number - 1; i++) {
			ses.sample_date += boost::gregorian::days(7);
			member_controller->reserve_private_session( program_controller->get_trainer_controller(trainer), des, ses);
		}
	}
}



void special_program_window::receive_sessions(const std::vector<std::string>&s)
{
	placeholder->hide();
	set_sessions_table(s);
}


void special_program_window::closeEvent(QCloseEvent* bar)
{
	parentWidget()->show();
}