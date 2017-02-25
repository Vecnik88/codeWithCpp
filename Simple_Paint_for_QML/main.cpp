#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"
#include <QQmlEngine>
#include <QQmlContext>
#include "mousememory.h"
#include <QScopedPointer>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QScopedPointer <MouseMemory> mouse(new MouseMemory);

    QtQuick2ApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/untitled35/main.qml"));
    viewer.show();

    viewer.rootContext()->setContextProperty("mouse", mouse.data());
    return app.exec();
}
