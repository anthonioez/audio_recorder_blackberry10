import bb.cascades 1.0

Page {
    signal deviceMoveItem(variant object)
    signal folderMoveItem(variant object)
    signal playItem(variant object)
    signal editItem(variant object)
    signal shareItem(variant object)
    signal deleteItem(variant object)
    signal deleteItems()
    
    actions: [
        MultiSelectActionItem {
            multiSelectHandler: listId.multiSelectHandler
        }
    ]
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
                horizontalAlignment: HorizontalAlignment.Center
                topPadding: 20.0
                bottomPadding: 10.0
                Label {
                    id: titleLabel
                    horizontalAlignment: HorizontalAlignment.Center
                    text: "Recordings"
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
                    objectName: "fileList"
                    multiSelectAction: MultiSelectActionItem {
                    }
                    multiSelectHandler {
                        actions: [
                            DeleteActionItem{
                                title: "Delete"
                                imageSource: "asset:///images/delete.png"
                                onTriggered: {
                                    deleteItems();
                                }
                                
                            }
                        ]
                        status: "No recording selected"                        
                    }

                    onSelectionChanged: {
                        if (selectionList().length > 1) 
                        {
                            multiSelectHandler.status = selectionList().length + " recordings selected";
                        } else if (selectionList().length == 1) {
                            multiSelectHandler.status = "1 recordings selected";
                        } else {
                            multiSelectHandler.status = "No recording selected";
                        }
                    }
                    listItemComponents: [
                        ListItemComponent {
                            type: "item"
                            RecorderFile {
                                id: itemRoot
                                image: ListItemData.icon
                                title: ListItemData.title
                                desc: ListItemData.desc
                                folder: ListItemData.ftitle
                                size: ListItemData.size;
                                duration: ListItemData.duration
                                date: ListItemData.date
                                type: ListItemData.type
                                hilite: (itemRoot.ListItem.active | itemRoot.ListItem.selected) ? true : false

                                contextActions: [
                                    ActionSet { 
                                        title: ListItemData.text
                                        subtitle: ListItemData.date
                                        ActionItem {
                                            title: "Play"
                                            imageSource: "asset:///images/play.png"
                                            onTriggered: {
                                                itemRoot.ListItem.view.playListItem(itemRoot.ListItem.indexPath);
                                            }
                                        }
                                        ActionItem {
                                            title: "Edit"
                                            imageSource: "asset:///images/edit.png"
                                            onTriggered: {
                                                itemRoot.ListItem.view.editListItem(itemRoot.ListItem.indexPath);
                                            }
                                        }
                                        ActionItem {
                                            title: "Move to Device Memory"
                                            imageSource: "asset:///images/move_to_device.png"
                                            enabled: ListItemData.secure
                                            onTriggered: {
                                                itemRoot.ListItem.view.deviceMoveListItem(itemRoot.ListItem.indexPath);
                                            }
                                        }
                                        ActionItem {
                                            title: "Move to another folder"
                                            imageSource: "asset:///images/move_to_folder.png"
                                            onTriggered: {
                                                itemRoot.ListItem.view.folderMoveListItem(itemRoot.ListItem.indexPath);
                                            }
                                        }
                                        ActionItem {
                                            title: "Share"
                                            imageSource: "asset:///images/share.png"
                                            onTriggered: {
                                                itemRoot.ListItem.view.shareListItem(itemRoot.ListItem.indexPath);
                                            }
                                        }
                                        DeleteActionItem {
                                            title: "Delete"
                                            onTriggered: {
                                                itemRoot.ListItem.view.deleteListItem(itemRoot.ListItem.indexPath);
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

                    function playListItem(indexPath) {
                        playItem(indexPath);
                    }

                    function editListItem(indexPath) {
                        editItem(indexPath);
                    }

                    function shareListItem(indexPath) {
                        shareItem(indexPath);
                    }
                    
                    function deviceMoveListItem(indexPath) {
                        deviceMoveItem(indexPath);
                    }
                    
                    function folderMoveListItem(indexPath) {
                        folderMoveItem(indexPath);
                    }
                    
                    function deleteListItem(indexPath) {
                        deleteItem(indexPath);
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
                        id: closeImage
                        objectName: "closeImage"
                        imageSource: "asset:///images/back.png"
                        horizontalAlignment: HorizontalAlignment.Left
                    }
                }
                Container {
                    layoutProperties: StackLayoutProperties {
                        spaceQuota: 1.0
                    }

                    horizontalAlignment: HorizontalAlignment.Center
                    verticalAlignment: VerticalAlignment.Center

                    ImageView {
                        id: cleanImage
                        objectName: "cleanImage"
                        imageSource: "asset:///images/icon.png"
                        horizontalAlignment: HorizontalAlignment.Center
                        verticalAlignment: VerticalAlignment.Center
                        visible: false
                    }
                }
                Container {
                    ImageView {
                        id: clearImage
                        objectName: "clearImage"
                        imageSource: "asset:///images/clear.png"
                        horizontalAlignment: HorizontalAlignment.Right
                    }
                }
            }
        }
    }
}