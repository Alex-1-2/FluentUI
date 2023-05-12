﻿import QtQuick
import QtQuick.Layouts
import QtQuick.Window
import QtQuick.Controls
import FluentUI
import "../component"

FluScrollablePage{

    title:"Acrylic"

    FluArea{
        Layout.fillWidth: true
        Layout.topMargin: 20
        height: 1439/5+20
        paddings: 10

        FluRectangle{
            width: 1080/5
            height: 1439/5
            radius:[25,25,25,25]
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 20
            Image {
                asynchronous: true
                source: "qrc:/example/res/image/image_huoyin.webp"
                anchors.fill: parent
                sourceSize: Qt.size(width,height)
                FluAcrylic {
                    anchors.centerIn: parent
                    width: 100
                    height: 100
                    FluText {
                        anchors.centerIn: parent
                        text: "Acrylic"
                        color: "#FFFFFF"
                        font.bold: true
                    }
                }
            }
        }
    }
    CodeExpander{
        Layout.fillWidth: true
        Layout.topMargin: -1
        code:'Image{
    width: 800
    height: 600
    source: "qrc:/example/res/image/image_huoyin.webp"
    radius: 8
    FluAcrylic{
        width: 100
        height: 100
        anchors.centerIn: parent
    }
}'
    }

}
