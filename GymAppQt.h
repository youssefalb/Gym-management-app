#pragma once

#include <QtWidgets/QMainWindow>
#include <iostream>
#include "ui_GymAppQt.h"
#include "Admin_win.h"


class GymAppQt : public QMainWindow, private Ui::GymAppQtClass
{
    Q_OBJECT
      
public:
    GymAppQt(QWidget *parent = Q_NULLPTR );

private slots:
    void on_Login_button_ad_clicked();
    void on_Login_button_tr_clicked();
    void on_Login_button_mb_clicked();
    void on_to_register_button_clicked();
private:
    std::shared_ptr<Main_controller> main_controller;
    std::shared_ptr<Admin_win> adminwin;
    std::shared_ptr <Member_win> mb_w;
    std::shared_ptr <Trainer_win> tr_w;
    Member_registration_window Member_registration_win;
};
