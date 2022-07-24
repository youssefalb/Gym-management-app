#include "GymAppQt.h"
#include "stdafx.h"
#include<QDebug>
#include<QMessageBox>


GymAppQt::GymAppQt(QWidget *parent) : QMainWindow(parent)
{
    setupUi(this);
    setFixedSize(805, 542);
    Login_button_ad->setAutoDefault(false); 
    password_input_ad->setEchoMode(QLineEdit::Password);
    password_input_mb->setEchoMode(QLineEdit::Password);
    password_input_tr->setEchoMode(QLineEdit::Password);
   // connect(update_button, SIGNAL(clicked()), this, SIGNAL(on_update_button_button_clicked()));
    main_controller = std::make_shared<Main_controller>();

}

void GymAppQt::on_Login_button_ad_clicked()
{
    QString username = login_input_ad->text();
    QString password = password_input_ad->text();
 
    std::shared_ptr<Admin_controller> admin_controller = main_controller->check_admin_login(username.toStdString(), password.toStdString());
    if (admin_controller != NULL) {
        adminwin =std::make_shared<Admin_win>(this, admin_controller);
        adminwin->show();
        password_input_ad->clear();
        login_input_ad->clear();
    }
    else {
        QMessageBox::warning(this, "login", MyQtConstants::UNSUCCESFUL_LOGIN);
    }
}

void GymAppQt::on_Login_button_tr_clicked()
{
    QString username = login_input_tr->text();
    QString password = password_input_tr->text();
    std::shared_ptr<Trainer_win_controller> tr = main_controller->check_trainer_login(username.toStdString(), password.toStdString());

    if (tr!= NULL) {
        tr_w = std::make_shared<Trainer_win>(this,tr);
        tr_w->show();
        login_input_tr->clear();
        password_input_tr->clear();
    }
    else {
        QMessageBox::warning(this, "login", MyQtConstants::UNSUCCESFUL_LOGIN);
    }
}

void GymAppQt::on_Login_button_mb_clicked()
{

    QString username = login_input_mb->text();
    QString password = password_input_mb->text();
    std::shared_ptr<Member_win_controller> mb = main_controller->check_member_login(username.toStdString(), password.toStdString());


    if (mb != NULL) {
         mb_w = std::make_shared<Member_win>(this,mb);
         mb_w->show();
         login_input_mb->clear();
         password_input_mb->clear();
    }
    else {
        QMessageBox::warning(this, "login", MyQtConstants::UNSUCCESFUL_LOGIN);
    }
}

void GymAppQt::on_to_register_button_clicked()
{
    Member_registration_win.show();
}
