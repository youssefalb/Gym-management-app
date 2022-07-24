#include "Member_registration.h"
#include <QMessageBox>

Member_registration_window::Member_registration_window(QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);
	setFixedSize(714,517);
	connect(this, SIGNAL(members_changed_signal()), parent, SLOT(members_changed()));
	password_input->setEchoMode(QLineEdit::Password);

}

void Member_registration_window::on_register_button_clicked() {
	registration_controller = std::make_shared<Member_registration_controller>();
	name_label_alert->setText("");
	surname_label_alert->setText("");
	login_label_alert->setText("");
	password_label_alert->setText("");
	password_status->setText("");
	login_status->setText("");
	int cases = 0;
	if (!checkForEmptyInputs()) {
		cases++;
	}
	 if (!registration_controller->Check_password_security(password_input->text().toStdString())) {
		password_status->setText(MyQtConstants::PASSWORD_SECURITY_REQUIREMNETS);
		cases ++;
	}
	 if (!registration_controller->check_if_member_login_is_unique(login_input->text().toStdString())) {
		login_status->setText(MyQtConstants::LOGIN_UNIQUE_REQUIREMNET);
		cases++;
	}
	if (cases == 0) {
		registration_controller->register_member(name_input->text().toStdString(),
		surname_input->text().toStdString(), 
		categoryCombo->currentText().toStdString(), 
		login_input->text().toStdString(), 
		password_input->text().toStdString(),
		level_combo->currentText().toStdString());
		emit members_changed_signal();
		hide();
		if (Database_manager::getInstance()->update_data()) {
			QMessageBox::Ok == QMessageBox::question(this, "Registration", MyQtConstants::REGISTRATION_DONE, QMessageBox::Ok);
		}
		else {
			QMessageBox messageBox;
			messageBox.critical(0, "Error", MyQtConstants::UPDATE_DATA_FAILED);
			messageBox.setFixedSize(500, 200);
		}

	}
		
	
}

bool Member_registration_window::checkForEmptyInputs()
{
	int cases = 0;
	QIcon ButtonIcon();

	if (name_input->text().isEmpty()){
		name_label_alert->setText(MyQtConstants::WARNING_IMAGE_SOURCE);
		cases++;
	}
	if (surname_input->text().isEmpty()) {
		surname_label_alert->setText(MyQtConstants::WARNING_IMAGE_SOURCE);
		cases++;
	}
	if (login_input->text().isEmpty()) {
		login_label_alert->setText(MyQtConstants::WARNING_IMAGE_SOURCE);
		cases++;
	}
	if (password_input->text().isEmpty()) {
		password_label_alert->setText(MyQtConstants::WARNING_IMAGE_SOURCE);
		cases++;
	}
	if (cases == 0)
		return true;
	else
		return false;

}
