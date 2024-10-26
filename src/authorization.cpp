#include "../includes/authorization.h"

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

void Authorization::sendLoginForm() {
}

Authorization::~Authorization() {
    
}