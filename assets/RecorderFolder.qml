import bb.cascades 1.0

Container {
    property alias title: titleLabel.text
    property alias desc: descLabel.text
    property alias info: infoLabel.text
    property alias hilite: hiliteContainer.visible
    property alias div: divider.visible

    layout: DockLayout {

    }

    Container {
        id: hiliteContainer
        verticalAlignment: VerticalAlignment.Fill
        horizontalAlignment: HorizontalAlignment.Fill
        background: Color.create("#66bfbfbf")
    }

    Container {
        id: rowContainer
        verticalAlignment: VerticalAlignment.Center
        Container {
            layout: StackLayout {
                orientation: LayoutOrientation.TopToBottom

            }

            leftPadding: 15.0
            rightPadding: 15.0
            topPadding: 15.0
            bottomPadding: 15.0
            verticalAlignment: VerticalAlignment.Center

            Container {
                Label {
                    id: titleLabel
                    text: "Title"
                    textStyle.fontSizeValue: 8.0
                    textStyle.fontSize: FontSize.PointValue
                    verticalAlignment: VerticalAlignment.Center
                    textStyle.color: Color.White

                }

            }

            Container {
                horizontalAlignment: HorizontalAlignment.Fill

                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight

                }
                Container {
                    verticalAlignment: VerticalAlignment.Center
                    layoutProperties: StackLayoutProperties {
                        spaceQuota: 1.0

                    }

                    Label {
                        id: descLabel
                        text: "Desc"
                        textStyle.fontSizeValue: 7.0
                        textStyle.fontSize: FontSize.PointValue
                        verticalAlignment: VerticalAlignment.Center
                        textStyle.color: Color.White
                    }

                }
                Container {
                    verticalAlignment: VerticalAlignment.Center
                    Label {
                        id: infoLabel
                        text: "2 recordings"
                        textStyle.fontSize: FontSize.PointValue
                        textStyle.fontSizeValue: 7.0
                        textStyle.textAlign: TextAlign.Right
                        horizontalAlignment: HorizontalAlignment.Right
                        textStyle.color: Color.White
                    }
                }

            }

        }
        Container {
            leftPadding: 20.0
            rightPadding: 20.0
            Divider {
                id: divider
                horizontalAlignment: HorizontalAlignment.Fill
                visible: true
            }
        }

    }
}