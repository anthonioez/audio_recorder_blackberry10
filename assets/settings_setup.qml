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
            verticalAlignment: VerticalAlignment.Center

            Container {
                id: titleContainer
                horizontalAlignment: HorizontalAlignment.Fill
                topPadding: 20.0
                bottomPadding: 10.0
                leftPadding: 30.0
                rightPadding: 30.0
                objectName: "titleContainer"
                Label {
                    id: titleLabel
                    horizontalAlignment: HorizontalAlignment.Left
                    text: "Setup Password "
                    textStyle.fontSize: FontSize.PointValue
                    textStyle.fontSizeValue: 9.0
                    textStyle.color: Color.White
                    textStyle.fontWeight: FontWeight.Bold
                    objectName: "titleLabel"
                }
            }

            Container {
                ScrollView {
                    layoutProperties: StackLayoutProperties {
                        spaceQuota: 1.0

                    }

                    Container {
                        topPadding: 20.0
                        leftPadding: 30.0
                        rightPadding: 30.0
                        bottomPadding: 20.0
                        Container {
                            horizontalAlignment: HorizontalAlignment.Left
                            Label {

                                text: "A password is required if you want to protect your recordings in a secure folder."

                                objectName: "titleLabel"
                                textStyle.fontSize: FontSize.PointValue
                                textStyle.fontSizeValue: 8.0

                                horizontalAlignment: HorizontalAlignment.Left
                                multiline: true
                                textStyle.color: Color.White
                            }
                        }
                        Container {
                            topPadding: 30.0
                            bottomPadding: 0.0
                            horizontalAlignment: HorizontalAlignment.Center

                            TextField {
                                id: passwordText
                                hintText: "Choose your password"
                                inputMode: TextFieldInputMode.Password
                                objectName: "passwordText"

                            }
                        }
                        Container {
                            topPadding: 30.0

                            horizontalAlignment: HorizontalAlignment.Center

                            TextField {
                                id: passwordConfirmText
                                hintText: "Confirm your password"
                                inputMode: TextFieldInputMode.Password
                                objectName: "passwordConfirmText"

                            }
                        }
                        Container {
                            topPadding: 50.0
                            Label {
                                text: "Password Recovery"
                                textStyle.color: Color.White
                                textStyle.fontSize: FontSize.PointValue
                                textStyle.fontSizeValue: 8.0

                            }

                        }

                        Container {
                            topPadding: 30.0

                            horizontalAlignment: HorizontalAlignment.Center

                            TextField {
                                id: recoveryQuestionText
                                hintText: "Recovery question"
                                objectName: "recoveryQuestionText"

                            }
                        }

                        Container {
                            topPadding: 30.0

                            horizontalAlignment: HorizontalAlignment.Center

                            TextField {
                                id: recoveryAnswerText
                                hintText: "Recovery answer"
                                objectName: "recoveryAnswerText"
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
                    verticalAlignment: VerticalAlignment.Center
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

                    horizontalAlignment: HorizontalAlignment.Center
                    verticalAlignment: VerticalAlignment.Center

                }
                Container {
                    verticalAlignment: VerticalAlignment.Center
                    ImageView {
                        id: saveImage

                        objectName: "saveImage"
                        imageSource: "asset:///images/yes.png"
                        horizontalAlignment: HorizontalAlignment.Center
                    }
                }
            }
        }
    }
}