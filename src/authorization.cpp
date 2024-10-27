#include "../includes/authorization.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkReply>
#include <QDebug>

Authorization::Authorization(QWidget *parent) : QDialog(parent) {
    this->setFixedSize(800,500);

    stackedWidget = new QStackedWidget(this);

    loginWidget = createLoginForm();
    registrationWidget = createRegistrationForm();

    stackedWidget->addWidget(loginWidget);
    stackedWidget->addWidget(registrationWidget);

    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(stackedWidget);

    setLayout(mainLayout);    

    networkManager = new QNetworkAccessManager(this);
}

QWidget* Authorization::createLoginForm() {
    QWidget *page = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;

    layout = new QVBoxLayout;
    layout->setSpacing(30);
    layout->addStretch(1);

    logoLogLayout = new QVBoxLayout;
    logoLogLabel = new QLabel("Login");
    logoLogLabel->setStyleSheet("font-size: 20px; font-weight: bold;");
    logoLogLayout->setAlignment(Qt::AlignCenter);
    logoLogLayout->setSpacing(0);
    logoLogLayout->addWidget(logoLogLabel);

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
    passwordLine->setEchoMode(QLineEdit::Password);
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

    redirectToRegLayout = new QVBoxLayout;
    toReg = new QLabel("<a href='#'>Create account</a>");
    toReg->setTextInteractionFlags(Qt::TextBrowserInteraction);
    toReg->setFixedWidth(80);
    redirectToRegLayout->addWidget(toReg);
    
    layout->addLayout(logoLogLayout);
    layout->addLayout(loginLayout);
    layout->addLayout(passwordLayout);
    layout->addLayout(confirmLayout);
    layout->addLayout(redirectToRegLayout);

    layout->addStretch(1);

    page->setLayout(layout);

    connect(confirmButton, &QPushButton::clicked, this, &Authorization::sendLoginForm);
    connect(toReg, &QLabel::linkActivated, this, [this]() {
        stackedWidget->setCurrentIndex(1);
    });

    return page;
}

QWidget* Authorization::createRegistrationForm() {
    QWidget *page = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;

    layout = new QVBoxLayout;
    layout->setSpacing(30);
    layout->addStretch(1);

    logoRegLayout = new QVBoxLayout;
    logoRegLabel = new QLabel("Registration");
    logoRegLabel->setStyleSheet("font-size: 20px; font-weight: bold;");
    logoRegLayout->setAlignment(Qt::AlignCenter);
    logoRegLayout->setSpacing(0);
    logoRegLayout->addWidget(logoRegLabel);

    loginRegLayout = new QVBoxLayout;
    loginRegLabel = new QLabel("Email");
    loginRegLine = new QLineEdit;
    loginRegLine->setFixedWidth(380);
    loginRegLine->setFixedHeight(40);
    loginRegLayout->setAlignment(Qt::AlignCenter);
    loginRegLayout->setSpacing(0);
    loginRegLayout->addWidget(loginRegLabel);
    loginRegLayout->addWidget(loginRegLine);

    passwordRegLayout = new QVBoxLayout;
    passwordRegLabel = new QLabel("Password");
    passwordRegLine = new QLineEdit;
    passwordRegLine->setEchoMode(QLineEdit::Password);
    passwordRegLine->setFixedWidth(380);
    passwordRegLine->setFixedHeight(40);
    passwordConfRegLabel = new QLabel("Confirm password");
    passwordConfRegLine = new QLineEdit;
    passwordConfRegLine->setEchoMode(QLineEdit::Password);
    passwordConfRegLine->setFixedWidth(380);
    passwordConfRegLine->setFixedHeight(40);
    passwordRegLayout->setAlignment(Qt::AlignCenter);
    passwordRegLayout->setSpacing(0);
    passwordConfRegLabel->setContentsMargins(0,30,0,0);
    passwordRegLayout->addWidget(passwordRegLabel);
    passwordRegLayout->addWidget(passwordRegLine);
    passwordRegLayout->addWidget(passwordConfRegLabel);
    passwordRegLayout->addWidget(passwordConfRegLine);

    confirmRegLayout = new QVBoxLayout;
    confirmRegButton = new QPushButton("Registration");
    confirmRegButton->setFixedWidth(220);
    confirmRegButton->setFixedHeight(40);
    confirmRegLayout->setAlignment(Qt::AlignCenter);
    confirmRegLayout->setSpacing(0);
    confirmRegLayout->addWidget(confirmRegButton);

    redirectToLogLayout = new QVBoxLayout;
    toLog = new QLabel("<a href='#'>Already have an account</a>");
    toLog->setTextInteractionFlags(Qt::TextBrowserInteraction);
    toLog->setFixedWidth(130);
    redirectToLogLayout->addWidget(toLog);
    
    layout->addLayout(logoRegLayout);
    layout->addLayout(loginRegLayout);
    layout->addLayout(passwordRegLayout);
    layout->addLayout(confirmRegLayout);
    layout->addLayout(redirectToLogLayout);

    layout->addStretch(1);

    page->setLayout(layout);

    connect(confirmRegButton, &QPushButton::clicked, this, &Authorization::sendRegistrationForm);
    connect(toLog, &QLabel::linkActivated, this, [this]() {
        stackedWidget->setCurrentIndex(0);
    });

    return page;
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
    // confirmRegButton->setEnabled(false);

    QString login = loginRegLine->text();
    QString password = passwordRegLine->text();
}

void Authorization::saveToken(QString token) {
    //Сохранить токен, но где? :D
}

Authorization::~Authorization() {
    
}