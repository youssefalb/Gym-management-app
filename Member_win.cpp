#include "Member_win.h"
#include<QMessageBox>


Member_win::Member_win(QWidget* parent, std::shared_ptr<Member_win_controller> mb_controller)
	: QDialog(parent), member_controller(mb_controller)
{
	setupUi(this);
	setFixedSize(967, 584);
	parentWidget()->hide();
	setWindowFlags(Qt::Window | Qt::WindowTitleHint);
	setInfo();
	set_sessions();
}


void Member_win::setInfo()
{
	name_label->setText(QString::fromStdString(member_controller->getname()));
	surname_label->setText(QString::fromStdString(member_controller->getsurname()));
	category_label->setText(QString::fromStdString(member_controller->getCategory()));
	level_label->setText(QString::fromStdString(member_controller->get_level()));


}

void Member_win::set_sessions()
{
	tableWidget->clear();
	int i = 0;
	for (auto session : member_controller->get_private_schedule()) {
		tableWidget->insertRow(i);
		tableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(session.second[0])));
		tableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(session.second[1])));
		tableWidget->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(session.second[2])));
		tableWidget->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(session.second[3])));
		std::pair<QWidget*, QPushButton*> delete_session_button = get_delete_button_layout();
		tableWidget->setCellWidget(i, 4, delete_session_button.first);
		connect(delete_session_button.second, SIGNAL(clicked()), this, SLOT(on_delete_session_button_clicked()));
		delete_button_map[delete_session_button.second] = session.first;
		i++;
	}
}

std::pair<QWidget*, QPushButton*> Member_win::get_delete_button_layout()
{
	QPushButton* bt_delete = new QPushButton();
	bt_delete->setText("Delete");
	bt_delete->setObjectName("bt_delete"); // Layout id
	bt_delete->setFixedWidth(120);
	bt_delete->setStyleSheet(MyQtConstants::BUTTON_DELETE_STYLE);
	QWidget* pWidget_delete = new QWidget();
	QHBoxLayout* pLayout_delete = new QHBoxLayout(pWidget_delete);
	pLayout_delete->addWidget(bt_delete);
	pLayout_delete->setAlignment(Qt::AlignCenter);
	pLayout_delete->setContentsMargins(0, 0, 0, 0);
	pWidget_delete->setLayout(pLayout_delete);
	return { pWidget_delete , bt_delete };
}



void Member_win::on_logout_button_clicked()
{
	if (!Database_manager::getInstance()->update_data()) {
		QMessageBox messageBox;
		messageBox.critical(0, "Error", MyQtConstants::UPDATE_DATA_FAILED);
		messageBox.setFixedSize(500, 200);
	}
	this->close();
	parentWidget()->show();
}

void Member_win::on_special_program_button_clicked()
{
	program_window = std::make_shared<special_program_window>(this, member_controller);
	program_window->show();
}

void Member_win::on_delete_session_button_clicked()
{
	QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
	if (QMessageBox::Yes == QMessageBox::question(this, "", "confirmation", QMessageBox::Yes | QMessageBox::No)) {
		if (member_controller->delete_session_by_slot_id(delete_button_map[buttonSender])) {
			set_sessions();
		}
		else {
			QMessageBox::Yes == QMessageBox::question(this, "", MyQtConstants::PORHIBITED_SESSION_DELETION, QMessageBox::Yes | QMessageBox::No);
		}
	}

}

void Member_win::on_reserve_session_button_clicked()
{
	rs = std::make_shared<Res_session>(this, member_controller, std::make_shared<Base_reservation_controller>(member_controller->getCategory()));
	rs->show();
}

void Member_win::on_change_password_button_clicked()
{
	password_change_window = std::make_shared<Password_change_window>(this, member_controller);
	password_change_window->show();

}

void Member_win::receiveSignalChanged()
{
	set_sessions();
}

void Member_win::on_resign_button_clicked()
{
	Database_manager::getInstance()->update_data();
	member_controller->delete_user();
	parentWidget()->show();
	close();
}
