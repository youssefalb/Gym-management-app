
#include <QDialog>
#include "ui_Program_selection_window.h"
#include"Res_session.h"


class Program_selection_window : public QDialog, private Ui::Program_selection_windowClass
{
	Q_OBJECT

public:

	Program_selection_window(QWidget* parent = Q_NULLPTR, std::shared_ptr<Special_program_controller> _sp_program_controller = NULL);
	void add_program_boxs();
	void closeEvent(QCloseEvent* bar);

private:
	std::shared_ptr<Special_program_controller> sp_program_controller;
	std::map < QPushButton*, std::vector <std::string> > sessions_button_map;
private slots:
	void on_sessions_button_clicked();
signals:
	void sendSessions(const std::vector<std::string>& s);
};
