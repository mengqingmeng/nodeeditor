#include "StyleCollection.hpp"

using QtNodes::ConnectionStyle;
using QtNodes::GraphicsViewStyle;
using QtNodes::NodeStyle;
using QtNodes::StyleCollection;

NodeStyle const &StyleCollection::nodeStyle()
{
    return instance()._nodeStyle;
}

ConnectionStyle const &StyleCollection::connectionStyle()
{
    return instance()._connectionStyle;
}

GraphicsViewStyle const &StyleCollection::flowViewStyle()
{
    return instance()._flowViewStyle;
}

void StyleCollection::setNodeStyle(NodeStyle nodeStyle)
{
    //instance()._nodeStyle = nodeStyle;
    mergeNodeStyle(nodeStyle);
}

void StyleCollection::setConnectionStyle(ConnectionStyle connectionStyle)
{
    instance()._connectionStyle = connectionStyle;
}

void StyleCollection::setGraphicsViewStyle(GraphicsViewStyle flowViewStyle)
{
    instance()._flowViewStyle = flowViewStyle;
}

StyleCollection &StyleCollection::instance()
{
    static StyleCollection collection;

    return collection;
}

void StyleCollection::mergeConnectionStyle(const ConnectionStyle &srcStyle) {
    if (srcStyle.constructionColor().isValid()) {
    }
}

void StyleCollection::mergeNodeStyle(const NodeStyle& srcStyle) {
    if (srcStyle.NormalBoundaryColor.isValid()) {
        instance()._nodeStyle.NormalBoundaryColor = srcStyle.NormalBoundaryColor;
    }

    if (srcStyle.SelectedBoundaryColor.isValid()) {
        instance()._nodeStyle.SelectedBoundaryColor = srcStyle.SelectedBoundaryColor;
    }

    if (srcStyle.GradientColor0.isValid()) {
        instance()._nodeStyle.GradientColor0 = srcStyle.GradientColor0;
    }

    if (srcStyle.GradientColor1.isValid()) {
        instance()._nodeStyle.GradientColor1 = srcStyle.GradientColor1;
    }

    if (srcStyle.GradientColor2.isValid()) {
        instance()._nodeStyle.GradientColor2 = srcStyle.GradientColor2;
    }

    if (srcStyle.GradientColor3.isValid()) {
        instance()._nodeStyle.GradientColor3 = srcStyle.GradientColor3;
    }

    if (srcStyle.ShadowColor.isValid()) {
        instance()._nodeStyle.ShadowColor = srcStyle.ShadowColor;
    }

    if (srcStyle.FontColor.isValid()) {
        instance()._nodeStyle.FontColor = srcStyle.FontColor;
    }

    if (srcStyle.FontColorFaded.isValid()) {
        instance()._nodeStyle.FontColorFaded = srcStyle.FontColorFaded;
    }

    if (srcStyle.ConnectionPointColor.isValid()) {
        instance()._nodeStyle.ConnectionPointColor = srcStyle.ConnectionPointColor;
    }
    
    if (srcStyle.FilledConnectionPointColor.isValid()) {
        instance()._nodeStyle.FilledConnectionPointColor = srcStyle.FilledConnectionPointColor;
    }

    if (srcStyle.WarningColor.isValid()) {
        instance()._nodeStyle.WarningColor = srcStyle.WarningColor;
    }

    if (srcStyle.ErrorColor.isValid()) {
        instance()._nodeStyle.ErrorColor = srcStyle.ErrorColor;
    }

    if (srcStyle.PenWidth > 0.0f)
        instance()._nodeStyle.PenWidth = srcStyle.PenWidth;

    if (srcStyle.HoveredPenWidth>0.0f)
        instance()._nodeStyle.HoveredPenWidth = srcStyle.HoveredPenWidth;

    if (srcStyle.ConnectionPointDiameter > 0.0f)
        instance()._nodeStyle.ConnectionPointDiameter = srcStyle.ConnectionPointDiameter;

    if (srcStyle.Opacity > 0.0f)
        instance()._nodeStyle.Opacity = srcStyle.Opacity;

    if (srcStyle.NodeMinWidth > 0.0f)
        instance()._nodeStyle.NodeMinWidth = srcStyle.NodeMinWidth;
}

void StyleCollection::mergeGraphicsViewStyle(const GraphicsViewStyle& srcStyle) {

}
