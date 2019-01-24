#ifndef ACTIONLISTLAYOUT_H
#define ACTIONLISTLAYOUT_H

#include <QObject>
#include <QWidget>
#include <QBoxLayout>
#include <QQueue>
#include <QLabel>

#include "dungeonstats.h"

const static double EPS = 0.0000001;

class ActionListLayout : public QWidget
{
    Q_OBJECT

private:
    struct ActionListMember
    {
        QString name;
        double manaNeed;
        double manaGot;

        ActionListMember() {
            name = "Dungeon Core";
            manaNeed = 2500;
            manaGot = 0;
        }

        double manaNeeds(){
            return manaNeed - manaGot;
        }

        void manaConsume(double mana) {
            manaGot += mana;
        }

        bool manaIsFull() {
            return abs(manaNeeds()) < EPS;
        }

        QString toString() const {
            return "Building: " + name + " | Progress: " + QString::number(manaGot) + " / " + QString::number(manaNeed);
        }
    };

    void initForm();

public:
    explicit ActionListLayout(QWidget *parent = nullptr);

    QLayout* layout();
    QBoxLayout *layoutPtr;

    QQueue<ActionListMember> currentActionList;
    void update();
    bool buildFromQueue(DungeonStats* stats);
public slots:
    void slotAddToBuildQueue();
};

#endif // ACTIONLISTLAYOUT_H
