#pragma once

#include <QDialog>
#include "ui_Password_change_window.h"
#include "Member_registration.h"


class Password_change_window : public QDialog, private Ui::Password_change_windowClass
{
	Q_OBJECT

	std::shared_ptr<User_controller> user_controller;
public:
	Password_change_window(QWidget *parent = nullptr, std::shared_ptr<User_controller> = nullptr);
private slots:
	void on_change_button_clicked();
};
