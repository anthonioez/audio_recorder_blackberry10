import bb.cascades 1.0

Page {
    signal editItem(variant object)
    signal deleteItem(variant object)
    signal addItem(variant object)

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
                horizontalAlignment: HorizontalAlignment.Fill
                topPadding: 20.0
                bottomPadding: 10.0
                leftPadding: 20.0
                rightPadding: 20.0
                verticalAlignment: VerticalAlignment.Top
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight

                }
                objectName: "titleContainer"

                visible: true
                Container {
                    verticalAlignment: VerticalAlignment.Center
                    ImageView {
                        id: deleteImage
                        objectName: "deleteImage"
                        imageSource: "asset:///images/delete.png"
                        horizontalAlignment: HorizontalAlignment.Left
                        verticalAlignment: VerticalAlignment.Center
                    }
                }
                Container {
                    layoutProperties: StackLayoutProperties {
                        spaceQuota: 1.0
                    }
                    verticalAlignment: VerticalAlignment.Center
                    Label {
                        id: titleLabel
                        objectName: "titleLabel"
                        text: "Edit"
                        textStyle.fontSize: FontSize.PointValue
                        textStyle.fontSizeValue: 8.0
                        textStyle.color: Color.White
                        textStyle.fontWeight: FontWeight.Bold
                        horizontalAlignment: HorizontalAlignment.Center
                        verticalAlignment: VerticalAlignment.Center
                    }
                }
                Container {
                    verticalAlignment: VerticalAlignment.Center
                    ImageView {
                        id: actionImage
                        objectName: "actionImage"
                        imageSource: "asset:///images/edit.png"
                        horizontalAlignment: HorizontalAlignment.Right
                    }
                }
            }
            Container {
                id: noteContainer

                horizontalAlignment: HorizontalAlignment.Fill
                verticalAlignment: VerticalAlignment.Fill
                leftPadding: 20.0
                rightPadding: 20.0

                layoutProperties: StackLayoutProperties {
                    spaceQuota: 1.0

                }

                layout: DockLayout {

                }
                Container {
                    id: viewContainer
                    horizontalAlignment: HorizontalAlignment.Fill
                    verticalAlignment: VerticalAlignment.Fill

                    layoutProperties: StackLayoutProperties {
                        spaceQuota: 1.0

                    }

                    objectName: "viewContainer"
                    visible: false

                    ScrollView {
                        scrollViewProperties.scrollMode: ScrollMode.Vertical

                        horizontalAlignment: HorizontalAlignment.Fill
                        verticalAlignment: VerticalAlignment.Fill
                        Container {
                            verticalAlignment: VerticalAlignment.Fill
                            layoutProperties: StackLayoutProperties {
                                spaceQuota: 1.0

                            }
                            horizontalAlignment: HorizontalAlignment.Fill

                            Label {
                                id: bodyLabel
                                objectName: "bodyLabel"
                                text: "..."
                                textStyle.color: Color.White
                                multiline: true
                                textFormat: TextFormat.Auto
                            }
                        }
                    }

                }
                Container {
                    id: editContainer
                    verticalAlignment: VerticalAlignment.Fill
                    horizontalAlignment: HorizontalAlignment.Fill
                    layoutProperties: StackLayoutProperties {
                        spaceQuota: 1.0

                    }
                    layout: StackLayout {

                    }

                    visible: true
                    objectName: "editContainer"
                    Container {

                        topPadding: 10.0

                        bottomPadding: 20.0
                        TextField {
                            id: titleEdit
                            hintText: "Recording title"
                            objectName: "titleText"
                            input.submitKey: SubmitKey.Next
                            input {
                                onSubmitted: {
                                    bodyText.requestFocus();
                                }
                            }
                        }
                    }
                    Container {
                        verticalAlignment: VerticalAlignment.Fill
                        layoutProperties: StackLayoutProperties {
                            spaceQuota: 1.0

                        }

                        background: Color.DarkYellow
                        TextArea {
                            id: bodyText
                            hintText: "Recording description"
                            objectName: "bodyText"
                            maximumLength: 10240
                            verticalAlignment: VerticalAlignment.Fill
                            horizontalAlignment: HorizontalAlignment.Fill
                            layoutProperties: StackLayoutProperties {
                                spaceQuota: 1.0

                            }

                            //                        input.submitKey: SubmitKey.Done
                        }

                    }
                }

            }
            Container {
                id: itemContainer
                leftPadding: 30.0
                rightPadding: 30.0
                Container {
                    horizontalAlignment: HorizontalAlignment.Fill
                    topPadding: 20.0
                    layout: DockLayout {

                    }
                    
                    Slider {
                        id: seekSlider
                        objectName: "seekSlider"
                        horizontalAlignment: HorizontalAlignment.Fill
                    }

                }                
                Container {
                    layout: StackLayout {
                        orientation: LayoutOrientation.LeftToRight

                    }
                    topPadding: 5.0
                    bottomPadding: 5.0
                    Container {
                        verticalAlignment: VerticalAlignment.Center
                        Label {
                            id: startLabel
                            objectName: "startLabel"
                            text: "0:00"
                            textStyle.fontSize: FontSize.PointValue
                            textStyle.fontSizeValue: 7.0
                            textStyle.color: Color.White

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
                        verticalAlignment: VerticalAlignment.Center
                        horizontalAlignment: HorizontalAlignment.Right
                        Label {
                            id: endLabel
                            objectName: "endLabel"
                            text: "0:00"
                            textStyle.fontSize: FontSize.PointValue
                            textStyle.fontSizeValue: 7.0
                            textStyle.color: Color.White

                        }
                    }
                }
            }

            Container {
                id: speedContainer
                objectName: "speedContainer"
                leftPadding: 30.0
                rightPadding: 30.0
                Container {
                    horizontalAlignment: HorizontalAlignment.Fill
                    topPadding: 20.0
                    layout: DockLayout {
                    
                    }
                    
                    Slider {
                        id: speedSlider
                        objectName: "speedSlider"
                        horizontalAlignment: HorizontalAlignment.Fill
                    }
                
                }
                Container {
                    layout: StackLayout {
                        orientation: LayoutOrientation.LeftToRight
                    
                    }
                    topPadding: 5.0
                    bottomPadding: 5.0
                    Container {
                        verticalAlignment: VerticalAlignment.Center
                        Label {
                            text: "normal"
                            textStyle.fontSize: FontSize.PointValue
                            textStyle.fontSizeValue: 7.0
                            textStyle.color: Color.White
                            verticalAlignment: VerticalAlignment.Center

                        }
                    }
                    Container {
                        layoutProperties: StackLayoutProperties {
                            spaceQuota: 1.0

                        }
                        verticalAlignment: VerticalAlignment.Center
                        horizontalAlignment: HorizontalAlignment.Center

                        Label {
                            visible: false
                            text: "speed"
                            objectName: "speedLabel"
                            textStyle.fontSize: FontSize.PointValue
                            textStyle.fontSizeValue: 7.0
                            textStyle.color: Color.White
                            verticalAlignment: VerticalAlignment.Center
                            horizontalAlignment: HorizontalAlignment.Center

                        }
                    }
                    Container {
                        verticalAlignment: VerticalAlignment.Center
                        horizontalAlignment: HorizontalAlignment.Right
                        Label {
                            text: "fast"
                            textStyle.fontSize: FontSize.PointValue
                            textStyle.fontSizeValue: 7.0
                            textStyle.color: Color.White
                            verticalAlignment: VerticalAlignment.Center
                            horizontalAlignment: HorizontalAlignment.Right

                        }
                    }
                }
            }
            Container {
                id: navContainer
                horizontalAlignment: HorizontalAlignment.Fill
                topPadding: 20.0
                bottomPadding: 20.0

                verticalAlignment: VerticalAlignment.Bottom
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight

                }
                objectName: "navContainer"

                rightPadding: 20.0
                leftPadding: 20.0
                Container {
                    verticalAlignment: VerticalAlignment.Center

                    ImageView {
                        id: closeImage1
                        objectName: "closeImage"
                        imageSource: "asset:///images/no.png"
                        horizontalAlignment: HorizontalAlignment.Left
                    }
                }
                Container {
                    layoutProperties: StackLayoutProperties {
                        spaceQuota: 1.0

                    }
                    ImageView {
                        id: playImage
                        objectName: "playImage"
                        imageSource: "asset:///images/play.png"
                        horizontalAlignment: HorizontalAlignment.Center
                    }
                }
                Container {
                    verticalAlignment: VerticalAlignment.Center

                    ImageView {
                        id: shareImage
                        objectName: "shareImage"
                        imageSource: "asset:///images/share.png"
                        horizontalAlignment: HorizontalAlignment.Right
                    }
                }
            }

        }
    }
}
