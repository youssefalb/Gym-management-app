#pragma once

#include <QWidget>
#include <QDialog>
#include <QCloseEvent>
#include "ui_Res_session.h"
#include "Trainer_win.h"
#include <QtGui/qvalidator.h>


class Res_session : public QDialog, private Ui::Res_session
{
	Q_OBJECT
	void closeEvent(QCloseEvent* bar);
	std::shared_ptr<Member_win_controller> member_controller;
	std::shared_ptr<Base_reservation_controller> reservation_controller;
public:
	Res_session(QWidget *parent = Q_NULLPTR, std::shared_ptr<Member_win_controller> mb_controller =NULL, std::shared_ptr<Base_reservation_controller> res_controller = NULL);
	void set_trainers();
	void set_possible_sessions();
private slots:
	void on_confirm_button_clicked();
signals:
	void sendSignalChanged();

};
