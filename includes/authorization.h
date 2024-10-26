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

class Authorization : public QDialog {

    Q_OBJECT

public:
    explicit Authorization(QWidget *parent = nullptr);
    ~Authorization();
private:
    QStackedWidget *loginWidget;
    QStackedWidget *registrationWidget;

    QVBoxLayout *mainLayout;

    QVBoxLayout *loginLayout;
    QLabel *loginLabel;
    QLineEdit *loginLine;

    QVBoxLayout *passwordLayout;
    QLabel *passwordLabel;
    QLineEdit *passwordLine;

    QVBoxLayout *confirmLayout;
    QPushButton *confirmButton;

    QNetworkAccessManager *networkManager;

    void switchToLoginForm();
    void switchToRegistrationForm();

    void sendLoginForm();
    void sendRegistrationForm();

    void saveToken(QString token);
};

#endif