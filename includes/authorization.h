#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QDialog>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QNetworkAccessManager>
#include "contentwindow.h"

class Authorization : public QDialog {

    Q_OBJECT

public:
    explicit Authorization(QWidget *parent = nullptr);
    ~Authorization();
private slots:
    void sendLoginForm();
    void sendRegistrationForm();
private:
    QStackedWidget *stackedWidget;
    QWidget *loginWidget;
    QWidget *registrationWidget;

    QVBoxLayout *mainLayout;

    //Login page data
    QVBoxLayout *logoLogLayout;
    QLabel *logoLogLabel;

    QVBoxLayout *loginLayout;
    QLabel *loginLabel;
    QLineEdit *loginLine;

    QVBoxLayout *passwordLayout;
    QLabel *passwordLabel;
    QLineEdit *passwordLine;

    QVBoxLayout *confirmLayout;
    QPushButton *confirmButton;

    QVBoxLayout *redirectToRegLayout;
    QLabel *toReg;

    //Registration page data
    QVBoxLayout *logoRegLayout;
    QLabel *logoRegLabel;

    QVBoxLayout *loginRegLayout;
    QLabel *loginRegLabel;
    QLineEdit *loginRegLine;

    QVBoxLayout *passwordRegLayout;
    QLabel *passwordRegLabel;
    QLineEdit *passwordRegLine;
    QLabel *passwordConfRegLabel;
    QLineEdit *passwordConfRegLine;

    QVBoxLayout *confirmRegLayout;
    QPushButton *confirmRegButton;

    QVBoxLayout *redirectToLogLayout;
    QLabel *toLog;

    //Network
    QNetworkAccessManager *networkManager;

    QWidget* createLoginForm();
    QWidget* createRegistrationForm();

    void saveToken(QString token);
};

#endif