import bb.cascades 1.0

Container {

    horizontalAlignment: HorizontalAlignment.Fill
    verticalAlignment: VerticalAlignment.Fill
    //    preferredWidth: 310.0
    //    preferredHeight: 211.0
    //    maxWidth: 310.0
    //    maxHeight: 211.0
    background: Color.Black
    layoutProperties: StackLayoutProperties {
        spaceQuota: 1.0

    }
    layout: DockLayout {

    }

    Container {
        verticalAlignment: VerticalAlignment.Center
        horizontalAlignment: HorizontalAlignment.Center

        background: Color.Black
        topPadding: 20.0
        bottomPadding: 20.0
        ImageView {
            id: statusImage
            objectName: "statusImage"
            scalingMethod: ScalingMethod.AspectFit
            imageSource: "asset:///images/icon_big.png"
            horizontalAlignment: HorizontalAlignment.Center
            verticalAlignment: VerticalAlignment.Center

        }
    }
    Container {
        layout: StackLayout {
            orientation: LayoutOrientation.LeftToRight

        }
        horizontalAlignment: HorizontalAlignment.Fill

        leftPadding: 10.0
        rightPadding: 10.0
        topPadding: 10.0
        bottomPadding: 10.0
        verticalAlignment: VerticalAlignment.Bottom
        Container {
            horizontalAlignment: HorizontalAlignment.Fill
            verticalAlignment: VerticalAlignment.Top

            layoutProperties: StackLayoutProperties {
                spaceQuota: 1.0

            }
            Label {
                id: titleLabel
                objectName: "titleLabel"
                text: "Ready"
                textStyle.fontSize: FontSize.PointValue
                textStyle.fontSizeValue: 7.0
                textStyle.color: Color.White
                horizontalAlignment: HorizontalAlignment.Left
                verticalAlignment: VerticalAlignment.Center
            }

        }
        Container {
            horizontalAlignment: HorizontalAlignment.Fill
            verticalAlignment: VerticalAlignment.Bottom

            Label {
                id: statusLabel
                objectName: "statusLabel"
                text: "00:00"
                textStyle.fontSize: FontSize.PointValue
                textStyle.fontSizeValue: 7.0
                textStyle.color: Color.White
                horizontalAlignment: HorizontalAlignment.Center
                verticalAlignment: VerticalAlignment.Center
            }

        }
    }
}