import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15
import FluentUI 1.0
import "../component"
import "../viewmodel"

FluScrollablePage{

    title: qsTr("TextBox")

    TextBoxViewModel{
        id:viewModel
    }

    FluArea{
        Layout.fillWidth: true
        height: 68
        paddings: 10
        Layout.topMargin: 20

        FluTextBox{
            placeholderText: qsTr("Single-line Input Box")
            disabled: text_box_switch.checked
            cleanEnabled: true
            text: viewModel.text1
            onTextChanged: {
                viewModel.text1 = text
            }
            anchors{
                verticalCenter: parent.verticalCenter
                left: parent.left
            }
        }

        FluToggleSwitch{
            id: text_box_switch
            anchors{
                verticalCenter: parent.verticalCenter
                right: parent.right
            }
            text: qsTr("Disabled")
        }
    }
    CodeExpander{
        Layout.fillWidth: true
        Layout.topMargin: -1
        code:'FluTextBox{
    placeholderText: qsTr("Single-line Input Box")
}'
    }

    FluArea{
        Layout.fillWidth: true
        height: 68
        paddings: 10
        Layout.topMargin: 20

        FluPasswordBox{
            placeholderText: qsTr("Please enter your password")
            disabled:password_box_switch.checked
            anchors{
                verticalCenter: parent.verticalCenter
                left: parent.left
            }
        }
        FluToggleSwitch{
            id:password_box_switch
            anchors{
                verticalCenter: parent.verticalCenter
                right: parent.right
            }
            text: qsTr("Disabled")
        }
    }
    CodeExpander{
        Layout.fillWidth: true
        Layout.topMargin: -1
        code:'FluPasswordBox{
    placeholderText: qsTr("Please enter your password")
}'
    }


    FluArea{
        Layout.fillWidth: true
        height: 36+multiine_textbox.height
        paddings: 10
        Layout.topMargin: 20

        FluMultilineTextBox{
            id: multiine_textbox
            placeholderText: qsTr("Multi-line Input Box")
            text:viewModel.text2
            onTextChanged: {
                viewModel.text2 = text
            }
            disabled: text_box_multi_switch.checked
            anchors{
                verticalCenter: parent.verticalCenter
                left: parent.left
            }
        }

        FluToggleSwitch{
            id:text_box_multi_switch
            anchors{
                verticalCenter: parent.verticalCenter
                right: parent.right
            }
            text: qsTr("Disabled")
        }
    }
    CodeExpander{
        Layout.fillWidth: true
        Layout.topMargin: -1
        code:'FluMultilineTextBox{
    placeholderText: qsTr("Multi-line Input Box")
}'
    }

    FluArea{
        Layout.fillWidth: true
        height: 68
        paddings: 10
        Layout.topMargin: 20
        FluAutoSuggestBox{
            placeholderText: qsTr("AutoSuggestBox")
            items: generateRandomNames(100)
            disabled: text_box_suggest_switch.checked
            anchors{
                verticalCenter: parent.verticalCenter
                left: parent.left
            }
        }
        FluToggleSwitch{
            id:text_box_suggest_switch
            anchors{
                verticalCenter: parent.verticalCenter
                right: parent.right
            }
            text: qsTr("Disabled")
        }
    }
    CodeExpander{
        Layout.fillWidth: true
        Layout.topMargin: -1
        code:'FluAutoSuggestBox{
    placeholderText: qsTr("AutoSuggestBox")
}'
    }

    FluArea{
        Layout.fillWidth: true
        height: 68
        paddings: 10
        Layout.topMargin: 20
        FluSpinBox{
            disabled: spin_box_switch.checked
            anchors{
                verticalCenter: parent.verticalCenter
                left: parent.left
            }
        }
        FluToggleSwitch{
            id: spin_box_switch
            anchors{
                verticalCenter: parent.verticalCenter
                right: parent.right
            }
            text: qsTr("Disabled")
        }
    }
    CodeExpander{
        Layout.fillWidth: true
        Layout.topMargin: -1
        code:'FluSpinBox{

}'
    }

    function generateRandomNames(numNames) {
        const alphabet = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ';
        const names = [];
        function generateRandomName() {
            const nameLength = Math.floor(Math.random() * 5) + 4;
            let name = '';
            for (let i = 0; i < nameLength; i++) {
                const letterIndex = Math.floor(Math.random() * 26);
                name += alphabet.charAt(letterIndex);
            }
            return name;
        }
        for (let i = 0; i < numNames; i++) {
            const name = generateRandomName();
            names.push({title:name});
        }
        return names;
    }


}
