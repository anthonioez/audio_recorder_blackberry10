import bb.cascades 1.0

Page {
    signal openItem(variant object)
    signal editItem(variant object)
    signal defaultItem(variant object)
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
                    text: "Folders"
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
                        status: "No folders selected"                        
                    }

                    onSelectionChanged: {
                        if (selectionList().length > 1) 
                        {
                            multiSelectHandler.status = selectionList().length + " recordings selected";
                        } else if (selectionList().length == 1) {
                            multiSelectHandler.status = "1 folder selected";
                        } else {
                            multiSelectHandler.status = "No folder selected";
                        }
                    }
                    listItemComponents: [
                        ListItemComponent {
                            type: "item"
                            RecorderFolder {
                                id: itemRoot
                                title: ListItemData.title
                                desc: ListItemData.desc
                                info: ListItemData.info
                                hilite: (itemRoot.ListItem.active | itemRoot.ListItem.selected) ? true : false

                                contextActions: [
                                    ActionSet { 
                                        title: ListItemData.text
                                        subtitle: ListItemData.date
                                        ActionItem {
                                            title: "Open"
                                            imageSource: "asset:///images/open.png"
                                            onTriggered: {
                                                itemRoot.ListItem.view.openListItem(itemRoot.ListItem.indexPath);
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
                                            title: "Set as recording folder"
                                            imageSource: "asset:///images/favorite.png"
                                            enabled: ListItemData.current ? false : true
                                            onTriggered: {
                                                itemRoot.ListItem.view.defaultListItem(itemRoot.ListItem.indexPath);
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

                    function openListItem(indexPath) {
                        playItem(indexPath);
                    }

                    function editListItem(indexPath) {
                        editItem(indexPath);
                    }
                    
                    function defaultListItem(indexPath) {
                        defaultItem(indexPath);
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

                    
                }
                Container {
                    ImageView {
                        id: addImage
                        objectName: "addImage"
                        imageSource: "asset:///images/add.png"
                        horizontalAlignment: HorizontalAlignment.Right
                    }
                }
            }
        }
    }
}