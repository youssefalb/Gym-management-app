#include "Program_selection_window.h"
#include<QPushButton>
#include<QMessageBox>

Program_selection_window::Program_selection_window(QWidget* parent, std::shared_ptr<Special_program_controller> _sp_program_controller)
	: QDialog(parent), sp_program_controller(_sp_program_controller)
{

	setupUi(this);
	parentWidget()->hide();
	setFixedSize(443, 530);
	connect(this, SIGNAL(sendSessions(std::vector<std::string>)), parent, SLOT(receive_sessions(std::vector<std::string>)));
	add_program_boxs();
}


void Program_selection_window::add_program_boxs()
{
		QVBoxLayout* layout = qobject_cast<QVBoxLayout*> (my_frame->layout());
		for (auto program_sessions : sp_program_controller->get_sessions()) {
			QString sessionsText;
			for (auto session : program_sessions) {
				sessionsText.append(QString::fromStdString(session) + "\n");
			}
			QPushButton* sessions_box = new QPushButton(sessionsText, my_frame);
			layout->insertWidget(0, sessions_box);
			sessions_button_map[sessions_box] = program_sessions;
			connect(sessions_box, SIGNAL(clicked()), this, SLOT(on_sessions_button_clicked()));
		}

}

void Program_selection_window::closeEvent(QCloseEvent* bar)
{
	parentWidget()->show();
}

void Program_selection_window::on_sessions_button_clicked()
{
	QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
	emit sendSessions(sessions_button_map[buttonSender]);
	this->hide();
	parentWidget()->show();

}


