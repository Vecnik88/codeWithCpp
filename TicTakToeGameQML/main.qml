import QtQuick 2.6
import QtQuick.Window 2.2

Window
    {
    visible: true

    id: boss
    title: "TicTakToe"
    width: 700
    height: 500
    color: "cyan"

    TicTakToe{
        anchors.fill: parent
    }
    }

