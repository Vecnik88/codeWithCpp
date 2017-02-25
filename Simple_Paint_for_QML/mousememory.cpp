#include "mousememory.h"

MouseMemory::MouseMemory(QObject *parent) :
    QObject(parent)
{
}

void MouseMemory::clear()
{
    qDebug() << "Clear the data";
}

void MouseMemory::save()
{
    qDebug() << "Save the pointer";
}
