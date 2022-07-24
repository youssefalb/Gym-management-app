#pragma once

#include <QWidget>
#include <QDialog>
#include "ui_Update_member_win.h"
#include"Member_win.h"


class Update_member_win : public QDialog, private Ui::Update_member_win
{
	Q_OBJECT
private:

	std::shared_ptr<Member_win_controller> member_controller; 
public:
	Update_member_win(QWidget* parent = Q_NULLPTR, std::shared_ptr<Member_win_controller > _member_controller = NULL);

public slots:
	void on_reset_password_button_clicked();
	void on_update_button_clicked();
signals:
	void member_updated_signal();
};
