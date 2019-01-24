#include "actionbutton.h"

ActionButton::ActionButton(QWidget *parent, QString bName, QString bText) : QPushButton(parent)
{
    setText(bText);
    setObjectName(bName);
    connect(this, SIGNAL(clicked()), parent, SLOT(slotButtonInActionListClicked()));
}

ActionButton::~ActionButton() {}
