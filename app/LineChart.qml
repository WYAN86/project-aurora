import QtQuick 2.15
import QtCharts 2.15
import QtGraphicalEffects 1.15

Item {
    id: lineChart
    property color mainColor: "#ffffff"
    property color subColor: "#4d4d4d"

    property int graphMaxY: 13000
    property int graphMinY: 0

    // Set this to canbuffer.powerSeries when Component.onCompleted happens
    property var series: series

    ChartView {
        id: chart
        anchors.fill: parent
        legend.visible: false
        backgroundColor: "transparent"
        visible: false
        antialiasing: true

        LineSeries {
            id: series
            color: "white"
            width: 3

            axisX: ValueAxis {
                color: "transparent"
                gridVisible: false
                labelsVisible: false
                max:0
                min:-100000
            }

            axisY: ValueAxis {
                color: "transparent"
                gridVisible: false
                labelsVisible: false
                max: lineChart.graphMaxY
            }
        }
    }

    LinearGradient {
        antialiasing: true
        start: Qt.point(0,0)
        end: Qt.point(parent.width,0)
        gradient: Gradient {
            GradientStop {
                    position: 0;
                    color: lineChart.subColor;
            }

            GradientStop {
                    position: 1;
                    color: lineChart.mainColor;
            }
       }
       anchors.fill: chart
       source: chart
    }
}
