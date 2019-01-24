#include "actionlistlayout.h"

ActionListLayout::ActionListLayout(QWidget *parent)
    : QWidget(parent)
{
    initForm();
}

QLayout *ActionListLayout::layout()
{
    return layoutPtr;
}

void ActionListLayout::initForm()
{
    layoutPtr = new QBoxLayout(QBoxLayout::TopToBottom);
    QLabel *lbl = new QLabel(this);
    lbl->setFont(QFont("Helvetica [Cronyx]", 12, QFont::Bold));
    lbl->setText("Action List");
    layoutPtr->addWidget(lbl);

    {
        QSpacerItem *spe = new QSpacerItem(200, this->height());
        layoutPtr->addItem(spe);
    }
    //actionListLayout.setRowStretch(1, 1);
}

void ActionListLayout::update() {
    int i;
    for(i = 0; i < currentActionList.size(); i++)
    {
        QLabel *lbl = qobject_cast<QLabel*>(layoutPtr->itemAt(i + 1)->widget());
        lbl->setText(currentActionList.at(i).toString());
    }
}

void ActionListLayout::slotAddToBuildQueue()
{
    ActionListMember *tmp = new ActionListMember;
    currentActionList.enqueue(*tmp);

    QLayoutItem *target = layoutPtr->takeAt(layoutPtr -> count() - 1);
    QLabel *lbl = new QLabel(this);
    layoutPtr->addWidget(lbl);
    layoutPtr->addItem(target);
}

bool ActionListLayout::buildFromQueue(DungeonStats* stats)
{
    if(!currentActionList.isEmpty())
    {
        auto& task = currentActionList.head();
        task.manaConsume(stats->spendMana(task.manaNeeds()));
        if(task.manaIsFull())
        {
            QLayoutItem *target = layoutPtr->takeAt(currentActionList.size());
            delete target->widget();
            currentActionList.dequeue();
            return true;
        }

        update();
    }
    return false;
}
