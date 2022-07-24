#include "Update_member_win.h"
#include <QMessagebox>

Update_member_win::Update_member_win(QWidget *parent, std::shared_ptr<Member_win_controller > _member_controller)
	: QDialog(parent) , member_controller(_member_controller)
{
	setupUi(this);
	setFixedSize(444,352);
	name_input->setText(QString::fromStdString(member_controller->getname()));
	surname_input->setText(QString::fromStdString(member_controller->getsurname()));
	level_combo->setCurrentText(QString::fromStdString(member_controller->get_level()));
	connect(this, SIGNAL(member_updated_signal()), parent, SLOT(members_changed()));

}

void Update_member_win::on_reset_password_button_clicked()
{
	if (QMessageBox::Yes == QMessageBox::question(this,QString::fromStdString( member_controller->getFullName()),MyQtConstants::PASSWORD_RESET_CONFIRMATION, QMessageBox::Yes | QMessageBox::No)) {
		member_controller->reset_password();
	}
}

void Update_member_win::on_update_button_clicked()
{
	std::string name = name_input->text().toStdString();
	std::string surname = surname_input->text().toStdString();
	std::string level = level_combo->currentText().toStdString();

	member_controller->update_member_data(name, surname , level);
	emit member_updated_signal();
}

