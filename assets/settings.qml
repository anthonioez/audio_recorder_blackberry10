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

            verticalAlignment: VerticalAlignment.Fill
            layoutProperties: StackLayoutProperties {
                spaceQuota: 1.0

            }

            Container {
                layoutProperties: StackLayoutProperties {
                    spaceQuota: 1.0

                }

                Container {
                    id: titleContainer
                    objectName: "titleContainer"
                    verticalAlignment: VerticalAlignment.Center
                    horizontalAlignment: HorizontalAlignment.Fill

                    topPadding: 20.0
                    leftPadding: 20.0
                    rightPadding: 20.0
                    Label {
                        text: "Settings"
                        textStyle.color: Color.White
                        textStyle.fontSize: FontSize.PointValue
                        textStyle.fontSizeValue: 8.0
                        textStyle.fontWeight: FontWeight.Bold
                        horizontalAlignment: HorizontalAlignment.Left
                    }
                }
                ScrollView {
                    layoutProperties: StackLayoutProperties {
                        spaceQuota: 1.0

                    }
                    scrollViewProperties.scrollMode: ScrollMode.Vertical
                    Container {
                        bottomPadding: 30.0

                        leftPadding: 20.0
                        rightPadding: 20.0
                        Container {
                            horizontalAlignment: HorizontalAlignment.Fill

                            topPadding: 20.0
                            Container {
                                horizontalAlignment: HorizontalAlignment.Fill

                                Label {
                                    text: "Recording"
                                    textStyle.fontSize: FontSize.PointValue
                                    textStyle.fontSizeValue: 8.0
                                    textStyle.color: Color.White
                                    textStyle.fontStyle: FontStyle.Italic
                                }
                            }
                            Container {
                                horizontalAlignment: HorizontalAlignment.Fill

                                topPadding: 10.0
                                DropDown {
                                    id: formatDrop
                                    title: "Format"
                                    horizontalAlignment: HorizontalAlignment.Fill
                                    selectedIndex: 0
                                    objectName: "formatDrop"
                                    Option {
                                        text: "AMR"
                                        description: "Low quality, small file size"
                                    }
                                    Option {
                                        text: "M4A"
                                        description: "Medium quality, average file size"
                                    }
                                    Option {
                                        text: "WAV"
                                        description: "High quality, large file size"
                                    }
                                }
                            }
                            Container {
                                horizontalAlignment: HorizontalAlignment.Fill
                                topPadding: 10.0
                                DropDown {
                                    id: sequenceDrop
                                    title: "Sequence"
                                    horizontalAlignment: HorizontalAlignment.Fill
                                    selectedIndex: 0
                                    objectName: "sequenceDrop"
                                    Option {
                                        text: "Record then pause"
                                    }
                                    Option {
                                        text: "Record then stop"
                                    }
                                }
                            }
                            Container {
                                horizontalAlignment: HorizontalAlignment.Fill
                                topPadding: 10.0
                                DropDown {
                                    id: storeDrop
                                    title: "Store"
                                    horizontalAlignment: HorizontalAlignment.Fill
                                    selectedIndex: 0
                                    objectName: "storeDrop"
                                    Option {
                                        text: "Secure folder (requires password)"
                                        description: "Store recordings within the app"
                                    }
                                    Option {
                                        text: "Device folder"
                                        description: "Device/voice/recorder+"
                                    }
                                    Option {
                                        text: "Media card folder"
                                        description: "Media card/voice/recorder+"
                                    }
                                }
                            }
                        }
                        Container {
                            horizontalAlignment: HorizontalAlignment.Fill
                            visible: true
                            topPadding: 20.0
                            Container {
                                horizontalAlignment: HorizontalAlignment.Fill

                                Label {
                                    text: "Notification"
                                    textStyle.fontSize: FontSize.PointValue
                                    textStyle.fontSizeValue: 8.0
                                    textStyle.color: Color.White
                                    textStyle.fontStyle: FontStyle.Italic
                                }
                            }
                            Container {
                                horizontalAlignment: HorizontalAlignment.Fill
                                topPadding: 10.0

                                DropDown {
                                    id: soundDrop
                                    title: "Sound"
                                    horizontalAlignment: HorizontalAlignment.Fill
                                    selectedIndex: 3
                                    objectName: "soundDrop"
                                    Option {
                                        text: "Off"
                                    }
                                    Option {
                                        text: "On record start only"
                                    }
                                    Option {
                                        text: "On record stop only"
                                    }
                                    Option {
                                        text: "On record start and stop"
                                    }
                                }
                            }
                            Container {
                                horizontalAlignment: HorizontalAlignment.Fill
                                topPadding: 10.0

                                DropDown {
                                    id: vibrateDrop
                                    title: "Vibrate"
                                    horizontalAlignment: HorizontalAlignment.Fill
                                    selectedIndex: 3
                                    objectName: "vibrateDrop"
                                    Option {
                                        text: "Off"
                                    }
                                    Option {
                                        text: "On record start only"
                                    }
                                    Option {
                                        text: "On record stop only"
                                    }
                                    Option {
                                        text: "On record start and stop"
                                    }
                                }
                            }
                            Container {
                                horizontalAlignment: HorizontalAlignment.Fill
                                topPadding: 10.0
                                DropDown {
                                    id: ledDrop
                                    title: "LED"
                                    horizontalAlignment: HorizontalAlignment.Fill
                                    selectedIndex: 0
                                    objectName: "ledDrop"
                                    Option {
                                        text: "Off"
                                    }
                                    Option {
                                        text: "Red"
                                    }
                                    Option {
                                        text: "Green"
                                    }
                                    Option {
                                        text: "Blue"
                                    }
                                    Option {
                                        text: "Yellow"
                                    }
                                    Option {
                                        text: "Cyan"
                                    }
                                    Option {
                                        text: "Magenta"
                                    }
                                    Option {
                                        text: "White"
                                    }
                                }
                            }
                        }
                        Container {
                            horizontalAlignment: HorizontalAlignment.Fill
                            topPadding: 20.0

                            Container {

                                Label {
                                    text: "Sorting"
                                    textStyle.color: Color.White
                                    textStyle.fontStyle: FontStyle.Italic
                                    textStyle.fontSize: FontSize.PointValue
                                    textStyle.fontSizeValue: 8.0

                                }
                            }
                            Container {
                                horizontalAlignment: HorizontalAlignment.Fill

                                topPadding: 10.0
                                DropDown {
                                    id: sortDrop
                                    title: "Sort entries"
                                    horizontalAlignment: HorizontalAlignment.Fill
                                    selectedIndex: 0
                                    objectName: "sortDrop"
                                    Option {
                                        text: "Title"
                                    }
                                    Option {
                                        text: "Description"
                                    }
                                    Option {
                                        text: "Duration"
                                    }
                                    Option {
                                        text: "File size"
                                    }
                                    Option {
                                        text: "Recording time"
                                    }
                                    Option {
                                        text: "Record ID"
                                    }
                                    Option {
                                        text: "Folder ID"
                                    }
                                }
                            }

                            Container {
                                horizontalAlignment: HorizontalAlignment.Fill

                                topPadding: 10.0
                                DropDown {
                                    id: orderDrop
                                    title: "Order entries"
                                    horizontalAlignment: HorizontalAlignment.Fill
                                    selectedIndex: 0
                                    objectName: "orderDrop"
                                    Option {
                                        text: "Descending"
                                    }
                                    Option {
                                        text: "Ascending"
                                    }
                                }
                            }                            
                        }
                        
                        Container {
                            horizontalAlignment: HorizontalAlignment.Fill

                            topPadding: 20.0

                            Container {
                                horizontalAlignment: HorizontalAlignment.Fill

                                Label {
                                    text: "Extras"
                                    textStyle.fontSize: FontSize.PointValue
                                    textStyle.fontSizeValue: 8.0
                                    textStyle.color: Color.White
                                    textStyle.fontStyle: FontStyle.Italic
                                }
                            }
                            Container {
                                horizontalAlignment: HorizontalAlignment.Fill

                                topPadding: 10.0
                                DropDown {
                                    id: playDrop
                                    title: "Audio player"
                                    horizontalAlignment: HorizontalAlignment.Fill
                                    selectedIndex: 0
                                    objectName: "playerDrop"
                                    Option {
                                        text: "Internal"
                                    }
                                    Option {
                                        text: "BlackBerry"
                                    }
                                }
                            }
                            Container {
                                horizontalAlignment: HorizontalAlignment.Fill
                                
                                topPadding: 10.0
                                DropDown {
                                    id: speedDrop
                                    title: "Enable speed control"
                                    horizontalAlignment: HorizontalAlignment.Fill
                                    selectedIndex: 0
                                    objectName: "speedDrop"
                                    Option {
                                        text: "No"
                                    }
                                    Option {
                                        text: "Yes"
                                    }
                                }
                            }
                            Container {
                                horizontalAlignment: HorizontalAlignment.Fill

                                topPadding: 10.0
                                DropDown {
                                    id: filenameDrop
                                    title: "Prompt for details"
                                    horizontalAlignment: HorizontalAlignment.Fill
                                    selectedIndex: 1
                                    objectName: "saveDrop"
                                    Option {
                                        text: "No"
                                    }
                                    Option {
                                        text: "Yes"
                                    }
                                }
                            }
                            Container {
                                horizontalAlignment: HorizontalAlignment.Fill
                                topPadding: 10.0
                                DropDown {
                                    id: cancelDrop
                                    title: "Prompt on cancel"
                                    horizontalAlignment: HorizontalAlignment.Fill
                                    selectedIndex: 1
                                    objectName: "cancelDrop"
                                    Option {
                                        text: "No"
                                    }
                                    Option {
                                        text: "Yes"
                                    }
                                }
                            }
                        }

                        Container {
                            horizontalAlignment: HorizontalAlignment.Fill

                            topPadding: 20.0

                            Container {
                                horizontalAlignment: HorizontalAlignment.Fill

                                Label {
                                    text: "Security"
                                    textStyle.fontSize: FontSize.PointValue
                                    textStyle.fontSizeValue: 8.0
                                    textStyle.color: Color.White
                                    textStyle.fontStyle: FontStyle.Italic
                                }
                            }
                            Container {
                                horizontalAlignment: HorizontalAlignment.Fill
                                topPadding: 10.0
                                DropDown {
                                    id: passwordDrop
                                    title: "Use password"
                                    horizontalAlignment: HorizontalAlignment.Fill
                                    selectedIndex: 0
                                    objectName: "passwordDrop"
                                    Option {
                                        text: "No"
                                    }
                                    Option {
                                        text: "Yes"
                                    }
                                }
                            }
                            Container {
                                horizontalAlignment: HorizontalAlignment.Fill
                                topPadding: 10.0
                                Button {
                                    id: passwordButton
                                    objectName: "passwordButton"
                                    text: "Setup Password"
                                    horizontalAlignment: HorizontalAlignment.Fill

                                }
                            }

                            Container {
                                horizontalAlignment: HorizontalAlignment.Fill
                                topPadding: 10.0
                                Button {
                                    id: recoveryButton
                                    objectName: "recoveryButton"
                                    text: "Password Recovery"
                                    horizontalAlignment: HorizontalAlignment.Fill
                                }
                            }

                        }
                        Container {
                            id: uiContainer
                            objectName: "uiContainer"
                            horizontalAlignment: HorizontalAlignment.Fill
                            
                            topPadding: 20.0
                            
                            Container {
                                horizontalAlignment: HorizontalAlignment.Fill
                                
                                Label {
                                    text: "Appearance"
                                    textStyle.fontSize: FontSize.PointValue
                                    textStyle.fontSizeValue: 8.0
                                    textStyle.color: Color.White
                                    textStyle.fontStyle: FontStyle.Italic
                                }
                            }
                            Container {
                                horizontalAlignment: HorizontalAlignment.Fill
                                topPadding: 10.0
                                DropDown {
                                    id: uiDrop
                                    title: "User interface"
                                    horizontalAlignment: HorizontalAlignment.Fill
                                    selectedIndex: 0
                                    objectName: "uiDrop"
                                    Option {
                                        text: "Cascades"
                                    }
                                    Option {
                                        text: "Miciniti+"
                                    }
                                }
                            }
                            
                            Container {
                                horizontalAlignment: HorizontalAlignment.Fill
                                topPadding: 10.0
                                
                                DropDown {
                                    id: themesDrop
                                    title: "Theme"
                                    horizontalAlignment: HorizontalAlignment.Fill
                                    selectedIndex: 0
                                    objectName: "themesDrop"
                                    Option {
                                        text: "Black"
                                    }
                                    Option {
                                        text: "Red"
                                    }
                                    Option {
                                        text: "Green"
                                    }
                                    Option {
                                        text: "Blue"
                                    }
                                    Option {
                                        text: "Magenta"
                                    }
                                    Option {
                                        text: "Yellow"
                                    }
                                    Option {
                                        text: "Cyan"
                                    }
                                
                                }
                            }
                        }                        
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
                        id: cancelImage
                        objectName: "cancelImage"
                        imageSource: "asset:///images/no.png"
                        horizontalAlignment: HorizontalAlignment.Left
                    }
                }
                Container {
                    layoutProperties: StackLayoutProperties {
                        spaceQuota: 1.0
                    }

                }
                Container {
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