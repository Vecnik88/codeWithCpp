import QtQuick 2.0

import QtQuick 2.0
import QtQuick.Controls 1.1

Item {
    id: cell
    width: 100
    height: 100
    /*
        0 - клетка пустая
        1 - в клетке х
        2 - в клетке 0
    */
    property var st: 0

    property var position

    Rectangle{
        anchors.fill: parent
        color: "blue"
        radius: 20
    }

    Image {
        id: plus
        anchors.fill: parent
        source: "http://branto.ru/Emoji/8/734.png"
        opacity: cell.st == 1 ? 1 : 0
    }

    Image {
        id: zero
        anchors.fill: parent
        source: "https://cdn.pixabay.com/photo/2015/02/13/09/48/pay-634905_640.png"
        opacity: cell.st == 2 ? 1 : 0
    }

    MouseArea{
        anchors.fill: parent

        onClicked: {
        if(cell.st == 0)
        {
            if(ticTac.isFirstPlayer)
            {
                course.text = "Course second player"
                cell.st = 1;
                ticTac.array[cell.position] = 1
                isGameOver()
                ticTac.isFirstPlayer = false
            }
            else
            {
                course.text = "Course first player"
                cell.st = 2;
                ticTac.array[cell.position] = 2
                isGameOver()
                ticTac.isFirstPlayer = true
            }
        }
        }
}
}
