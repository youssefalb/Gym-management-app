#pragma once

#include <QWidget>
#include<QDialog>
#include "ui_Member_win.h"
#include "special_program_window.h"


class Member_win : public QDialog, private Ui::Member_win	
{
	Q_OBJECT

	std::shared_ptr<Member_win_controller> member_controller;
	std::shared_ptr<Res_session> rs;
	std::shared_ptr<special_program_window> program_window;
	std::shared_ptr<Password_change_window> password_change_window;
	std::pair<QWidget*, QPushButton*> get_delete_button_layout();
	std::map<QPushButton*, int> delete_button_map;

public: 
	Member_win( QWidget* parent = Q_NULLPTR, std::shared_ptr<Member_win_controller> mb_controller = NULL);
	void setInfo();
	void set_sessions();
private slots:

	void on_reserve_session_button_clicked();
	void on_change_password_button_clicked();
	void receiveSignalChanged();
	void on_logout_button_clicked();
	void on_special_program_button_clicked();
	void on_delete_session_button_clicked();
	void on_resign_button_clicked();
};
