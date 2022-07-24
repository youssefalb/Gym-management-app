#include "Admin_win.h"
#include <QMessageBox>
#include<QHBoxLayout>
#include<QtConcurrent/QtConcurrent>
#include<QFuture>
#include <QDebug>
#include<QThread>


Admin_win::Admin_win(QWidget *parent, std::shared_ptr<Admin_controller> _admin_controller ) : QDialog(parent), admin_controller(_admin_controller)
{
	setupUi(this);
	setFixedSize(1011, 491);
	name_label->setText(QString::fromStdString(admin_controller->getname()));
	surname_label->setText(QString::fromStdString(admin_controller->getsurname()));
	setWindowFlags(Qt::Window | Qt::WindowTitleHint);
	parentWidget()->hide();	
	qInfo() << "scan";
	csv_creator_controller = std::make_shared<Csv_creator_controller>();
	std::thread th1(&Admin_win::set_add_icon, this);
	set_sessions();
	set_members();
	set_trainers();
	th1.join();
}


void Admin_win::set_members()
{
	members_table->clear();
	members_table->setRowCount(0);
	members_delete_update_button.clear();
	for (auto& [id , member_data] : admin_controller->get_members_data()) {
		members_table->insertRow(members_table->rowCount());
		members_table->setItem(members_table->rowCount()-1, 0, new QTableWidgetItem(QString::fromStdString(member_data[0])));
		members_table->setItem(members_table->rowCount()-1, 1, new QTableWidgetItem(QString::fromStdString(member_data[1])));
		members_table->setItem(members_table->rowCount()-1, 2, new QTableWidgetItem(QString::fromStdString(member_data[2])));
		members_table->setItem(members_table->rowCount()-1, 3, new QTableWidgetItem(QString::fromStdString(member_data[3])));

		std::pair<QWidget*, QPushButton*> update_button_layout = get_update_button_layout();
		std::pair<QWidget*, QPushButton*> delete_button_layout = get_delete_button_layout();
		members_table->setCellWidget(members_table->rowCount() - 1, 4, delete_button_layout.first);
		members_table->setCellWidget(members_table->rowCount() - 1, 5, update_button_layout.first);

		members_delete_update_button[delete_button_layout.second] = id;
		members_delete_update_button[update_button_layout.second] = id;
		connect(delete_button_layout.second, SIGNAL(clicked()), this, SLOT(on_delete_member_button_clicked()));
		connect(update_button_layout.second, SIGNAL(clicked()), this, SLOT(on_update_member_button_clicked()));
	}
}

void Admin_win::set_add_icon()
{
	QPixmap pixmap("Add_icon(2).png");
	QIcon ButtonIcon(pixmap);
	add_button_mb->setIcon(ButtonIcon);
	add_button_mb->setIconSize(pixmap.rect().size());
	add_button_tr->setIcon(ButtonIcon);
	add_button_tr->setIconSize(pixmap.rect().size());

}
 
void Admin_win::set_trainers()
{
	trainers_table->clear();
	trainers_table->setRowCount(0);
	trainers_delete_update_button.clear();
	for (auto& [id, trainer_data] :admin_controller->get_trainers_data()) {
		trainers_table->insertRow(trainers_table->rowCount());
		trainers_table->setItem(trainers_table->rowCount() - 1, 0, new QTableWidgetItem(QString::fromStdString(trainer_data[0])));
		trainers_table->setItem(trainers_table->rowCount() - 1, 1, new QTableWidgetItem(QString::fromStdString(trainer_data[1])));
		trainers_table->setItem(trainers_table->rowCount() - 1, 2, new QTableWidgetItem(QString::fromStdString(trainer_data[2])));
		std::pair<QWidget*, QPushButton*> delete_button_layout = get_delete_button_layout();
		trainers_table->setCellWidget(trainers_table->rowCount() - 1, 3, delete_button_layout.first);
		trainers_delete_update_button[delete_button_layout.second] = id;
		connect(delete_button_layout.second, SIGNAL(clicked()), this, SLOT(on_delete_trainer_button_clicked()));
	}

}

void Admin_win::set_sessions()
{
	sessions_table->clear();
	sessions_table->setRowCount(0);
	for (auto session : admin_controller->get_sessions()) {
			sessions_table->insertRow(sessions_table->rowCount());
			sessions_table->setItem(sessions_table->rowCount() - 1, 0, new QTableWidgetItem(QString::fromStdString(session[0])));
			sessions_table->setItem(sessions_table->rowCount() - 1, 1, new QTableWidgetItem(QString::fromStdString(session[1])));
			sessions_table->setItem(sessions_table->rowCount() - 1, 2, new QTableWidgetItem(QString::fromStdString(session[2])));
			sessions_table->setItem(sessions_table->rowCount() - 1, 3, new QTableWidgetItem(QString::fromStdString(session[3])));
			sessions_table->setItem(sessions_table->rowCount() - 1, 4, new QTableWidgetItem(QString::fromStdString(session[4])));
		}
	
}



void Admin_win::on_delete_member_button_clicked() 
{
	if (QMessageBox::Yes == QMessageBox::question(this, "Close Confirmation", MyQtConstants::USER_DELETION_CONFIRMATION, QMessageBox::Yes | QMessageBox::No)) {
		QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
		admin_controller->delete_member_from_gym(members_delete_update_button[buttonSender]);
		set_members();
		set_sessions();
	}
}

void Admin_win::on_delete_trainer_button_clicked()
{
	if (QMessageBox::Yes == QMessageBox::question(this, "Close Confirmation",MyQtConstants::USER_DELETION_CONFIRMATION , QMessageBox::Yes | QMessageBox::No)) {
		QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
		admin_controller->delete_trainer_from_gym(trainers_delete_update_button[buttonSender]);
		set_trainers();
		set_sessions();
	}
}


void Admin_win::on_update_member_button_clicked()
{
	QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
	  //get the member_controller and pass it 
	if (QMessageBox::Yes == QMessageBox::question(this,"update window",MyQtConstants::USER_UPDATE_CONFIRMATION, QMessageBox::Yes | QMessageBox::No)) {
		update_member_window = std::make_shared<Update_member_win>(this, admin_controller->get_member_controller(members_delete_update_button[buttonSender]));
		update_member_window->show();
	}
}


void Admin_win::on_add_button_mb_clicked() {
	member_registration_win = std::make_shared<Member_registration_window>(this);
	member_registration_win->show();
}
void Admin_win::on_add_button_tr_clicked() {
	trainer_registration_win = std::make_shared<Trainer_registration_window>(this);
	trainer_registration_win->show();
}


void Admin_win::on_logout_button_clicked() {
	if (!Database_manager::getInstance()->update_data()) {
		QMessageBox messageBox;
		messageBox.critical(0, "Error", MyQtConstants::UPDATE_DATA_FAILED);
		messageBox.setFixedSize(500, 200);
	}
	this->close();
	parentWidget()->show();
}

std::pair<QWidget*, QPushButton*> Admin_win::get_delete_button_layout()
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

std::pair<QWidget*, QPushButton*> Admin_win::get_update_button_layout()
{
	QPushButton* btn_update = new QPushButton();
	btn_update->setObjectName("btn_update"); // Layout id
	btn_update->setFixedWidth(120);
	btn_update->setStyleSheet(MyQtConstants::BUTTON_UPDATE_STYLE);
	btn_update->setText("Update");
	QWidget* pWidget_update = new QWidget();
	QHBoxLayout* pLayout_update = new QHBoxLayout(pWidget_update);
	pLayout_update->addWidget(btn_update);
	pLayout_update->setAlignment(Qt::AlignCenter);
	pLayout_update->setContentsMargins(0, 0, 0, 0);
	pWidget_update->setLayout(pLayout_update);
	return { pWidget_update , btn_update };
}


void Admin_win::on_sessions_csv_button_clicked() {
	auto sessions_to_write = admin_controller->get_sessions();
	if (csv_creator_controller->create_sessions_file(sessions_to_write))
		QMessageBox::Yes == QMessageBox::question(this, "", "File created", QMessageBox::Yes | QMessageBox::No);
	else
		QMessageBox::Yes == QMessageBox::question(this, "", "Something went Wrong", QMessageBox::Yes | QMessageBox::No);
}

void Admin_win::on_members_csv_button_clicked() {
	std::vector<std::vector<std::string>> members_to_write;
	for (auto member_pair: admin_controller->get_members_data()) {
		members_to_write.push_back(member_pair.second);
	}
	if (csv_creator_controller->create_members_file(members_to_write))
		QMessageBox::Yes == QMessageBox::question(this, "", "File created", QMessageBox::Yes | QMessageBox::No);
	else
		QMessageBox::Yes == QMessageBox::question(this, "", "Something went Wrong", QMessageBox::Yes | QMessageBox::No);
}

void Admin_win::on_trainers_csv_button_clicked() {
	std::vector < std::vector < std::string >> trainers_to_write;
	for (auto trainer_pair : admin_controller->get_trainers_data()) {
		trainers_to_write.push_back(trainer_pair.second);
	}
	if (csv_creator_controller->create_trainers_file(trainers_to_write))
		QMessageBox::Yes == QMessageBox::question(this, "", "File created", QMessageBox::Yes | QMessageBox::No);
	else
		QMessageBox::Yes == QMessageBox::question(this, "", "Something went Wrong", QMessageBox::Yes | QMessageBox::No);
}


void Admin_win::members_changed() {
	set_members();
	set_sessions();
}
void Admin_win::trainers_changed() {
	set_trainers();
	set_sessions();
}

