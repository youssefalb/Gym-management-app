#include "Trainer_win.h"

Trainer_win::Trainer_win(QWidget *parent, std::shared_ptr<Trainer_win_controller> tr_controller)
	: QDialog(parent), trainer_controller(tr_controller)
{
	setFixedSize(931, 580);
	setWindowFlags(Qt::Window | Qt::WindowTitleHint);

	parentWidget()->hide();
	setupUi(this);
	setInfo();
}

void Trainer_win::setInfo()
{
	name_label->setText(QString::fromStdString(trainer_controller->getname()));
	surname_label->setText(QString::fromStdString(trainer_controller->getsurname()));
	category_label->setText(QString::fromStdString(trainer_controller->getCategory()));

	for (auto& ses : trainer_controller->get_private_schedule()) {
			tableWidget->insertRow(tableWidget->rowCount());
			tableWidget->setItem(tableWidget->rowCount() - 1, 0, new QTableWidgetItem(QString::fromStdString(ses[0])));
			tableWidget->setItem(tableWidget->rowCount() - 1, 1, new QTableWidgetItem(QString::fromStdString(ses[1])));
			tableWidget->setItem(tableWidget->rowCount() - 1, 2, new QTableWidgetItem(QString::fromStdString(ses[2])));
			tableWidget->setItem(tableWidget->rowCount() - 1, 3, new QTableWidgetItem(QString::fromStdString(ses[3])));
	}

}


void Trainer_win::on_logout_button_clicked()
{
	this->close();
	parentWidget()->show();
}

void Trainer_win::on_resign_button_clicked()
{
	trainer_controller->delete_user();
	this->close();
	parentWidget()->show();
	Database_manager::getInstance()->update_data();
}

void Trainer_win::on_change_password_button_clicked()
{
	password_change_window = std::make_shared<Password_change_window>(this, trainer_controller);
	password_change_window->show();
}
