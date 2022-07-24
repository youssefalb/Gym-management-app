#include "Trainer_registration_window.h"
#include <QMessageBox>


Trainer_registration_window::Trainer_registration_window(QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);
	setFixedSize(733, 520);
	password_input_tr->setEchoMode(QLineEdit::Password);

	connect(this, SIGNAL(trainers_changed_signal()), parent, SLOT(trainers_changed()));
}

void Trainer_registration_window::on_register_button_tr_clicked() {
	registration_controller = std::make_shared<Trainer_registration_controller>();
	name_label_alert_tr->setText("");
	surname_label_alert_tr->setText("");
	login_label_alert_tr->setText("");
	password_label_alert_tr->setText("");
	password_status_tr->setText("");
	login_status_tr->setText("");
	int cases = 0;
	if (!checkForEmptyInputs()) {
		cases++;
	}
	if (!registration_controller->Check_password_security(password_input_tr->text().toStdString())) {
		password_status_tr->setText(MyQtConstants::PASSWORD_SECURITY_REQUIREMNETS);
		cases++;
	}
	if (!registration_controller->check_if_member_login_is_unique(login_input_tr->text().toStdString())) {
		login_status_tr->setText(MyQtConstants::LOGIN_UNIQUE_REQUIREMNET);
		cases++;
	}
	if (cases == 0) {
		registration_controller->register_trainer(name_input_tr->text().toStdString(),
			surname_input_tr->text().toStdString(),
			categoryCombo_tr->currentText().toStdString(),
			login_input_tr->text().toStdString(),
			password_input_tr->text().toStdString());
			emit trainers_changed_signal();
			hide();
			QMessageBox::Ok == QMessageBox::question(this, "Registration", MyQtConstants::REGISTRATION_DONE, QMessageBox::Ok);
	}

}

bool Trainer_registration_window::checkForEmptyInputs()
{
	int cases = 0;
	QIcon ButtonIcon();

	if (name_input_tr->text().isEmpty()) {
		name_label_alert_tr->setText(MyQtConstants::WARNING_IMAGE_SOURCE);
		cases++;
	}
	if (surname_input_tr->text().isEmpty()) {
		surname_label_alert_tr->setText(MyQtConstants::WARNING_IMAGE_SOURCE);
		cases++;
	}
	if (login_input_tr->text().isEmpty()) {
		login_label_alert_tr->setText(MyQtConstants::WARNING_IMAGE_SOURCE);
		cases++;
	}
	if (password_input_tr->text().isEmpty()) {
		password_label_alert_tr->setText(MyQtConstants::WARNING_IMAGE_SOURCE);
		cases++;
	}
	if (cases == 0)
		return true;
	else
		return false;

}
