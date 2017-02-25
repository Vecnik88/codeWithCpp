import QtQuick 2.2
import QtQuick.Window 2.0
import QtQuick.Controls 1.1


Rectangle {
    // инициализируем виджет
    visible: true
    width: 500
    height: 500
    color: "green"
    id: root

    Row{                                        // <---. строчно компануем кнопки
        id: tools
        Button
        {
            id: clear
            text: "CLEAR"
            onClicked: {
                canvas.clear()
            }
        }
            Button
        {
                id: save
                text: "SAVE"
                onClicked: {
                    mouse.save()
                }
}
    }
      Canvas{                                   // <---. объект для рисования
          id: canvas
          anchors.top: tools.bottom
          width: 500
          height: 500
          property int lastX: 0
          property int lastY: 0

          function clear()
          {
              var ctx = getContext("2d")
              ctx.reset()
              canvas.requestPaint()
              mouse.clear()
          }

          onPaint:
          {
                var ctx = getContext("2d")
              ctx.lineWidth = 2
              ctx.strokeStyle = color.red

              ctx.beginPath()
              ctx.moveTo(lastX, lastY)

              lastX = area.mouseX
              lastY = area.mouseY

              ctx.lineTo(lastX, lastY)
              ctx.stroke()
          }
      MouseArea{
          id: area
          anchors.fill: parent
          onPressed: {
              canvas.lastX = mouseX
              canvas.lastY = mouseY
          }
          onPositionChanged: {
              canvas.requestPaint()
          }
      }
      }
}

