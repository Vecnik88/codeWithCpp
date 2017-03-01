import QtQuick 2.6

Item {

    id: ticTac
    property var array: [0, 0, 0, 0, 0, 0, 0, 0, 0]

    property bool isFirstPlayer: true

    property bool isGamePlay: true

    Cell
    {
        id: cell0
        position: 0

        anchors.centerIn: parent
        anchors.horizontalCenterOffset: -width
        anchors.verticalCenterOffset: -height

        enabled: isGamePlay
    }
    Cell
    {
        position: 1

        anchors.centerIn: parent
        anchors.verticalCenterOffset: -height

        enabled: isGamePlay
    }
    Cell
    {
        position: 2

        anchors.centerIn: parent
        anchors.horizontalCenterOffset: width
        anchors.verticalCenterOffset: -height

        enabled: isGamePlay
    }
    Cell
    {
        position: 3

        anchors.centerIn: parent
        anchors.horizontalCenterOffset: -width

        enabled: isGamePlay
    }
    Cell
    {
        position: 4

        anchors.centerIn: parent

        enabled: isGamePlay
    }
    Cell
    {
        position: 5

        anchors.centerIn: parent
        anchors.horizontalCenterOffset: width

        enabled: isGamePlay
    }
    Cell
    {
        position: 6

        anchors.centerIn: parent
        anchors.horizontalCenterOffset: -width
        anchors.verticalCenterOffset: height

        enabled: isGamePlay
    }
    Cell
    {
        position: 7

        anchors.centerIn: parent
        anchors.verticalCenterOffset: height

        enabled: isGamePlay
    }
    Cell
    {
        position: 8

        anchors.centerIn: parent
        anchors.horizontalCenterOffset: width
        anchors.verticalCenterOffset: height

        enabled: isGamePlay
    }

    Text
    {
        id: course
        anchors.verticalCenterOffset: 100
        anchors.horizontalCenter: parent.horizontalCenter
        text: "Course first player"

        font.pixelSize: 30
        color: "green"
    }
    Text
    {
        id: winnerText
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: cell0.top
        text: ""

        font.pixelSize: 30
        color: "red"
    }

    function isGameOver()
    {
        isResult(0,1,2)
        isResult(3,4,5)
        isResult(6,7,8)
        isResult(0,4,8)
        isResult(2,4,6)
        isResult(0,3,6)
        isResult(1,4,7)
        isResult(2,5,8)
    }

    function isResult(x,y,z)
    {
        if(array[x] == array[y] && array[y] == array[z] && array[x] != 0)
        {
            if(isFirstPlayer)
            {
                winnerText.text = "Winner first player! Congratulations!"
                ticTac.isGamePlay = false
                course.text = ""
            }
            else
            {
                winnerText.text = "Winner second player! Congratulations!"
                ticTac.isGamePlay = false
                course.text = ""
            }
        }
        if(array[0] != 0 && array[1] != 0 && array[2] != 0 &&
                array[3] != 0 && array[4] != 0 && array[5] != 0 &&
                array[6] != 0 && array[7] != 0 && array[8] != 0)
        {
            winnerText.text = "Friend Draw"
            course.text = ""
        }
    }

}
