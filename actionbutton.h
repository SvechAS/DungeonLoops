#ifndef ACTIONBUTTON_H
#define ACTIONBUTTON_H

#include <QString>
#include <QWidget>
#include <QPushButton>

class ActionButton : public QPushButton
{
    Q_OBJECT
public:
    explicit ActionButton(QWidget *parent = nullptr,
                          QString bName = "",
                          QString bText = "");
    ~ActionButton();
};

#endif // ACTIONBUTTON_H
