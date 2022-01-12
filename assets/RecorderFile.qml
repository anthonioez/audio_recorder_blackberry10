import bb.cascades 1.0

Container {

    property alias image: statusImage.imageSource
    property alias istate: statusImage.opacity
    property alias type: statusLabel.text
    property alias title: titleLabel.text
    property alias desc: descLabel.text
    property alias folder: folderLabel.text
    property alias size: sizeLabel.text
    property alias duration: durationLabel.text
    property alias date: dateLabel.text

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
                orientation: LayoutOrientation.LeftToRight

            }

            leftPadding: 10.0
            rightPadding: 10.0
            topPadding: 15.0
            bottomPadding: 15.0
            verticalAlignment: VerticalAlignment.Center

            Container {
                rightPadding: 10.0
                leftPadding: 10.0

                verticalAlignment: VerticalAlignment.Center

                layout: DockLayout {

                }
                Container {
                    verticalAlignment: VerticalAlignment.Center
                    ImageView {
                        id: statusImage
                        imageSource: "asset:///images/icon.png"
                        preferredWidth: 81.0
                        preferredHeight: 81.0
                        scalingMethod: ScalingMethod.AspectFit
                    }

                }
                Container {
                    horizontalAlignment: HorizontalAlignment.Right
                    verticalAlignment: VerticalAlignment.Bottom
                    Label {
                        id: statusLabel
                        text: "amr"
                        textStyle.color: Color.create("#ffeeeeee")
                        textStyle.fontSize: FontSize.PointValue
                        textStyle.fontSizeValue: 6.0
                    }
                }
            }
            Container {

                layoutProperties: StackLayoutProperties {
                    spaceQuota: 1.0

                }
                leftPadding: 10.0
                rightPadding: 10.0

                Container {
                    horizontalAlignment: HorizontalAlignment.Fill

                    layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight
                    
                    }
                    Container {
                        layoutProperties: StackLayoutProperties {
                            spaceQuota: 1.0

                        }
                        Label {
                            id: titleLabel
                            text: "Recording title"
                            textStyle.fontSizeValue: 8.0
                            textStyle.fontSize: FontSize.PointValue
                            verticalAlignment: VerticalAlignment.Center
                            textStyle.color: Color.White

                        }

                    }
                    
                    Container {
                        verticalAlignment: VerticalAlignment.Center
                        
                        Label {
                            id: folderLabel
                            text: "Default d ljsdk jlsj ldsjl djls djlsjd lsj lkdjskl jdls jdlsj lkd "
                            textStyle.fontSizeValue: 6.0
                            textStyle.fontSize: FontSize.PointValue
                            verticalAlignment: VerticalAlignment.Center
                            textStyle.color: Color.LightGray
                            maxWidth: 150.0
                        }
                    
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
                            text: "Recording description"
                            textStyle.fontSizeValue: 7.0
                            textStyle.fontSize: FontSize.PointValue
                            verticalAlignment: VerticalAlignment.Center
                            textStyle.color: Color.White
                        }

                    }
                    Container {
                        verticalAlignment: VerticalAlignment.Center

                        Label {
                            id: durationLabel
                            text: "00:00"
                            textStyle.fontSizeValue: 6.0
                            textStyle.fontSize: FontSize.PointValue
                            verticalAlignment: VerticalAlignment.Center
                            textStyle.color: Color.LightGray
                        }

                    }
                }
                Container {
                    horizontalAlignment: HorizontalAlignment.Fill

                    layout: StackLayout {
                        orientation: LayoutOrientation.LeftToRight

                    }
                    Container {
                        layoutProperties: StackLayoutProperties {
                            spaceQuota: 1.0

                        }
                        Label {
                            id: dateLabel
                            text: "17 Sept, 10:00 am"
                            textStyle.fontSize: FontSize.PointValue
                            textStyle.fontSizeValue: 6.0
                            textStyle.textAlign: TextAlign.Left
                            horizontalAlignment: HorizontalAlignment.Left
                            textStyle.color: Color.LightGray
                        }
                    }
                    Container {
                        horizontalAlignment: HorizontalAlignment.Right
                        Label {
                            id: sizeLabel
                            text: "10kb"
                            textStyle.fontSize: FontSize.PointValue
                            textStyle.fontSizeValue: 6.0
                            textStyle.textAlign: TextAlign.Left
                            horizontalAlignment: HorizontalAlignment.Left
                            textStyle.color: Color.LightGray
                        }
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