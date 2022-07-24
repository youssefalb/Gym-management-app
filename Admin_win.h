#pragma once

#include <QWidget>
#include <QDialog>
#include "ui_Admin_win.h"
#include "Update_member_win.h"

class Admin_win : public QDialog , private Ui::Admin_win
{
	Q_OBJECT

private:
	std::shared_ptr<Update_member_win> update_member_window;
	std::shared_ptr<Admin_controller> admin_controller;
	std::shared_ptr<Csv_creator_controller> csv_creator_controller;
	std::shared_ptr<Member_registration_window> member_registration_win;
	std::shared_ptr<Trainer_registration_window> trainer_registration_win;
	std::map <QPushButton*, int > members_delete_update_button;
	std::map <QPushButton*, int > trainers_delete_update_button;
	std::pair<QWidget*, QPushButton*> get_delete_button_layout();
	std::pair<QWidget*, QPushButton*> get_update_button_layout();

public:

	Admin_win(QWidget* parent = Q_NULLPTR, std::shared_ptr<Admin_controller> _admin_controller= NULL);
	void set_members();
	void set_add_icon();

	void set_trainers();
	void set_sessions();




private slots:
	void on_add_button_mb_clicked();
	void on_add_button_tr_clicked();
	void on_logout_button_clicked();
	void on_delete_member_button_clicked();
	void on_delete_trainer_button_clicked();
	void on_update_member_button_clicked();
	void on_sessions_csv_button_clicked();
	void on_members_csv_button_clicked();
	void on_trainers_csv_button_clicked();
public slots:
	void trainers_changed();
	void members_changed();

};
