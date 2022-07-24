#pragma once

#include <QDialog>

#include "ui_Member_registration.h"
#include "Trainer_registration_window.h"
class Member_registration_window : public QDialog , private Ui::Member_registration
{
	Q_OBJECT

public:
	std::shared_ptr<Member_registration_controller> registration_controller;
	Member_registration_window(QWidget *parent = Q_NULLPTR);
	bool checkForEmptyInputs();

private slots:
	void on_register_button_clicked();
signals:
	void members_changed_signal();

};
