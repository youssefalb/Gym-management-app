#pragma once

#include <QWidget>
#include "ui_Program_sessions_win.h"

class Program_sessions_win : public QWidget
{
	Q_OBJECT

public:
	Program_sessions_win(QWidget *parent = Q_NULLPTR);
	~Program_sessions_win();

private:
	Ui::Program_sessions_win ui;
};
