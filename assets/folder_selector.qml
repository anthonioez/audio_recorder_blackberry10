import bb.cascades 1.0

Page {
    signal selectItem(variant object) 

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
                bottomPadding: 20.0
                leftPadding: 20.0
                rightPadding: 20.0
                Label {
                    id: titleLabel
                    horizontalAlignment: HorizontalAlignment.Left
                    text: "Select destination folder"
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

                ListView {
                    id: listId
                    objectName: "folderList"
                    listItemComponents: [
                        ListItemComponent {
                            type: "item"
                            RecorderFolder {
                                id: itemRoot
                                title: ListItemData.title
                                desc: ListItemData.desc
                                info: ListItemData.info
                                hilite: itemRoot.ListItem.active ? true : false

                                contextActions: [
                                    ActionSet {
                                        title: ListItemData.text
                                        subtitle: ListItemData.date
                                        ActionItem {
                                            title: "Select"
                                            imageSource: "asset:///images/yes.png"
                                            onTriggered: {
                                                itemRoot.ListItem.view.selectListItem(itemRoot.ListItem.indexPath);
                                            }
                                        }

                                    }
                                ]
                            }
                        }
                    ]

                    function itemType(data, indexPath) {
                        return 'item';
                    }

                    function selectListItem(indexPath) {
                        selectItem(indexPath);
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
                        id: addImage

                        objectName: "addImage"
                        imageSource: "asset:///images/add.png"
                        horizontalAlignment: HorizontalAlignment.Center
                    }
                }
            }
        }
    }
}