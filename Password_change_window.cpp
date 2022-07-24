#include "Password_change_window.h"
#include<QMessageBox>

Password_change_window::Password_change_window(QWidget* parent, std::shared_ptr<User_controller> _user_controller)
	: QDialog(parent), user_controller(_user_controller)
{
	setupUi(this);
	parent->setEnabled(1);
	setFixedSize(275,292);
	current_password_input->setEchoMode(QLineEdit::Password);
	new_password_input->setEchoMode(QLineEdit::Password);

}

void Password_change_window::on_change_button_clicked()
{
	password_status->clear();
	if (!user_controller->check_current_password(current_password_input->text().toStdString())) {
		QMessageBox::information(this, "Just for testing", "Incorrect current password");
		return;
	}
	else if(!user_controller->Check_password_security(new_password_input->text().toStdString())) {
		password_status->setText(MyQtConstants::PASSWORD_SECURITY_REQUIREMNETS);
			return;
	}

	user_controller->change_password(new_password_input->text().toStdString());
	QMessageBox::information(this, "Password change", "Done");


}
