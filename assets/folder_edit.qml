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

            Container {
                id: titleContainer
                objectName: "titleContainer"

                horizontalAlignment: HorizontalAlignment.Left
                topPadding: 20.0
                bottomPadding: 10.0
                leftPadding: 20.0
                Label {
                    id: titleLabel
                    horizontalAlignment: HorizontalAlignment.Left
                    text: "Edit Folder"
                    textStyle.fontSize: FontSize.PointValue
                    textStyle.fontSizeValue: 9.0
                    textStyle.color: Color.White
                    textStyle.fontWeight: FontWeight.Bold
                    objectName: "titleLabel"
                }
            }
            Container {
                horizontalAlignment: HorizontalAlignment.Fill
                verticalAlignment: VerticalAlignment.Fill

                layoutProperties: StackLayoutProperties {
                    spaceQuota: 1.0

                }
                leftPadding: 20.0
                rightPadding: 20.0
                Container {
                    topPadding: 10.0
                    bottomPadding: 20.0
                    TextField {
                        id: titleText
                        objectName: "titleText"
                        hintText: "Folder title"
                        input.submitKey: SubmitKey.Next
                        input {
                            onSubmitted: {
                                descText.requestFocus();
                            }
                        }
                    }
                }
                Container {
                    verticalAlignment: VerticalAlignment.Fill
                    layoutProperties: StackLayoutProperties {
                        spaceQuota: 1.0

                    }
                    bottomPadding: 20.0
                    TextArea {
                        id: descText
                        objectName: "descText"
                        maximumLength: 50
                        hintText: "Folder description"
                        layoutProperties: StackLayoutProperties {
                            spaceQuota: 1.0

                        }
                        input.submitKey: SubmitKey.Done
                        //                        input.submitKey: SubmitKey.Done
                    }

                }
            }

            Container {
                id: navContainer
                objectName: "navContainer"

                horizontalAlignment: HorizontalAlignment.Fill
                topPadding: 20.0
                bottomPadding: 20.0
                leftPadding: 20.0
                rightPadding: 20.0
                verticalAlignment: VerticalAlignment.Bottom
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight

                }

                Container {
                    verticalAlignment: VerticalAlignment.Center
                    ImageView {
                        id: closeImage
                        objectName: "closeImage"
                        imageSource: "asset:///images/no.png"
                        horizontalAlignment: HorizontalAlignment.Left
                    }
                }
                Container {
                    horizontalAlignment: HorizontalAlignment.Center
                    verticalAlignment: VerticalAlignment.Center
                    layoutProperties: StackLayoutProperties {
                        spaceQuota: 1.0

                    }

                    ImageView {
                        id: deleteImage
                        objectName: "deleteImage"
                        imageSource: "asset:///images/delete.png"
                        horizontalAlignment: HorizontalAlignment.Center
                        verticalAlignment: VerticalAlignment.Center
                    }

                }
                Container {
                    verticalAlignment: VerticalAlignment.Center
                    ImageView {
                        id: saveImage
                        objectName: "saveImage"
                        imageSource: "asset:///images/yes.png"
                        horizontalAlignment: HorizontalAlignment.Right
                    }
                }
            }
        }
    }
}