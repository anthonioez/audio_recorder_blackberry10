import bb.cascades 1.0

Page {

    Container {
        layout: DockLayout {
        }
        Container {
            horizontalAlignment: HorizontalAlignment.Fill
            verticalAlignment: VerticalAlignment.Fill
            ImageView {
                id: themeImage
                objectName: "themeImage"
                imageSource: "asset:///images/red.png"
                verticalAlignment: VerticalAlignment.Fill
                horizontalAlignment: HorizontalAlignment.Fill

            }
        }

        Container {
            horizontalAlignment: HorizontalAlignment.Fill

            Container {
                id: titleContainer
                objectName: "titleContainer"
                topPadding: 20.0

                leftPadding: 20.0
                rightPadding: 20.0
                horizontalAlignment: HorizontalAlignment.Fill
                verticalAlignment: VerticalAlignment.Top

                Label {
                    id: titleLabel
                    horizontalAlignment: HorizontalAlignment.Center
                    verticalAlignment: VerticalAlignment.Center
                    text: "Recorder+"
                    textStyle.fontSize: FontSize.PointValue
                    textStyle.fontSizeValue: 9.0
                    textStyle.color: Color.White
                    objectName: "titleLabel"
                    textStyle.textAlign: TextAlign.Center
                    textStyle.fontWeight: FontWeight.Bold
                }
            }

            Container {
                id: timeContainer
                objectName: "timeContainer"
                verticalAlignment: VerticalAlignment.Top
                horizontalAlignment: HorizontalAlignment.Center
                topPadding: 20.0
                Label {
                    id: timeLabel
                    objectName: "timeLabel"
                    text: "00:00"
                    textStyle.color: Color.White
                    horizontalAlignment: HorizontalAlignment.Center
                    verticalAlignment: VerticalAlignment.Center
                    textStyle.fontSize: FontSize.PointValue
                    textStyle.fontSizeValue: 9.0
                    textStyle.fontWeight: FontWeight.Bold
                }

            }
            Container {
                id: sizeContainer
                objectName: "sizeContainer"
                verticalAlignment: VerticalAlignment.Top
                horizontalAlignment: HorizontalAlignment.Center
                topPadding: 10.0
                Label {
                    id: sizeLabel
                    objectName: "sizeLabel"
                    text: "10kb"
                    textStyle.color: Color.White
                    horizontalAlignment: HorizontalAlignment.Center
                    verticalAlignment: VerticalAlignment.Center
                    textStyle.fontSize: FontSize.PointValue
                    textStyle.fontSizeValue: 6.0
                    textStyle.fontWeight: FontWeight.Bold
                }

            }
        }

        Container {

            objectName: "sliderContainer"

            verticalAlignment: VerticalAlignment.Center
            horizontalAlignment: HorizontalAlignment.Center

            Container {
                id: actionContainer

                objectName: "actionContainer"
                verticalAlignment: VerticalAlignment.Center
                horizontalAlignment: HorizontalAlignment.Center
                ImageView {
                    id: actionImage
                    imageSource: "asset:///images/record_big.png"
                    objectName: "actionImage"
                    horizontalAlignment: HorizontalAlignment.Center
                    verticalAlignment: VerticalAlignment.Center
                }
            }
            Container {
                topPadding: 10.0
                horizontalAlignment: HorizontalAlignment.Center
                verticalAlignment: VerticalAlignment.Center
                Label {
                    id: tipsLabel
                    text: "touch the circle to record"
                    objectName: "tipsLabel"
                    textStyle.color: Color.White
                    textStyle.fontSize: FontSize.PointValue
                    textStyle.fontSizeValue: 6.0
                    textStyle.fontStyle: FontStyle.Italic

                }
            }
        }
        Container {
            horizontalAlignment: HorizontalAlignment.Fill
            verticalAlignment: VerticalAlignment.Bottom
            Container {
                id: statusContainer
                objectName: "statusContainer"
                verticalAlignment: VerticalAlignment.Bottom
                horizontalAlignment: HorizontalAlignment.Center
                topPadding: 0.0

                bottomPadding: 20.0
                Label {
                    id: statusLabel
                    objectName: "statusLabel"
                    text: "Recording"
                    textStyle.fontSize: FontSize.PointValue
                    textStyle.fontSizeValue: 6.0
                    textStyle.color: Color.White
                    verticalAlignment: VerticalAlignment.Center
                    horizontalAlignment: HorizontalAlignment.Center
                }
            }
            Container {
                id: editContainer
                horizontalAlignment: HorizontalAlignment.Center
                topPadding: 20.0
                bottomPadding: 20.0
                leftPadding: 20.0
                rightPadding: 20.0
                verticalAlignment: VerticalAlignment.Bottom
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight

                }
                objectName: "editContainer"

                visible: false

                Container {
                    ImageView {
                        id: cancelImage
                        objectName: "cancelImage"
                        imageSource: "asset:///images/no.png"
                        horizontalAlignment: HorizontalAlignment.Left
                        verticalAlignment: VerticalAlignment.Center
                    }
                }

                Container {
                    layoutProperties: StackLayoutProperties {
                        spaceQuota: 1.0

                    }
                    verticalAlignment: VerticalAlignment.Center
                    horizontalAlignment: HorizontalAlignment.Center

                }
                Container {
                    ImageView {
                        id: stopImage
                        objectName: "stopImage"
                        imageSource: "asset:///images/stop.png"
                        horizontalAlignment: HorizontalAlignment.Right
                        verticalAlignment: VerticalAlignment.Center
                    }
                }
            }
            Container {
                id: navContainer
                horizontalAlignment: HorizontalAlignment.Fill
                topPadding: 20.0
                bottomPadding: 20.0
                leftPadding: 20.0
                rightPadding: 20.0
                verticalAlignment: VerticalAlignment.Bottom
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight

                }
                objectName: "navContainer"

                Container {
                    ImageView {
                        id: folderImage
                        objectName: "folderImage"
                        imageSource: "asset:///images/folder.png"
                        horizontalAlignment: HorizontalAlignment.Left
                        verticalAlignment: VerticalAlignment.Center
                    }
                }
                Container {
                    layoutProperties: StackLayoutProperties {
                        spaceQuota: 1.0
                    }
                    verticalAlignment: VerticalAlignment.Center
                    ImageView {
                        id: settingsImage
                        objectName: "settingsImage"
                        imageSource: "asset:///images/settings.png"
                        horizontalAlignment: HorizontalAlignment.Center
                        verticalAlignment: VerticalAlignment.Center
                        visible: false
                    }
                }
                Container {
                    ImageView {
                        id: listImage
                        objectName: "listImage"
                        imageSource: "asset:///images/open.png"
                        horizontalAlignment: HorizontalAlignment.Right
                        verticalAlignment: VerticalAlignment.Center
                    }
                }
            }
        }
    }
}