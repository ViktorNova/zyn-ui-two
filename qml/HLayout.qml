import QtQuick 2.0

Item {
    id: layout

    onChildrenChanged: performLayout()
    onWidthChanged: performLayout()
    onHeightChanged: performLayout()
    onXChanged: performLayout()
    onYChanged: performLayout()
    
    property variant weights: [1.0]

    function performLayout() {
        var currentX = 0
        var N = layout.children.length
        
        var iWeights = weights;
        if(iWeights.length != N) {
            iWeights = []
            for (var i = 0; i < N; ++i) {
                iWeights.push(1.0/N)
            }
        }

        for (var i = 0; i < N; ++i) {
            var obj = layout.children[i]
            obj.x      = currentX
            obj.y      = 0
            obj.width  = layout.width*iWeights[i]
            obj.height = layout.height
            currentX  += layout.width*iWeights[i]
        }
    }
}
