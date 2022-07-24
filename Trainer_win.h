#pragma once

#include <QWidget>
#include <QDialog>
#include "Password_change_window.h"
#include "ui_Trainer_win.h"

class Trainer_win : public QDialog, private Ui::Trainer_win
{

	Q_OBJECT
private:
		std::shared_ptr<Trainer_win_controller> trainer_controller;
		std::shared_ptr<Password_change_window> password_change_window;
		
		void setInfo();
public:
	Trainer_win(QWidget *parent = Q_NULLPTR, std::shared_ptr<Trainer_win_controller> tr_controller = NULL);

private slots: 
	void on_logout_button_clicked();
	void on_resign_button_clicked();
	void on_change_password_button_clicked();
};
