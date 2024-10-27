#ifndef CONTENT_WINDOW_h
#define CONTENT_WINDOW_h

#include <QMainWindow>

class ContentWindow : public QMainWindow {
    
    Q_OBJECT

public:
    ContentWindow(QWidget *parent = nullptr);
    ~ContentWindow();
};

#endif