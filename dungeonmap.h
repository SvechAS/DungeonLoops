#ifndef DUNGEONMAP_H
#define DUNGEONMAP_H

#define MAP_WALL 0
#define MAP_GROUND 1
#define MAP_CONSTRUCT 2
#define MAP_CORE 3

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QMouseEvent>
#include <QTimer>

class DungeonMap : public QGraphicsView
{
    Q_OBJECT
public:
    explicit DungeonMap(QWidget *parent = nullptr);
    ~DungeonMap();
    void updateScene();
    void startPlaning();

signals:
    void signalBuildingStart();

public slots:
    void slotBuildingEnd();

private slots:

private:
    QGraphicsScene      *scene;
    QGraphicsItemGroup  *groupMap,
                        *building;
    QTimer              *timer;
    QPixmap             wall, ground, construct, core,
                        mapPic;

    QPoint              cursorPos;
    QPoint              buildingPos;

    int                 mapData[15][15];
    bool isPlaning = false;
    void initMap();
    void loadRes();
    void drawMap();
    void redrawMap();
    void drawScene();
    void deleteItemsFromGroup(QGraphicsItemGroup *group_1);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

};

#endif // DUNGEONMAP_H
