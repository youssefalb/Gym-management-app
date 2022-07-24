#pragma once

#include <QDialog>
#include "ui_Trainer_registration_window.h"
#include "Csv_creator_controller.h"


class Trainer_registration_window : public QDialog, private Ui::Trainer_registration_windowClass
{
	Q_OBJECT

public:
	Trainer_registration_window(QWidget* parent = nullptr);

	std::shared_ptr<Trainer_registration_controller> registration_controller;
	bool checkForEmptyInputs();
private slots:
	void on_register_button_tr_clicked();

signals:
	void trainers_changed_signal();


};
