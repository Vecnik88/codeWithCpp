#ifndef MOUSEMEMORY_H
#define MOUSEMEMORY_H

#include <QObject>
#include <QDebug>
#include <QPoint>

class MouseMemory : public QObject
{
    Q_OBJECT
public:
    explicit MouseMemory(QObject *parent = 0);

    Q_INVOKABLE void clear();
    Q_INVOKABLE void save();

signals:

public slots:

};



#endif // MOUSEMEMORY_H
