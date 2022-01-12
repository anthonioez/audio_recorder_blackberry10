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
            verticalAlignment: VerticalAlignment.Fill

            layoutProperties: StackLayoutProperties {
                spaceQuota: 1.0

            }

            Container {
                id: titleContainer
                horizontalAlignment: HorizontalAlignment.Fill
                topPadding: 20.0
                bottomPadding: 10.0
                leftPadding: 30.0
                rightPadding: 30.0
                objectName: "titleContainer"
                verticalAlignment: VerticalAlignment.Top
                Label {
                    id: titleLabel
                    horizontalAlignment: HorizontalAlignment.Left
                    text: "Login"
                    textStyle.fontSize: FontSize.PointValue
                    textStyle.fontSizeValue: 9.0
                    textStyle.color: Color.White
                    textStyle.fontWeight: FontWeight.Bold
                    objectName: "titleLabel"
                }
            }
            ScrollView {
                scrollViewProperties.scrollMode: ScrollMode.Vertical

                layoutProperties: StackLayoutProperties {
                    spaceQuota: 1.0

                }
                horizontalAlignment: HorizontalAlignment.Fill
                verticalAlignment: VerticalAlignment.Fill
                Container {
                    horizontalAlignment: HorizontalAlignment.Left

                    verticalAlignment: VerticalAlignment.Center
                    layout: DockLayout {

                    }

                    topPadding: 30.0
                    Container {
                        id: loginContainer
                        leftPadding: 30.0
                        rightPadding: 30.0
                        objectName: "loginContainer"
                        visible: true
                        Container {

                            horizontalAlignment: HorizontalAlignment.Left

                            Label {

                                text: "Welcome!"

                                objectName: "titleLabel"
                                textStyle.fontSize: FontSize.PointValue
                                textStyle.fontSizeValue: 8.0

                                horizontalAlignment: HorizontalAlignment.Left
                                textStyle.color: Color.White

                            }
                        }
                        Container {
                            topPadding: 20.0
                            bottomPadding: 20.0
                            horizontalAlignment: HorizontalAlignment.Center

                            TextField {
                                id: passwordText
                                hintText: "Enter your login password"
                                inputMode: TextFieldInputMode.Password
                                objectName: "passwordText"
                                textStyle.fontSize: FontSize.PointValue
                                textStyle.fontSizeValue: 8.0

                            }
                        }
                        Container {
                            topPadding: 20.0
                            bottomPadding: 20.0
                            horizontalAlignment: HorizontalAlignment.Fill

                            layout: StackLayout {
                                orientation: LayoutOrientation.LeftToRight

                            }
                            Container {

                                layoutProperties: StackLayoutProperties {
                                    spaceQuota: 1.0

                                }

                                horizontalAlignment: HorizontalAlignment.Fill

                                rightPadding: 2.0
                                Button {
                                    id: loginButton
                                    text: "Login"
                                    horizontalAlignment: HorizontalAlignment.Fill

                                    objectName: "loginButton"
                                    visible: true
                                }
                            }
                            Container {

                                layoutProperties: StackLayoutProperties {
                                    spaceQuota: 1.0

                                }

                                horizontalAlignment: HorizontalAlignment.Fill
                                visible: true

                                Button {
                                    id: forgotButton
                                    text: "Forgot Password?"
                                    horizontalAlignment: HorizontalAlignment.Fill

                                    objectName: "forgotButton"
                                }
                            }

                        }
                    }

                    Container {
                        id: recoveryContainer

                        visible: false
                        objectName: "recoveryContainer"
                        leftPadding: 30.0
                        rightPadding: 30.0
                        Container {
                            Label {
                                text: "Security question:"
                                textStyle.fontSize: FontSize.PointValue
                                textStyle.fontSizeValue: 8.0
                                textStyle.color: Color.White

                            }

                        }
                        Container {

                            horizontalAlignment: HorizontalAlignment.Left

                            bottomPadding: 20.0
                            topPadding: 10.0
                            Label {
                                id: questionLabel
                                text: "sample"
                                objectName: "questionLabel"
                                multiline: true
                                textStyle.fontSize: FontSize.PointValue
                                textStyle.fontSizeValue: 8.0
                                textStyle.color: Color.White

                            }

                        }
                        Container {
                            topPadding: 20.0
                            bottomPadding: 20.0
                            horizontalAlignment: HorizontalAlignment.Center

                            TextField {
                                id: answerText
                                hintText: "Enter your security answer"
                                objectName: "answerText"
                                textStyle.fontSize: FontSize.PointValue
                                textStyle.fontSizeValue: 8.0

                            }
                        }
                        Container {
                            topPadding: 20.0
                            bottomPadding: 20.0
                            horizontalAlignment: HorizontalAlignment.Fill

                            layout: StackLayout {
                                orientation: LayoutOrientation.LeftToRight

                            }
                            Container {

                                layoutProperties: StackLayoutProperties {
                                    spaceQuota: 1.0

                                }

                                horizontalAlignment: HorizontalAlignment.Fill

                                rightPadding: 2.0
                                Button {
                                    id: recoverButton
                                    text: "Recover Password"
                                    horizontalAlignment: HorizontalAlignment.Fill

                                    objectName: "recoverButton"
                                    visible: true
                                }
                            }
                            Container {
                                id: forgotContainer
                                layoutProperties: StackLayoutProperties {
                                    spaceQuota: 1.0

                                }

                                horizontalAlignment: HorizontalAlignment.Fill
                                visible: true
                                objectName: "forgotContainer"
                                leftPadding: 2.0
                                Button {
                                    id: cancelButton
                                    text: "Cancel"
                                    horizontalAlignment: HorizontalAlignment.Fill

                                    objectName: "cancelButton"
                                }
                            }

                        }
                    }

                }
            }
        }
    }
}
