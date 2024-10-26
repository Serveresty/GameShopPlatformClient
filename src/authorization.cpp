#include "../includes/authorization.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkReply>

Authorization::Authorization(QWidget *parent) : QDialog(parent) {
    this->setFixedSize(800,500);

    mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(30);
    mainLayout->addStretch(1);

    loginLayout = new QVBoxLayout;
    loginLabel = new QLabel("Email");
    loginLine = new QLineEdit;
    loginLine->setFixedWidth(380);
    loginLine->setFixedHeight(40);
    loginLayout->setAlignment(Qt::AlignCenter);
    loginLayout->setSpacing(0);
    loginLayout->addWidget(loginLabel);
    loginLayout->addWidget(loginLine);

    passwordLayout = new QVBoxLayout;
    passwordLabel = new QLabel("Password");
    passwordLine = new QLineEdit;
    passwordLine->setFixedWidth(380);
    passwordLine->setFixedHeight(40);
    passwordLayout->setAlignment(Qt::AlignCenter);
    passwordLayout->setSpacing(0);
    passwordLayout->addWidget(passwordLabel);
    passwordLayout->addWidget(passwordLine);

    confirmLayout = new QVBoxLayout;
    confirmButton = new QPushButton("Login");
    confirmButton->setFixedWidth(220);
    confirmButton->setFixedHeight(40);
    confirmLayout->setAlignment(Qt::AlignCenter);
    confirmLayout->setSpacing(0);
    confirmLayout->addWidget(confirmButton);
    
    mainLayout->addLayout(loginLayout);
    mainLayout->addLayout(passwordLayout);
    mainLayout->addLayout(confirmLayout);

    mainLayout->addStretch(1);

    this->setLayout(mainLayout);

    networkManager = new QNetworkAccessManager(this);

    connect(confirmButton, &QPushButton::clicked, this, &Authorization::sendLoginForm);
}

void Authorization::switchToLoginForm() {

}

void Authorization::switchToRegistrationForm() {

}

void Authorization::sendLoginForm() {
    confirmButton->setEnabled(false);

    QString login = loginLine->text();
    QString password = passwordLine->text();
    
    QUrl url("http://localhost:8080/auth/sign-in");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QJsonObject jsonData;
    jsonData["email"] = login;
    jsonData["password"] = password;

    QJsonDocument jsonDoc(jsonData);
    QByteArray byteArr = jsonDoc.toJson();

    QNetworkReply *reply = networkManager->post(request, byteArr);

    connect(reply, &QNetworkReply::finished, this, [this]() {
        QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray responseData = reply->readAll();

            QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);
            if (jsonResponse.isObject()) {
                QJsonObject jsonObject = jsonResponse.object();
                QString token = jsonObject["token"].toString();

                saveToken(token);

                this->close();

                // MainWindow *mainWindow = new MainWindow(); // New Window
                // mainWindow->show();
            }
        } else {
            qDebug() << "Error:" << reply->errorString();
            confirmButton->setEnabled(true);
        }
        reply->deleteLater();
    });
}

void Authorization::sendRegistrationForm() {

}

void Authorization::saveToken(QString token) {
    //Сохранить токен, но где? :D
}

Authorization::~Authorization() {
    
}