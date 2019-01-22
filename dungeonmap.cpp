#include "dungeonmap.h"

DungeonMap::DungeonMap(QWidget *parent) : QGraphicsView(parent)
{
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setAlignment(Qt::AlignTop);
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    this->setFixedSize(302, 302);
    this->setMouseTracking(true);

    loadRes();
    initMap();
    drawMap();

    scene = new QGraphicsScene();
    this->setScene(scene);
    groupMap = new QGraphicsItemGroup();
    building = new QGraphicsItemGroup();
    scene->addItem(groupMap);
    scene->addItem(building);
    drawScene();
}

DungeonMap::~DungeonMap()
{

}

void DungeonMap::initMap()
{
    for(int i = 0; i < 15; i++)
        for(int j = 0; j < 15; j++)
        {
            mapData[i][j] = MAP_WALL;
        }
    mapData[7][0] = MAP_GROUND;
    mapData[6][1] = MAP_GROUND;
    mapData[7][1] = MAP_GROUND;
    mapData[6][2] = MAP_GROUND;
    mapData[7][2] = MAP_GROUND;
    mapData[8][2] = MAP_GROUND;
    mapData[6][3] = MAP_GROUND;
    mapData[7][3] = MAP_GROUND;
    mapData[8][3] = MAP_GROUND;
    mapData[7][4] = MAP_GROUND;
    mapData[8][4] = MAP_GROUND;
}

void DungeonMap::mouseMoveEvent(QMouseEvent *event)
{
    cursorPos = event->pos();
}

void DungeonMap::mouseReleaseEvent(QMouseEvent *event)
{
    if((isPlaning) && (event->button() == Qt::LeftButton) &&
      (mapData[cursorPos.x() / 20][cursorPos.y() / 20] == MAP_GROUND))
    {
        buildingPos.setX(cursorPos.x() / 20);
        buildingPos.setY(cursorPos.y() / 20);

        isPlaning = false;
        mapData[buildingPos.x()][buildingPos.y()] = MAP_CONSTRUCT;
        emit signalBuildingStart();
    }
    drawMap();
}

void DungeonMap::slotBuildingEnd()
{
    mapData[buildingPos.x()][buildingPos.y()] = MAP_CORE;
    drawMap();
}

void DungeonMap::loadRes()
{
    wall.load(":/data/stone.png");
    wall = wall.scaled(20, 20);
    ground.load(":/data/ground.png");
    ground = ground.scaled(20, 20);
    construct.load(":/data/construct.png");
    construct = construct.scaled(20, 20);
    core.load(":/data/core.png");
    core = core.scaled(20, 20);
}

void DungeonMap::drawMap()
{
    QPixmap pixmap(this->width(), this->height());
    QPainter painter(&pixmap);
    for(int i = 0; i < 15; i++)
        for(int j = 0; j < 15; j++)
        {
            switch(mapData[i][j])
            {
            case MAP_WALL:
                painter.drawPixmap(i * 20, j * 20, 20, 20, wall);
                break;
            case MAP_GROUND:
                painter.drawPixmap(i * 20, j * 20, 20, 20, ground);
                break;
            case MAP_CONSTRUCT:
                painter.drawPixmap(i * 20, j * 20, 20, 20, construct);
                break;
            case MAP_CORE:
                painter.drawPixmap(i * 20, j * 20, 20, 20, core);
            }
        }
    painter.end();
    mapPic = pixmap;
}

void DungeonMap::redrawMap()
{

}

void DungeonMap::drawScene()
{
    this->deleteItemsFromGroup(groupMap);
    this->deleteItemsFromGroup(building);
    scene->setSceneRect(0, 0, width(), height());
    groupMap->addToGroup(scene->addPixmap(mapPic));
    if(underMouse())
        if(isPlaning)
        {
            QPen *pen = new QPen();
            if(mapData[cursorPos.x() / 20][cursorPos.y() / 20] == MAP_GROUND)
                pen->setColor(QColor(20, 240, 20));
            else
                pen->setColor(QColor(240, 20, 20));
            building->addToGroup(scene->addRect(cursorPos.x() / 20 * 20, cursorPos.y() / 20 * 20, 19, 19, *pen));
        }
}

void DungeonMap::deleteItemsFromGroup(QGraphicsItemGroup *group)
{
    foreach( QGraphicsItem *item, scene->items(group->boundingRect()))
        if(item->group() == group )
            delete item;
}

void DungeonMap::updateScene()
{
    drawScene();
}

void DungeonMap::startPlaning()
{
    isPlaning = true;
}
