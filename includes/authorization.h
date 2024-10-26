#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QDialog>

class Authorization : public QDialog {

    Q_OBJECT

public:
    explicit Authorization(QWidget *parent = nullptr);
    ~Authorization();

};

#endif