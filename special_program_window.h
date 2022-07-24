#pragma once

#include <QWidget>
#include <QDialog>
#include "ui_special_program_window.h"
#include "Program_selection_window.h"


class special_program_window : public QDialog, private Ui::special_program_window
{
	Q_OBJECT
private:
	std::shared_ptr<Special_program_controller> program_controller;
	std::shared_ptr<Member_win_controller> member_controller;
	std::shared_ptr<Program_selection_window> selection_window;
public:
	std::map<QPushButton*, int> buttons_map;
	void closeEvent(QCloseEvent* bar);
	std::map<int, bool> is_available;
	special_program_window(QWidget *parent = Q_NULLPTR, std::shared_ptr<Member_win_controller> mb_controller =NULL);
	void program_found();
	void set_sessions_table(const std::vector<std::string>& sessions);
	void setup_combo_cells(int id);
	bool check_availability(int id, int weeks,std::string trainer, Specific_slot sp_slot);
	std::vector <std::string>   read_row_data(int id);
	void reserve_sessions(std::string trainer, int weeks_number,
	std::vector <std::pair<Specific_slot, std::string>> sessions_to_reserve);

private slots:
	void on_search_button_clicked();
	void on_reserve_program_button_clicked();
public slots:
	void receive_sessions(const std::vector<std::string>& s);
signals:
	void reservation_added();
};
