#include "NodeDelegateModel.hpp"

#include "StyleCollection.hpp"

namespace QtNodes {

NodeDelegateModel::NodeDelegateModel()
    : _nodeStyle(StyleCollection::nodeStyle())
{
    // Derived classes can initialize specific style here
}

NodeDelegateModel::NodeDelegateModel(const QString &name,
                                     const QString &caption,
                                     const QString &category,
                                     unsigned int inCount,
                                     unsigned int outCount)
    : _caption(caption)
    , _name(name)
    , _category(category)
    , _inCount(inCount)
    , _outCount(outCount)
{}

QJsonObject NodeDelegateModel::save() const
{
    QJsonObject modelJson;

    modelJson["model-name"] = name();

    return modelJson;
}

void NodeDelegateModel::load(QJsonObject const &)
{
    //
}

ConnectionPolicy NodeDelegateModel::portConnectionPolicy(PortType portType, PortIndex) const
{
    auto result = ConnectionPolicy::One;
    switch (portType) {
    case PortType::In:
        result = ConnectionPolicy::Many;
        break;
    case PortType::Out:
        result = ConnectionPolicy::Many;
        break;
    case PortType::None:
        break;
    }

    return result;
}

NodeStyle const &NodeDelegateModel::nodeStyle() const
{
    return _nodeStyle;
}

void NodeDelegateModel::setNodeStyle(NodeStyle const &style)
{
    _nodeStyle = style;
}

unsigned int NodeDelegateModel::nPorts(PortType portType) const
 {
    if (portType == PortType::In) {
        return _inCount;
    } else if (portType == PortType::Out) {
        return _outCount;
    }
    return 0;
}

QString NodeDelegateModel::caption() const {
    return _caption;
}

QString NodeDelegateModel::name() const
{
    return _name;
}

QString NodeDelegateModel::category() const
{
    return _category;
}

void NodeDelegateModel::setSvgToLabel(QLabel *label,
                                      const QString &svgPath,
                                      const int size,
                                      int sampleFactor)
{
    if (!label || svgPath.isEmpty())
        return;

    //QSvgRenderer renderer(svgPath);
    //if (!renderer.isValid())
    //    return;

    // // 计算目标尺寸（考虑HiDPI）
    //qreal dpr = label->devicePixelRatioF();
    //qreal targetSize = dpr * size;
    //// 创建透明背景的Pixmap
    //QPixmap pixmap(targetSize, targetSize);
    //pixmap.fill(Qt::transparent); // 关键：透明背景避免白边
    //// 使用QPainter进行抗锯齿渲染
    //QPainter painter(&pixmap);
    //painter.setRenderHint(QPainter::Antialiasing, true);
    //painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    //painter.setRenderHint(QPainter::TextAntialiasing, true);

    //// 渲染SVG到Pixmap
    //renderer.render(&painter, QRect(0, 0, targetSize, targetSize));
    //painter.end();
    //// 设置设备像素比
    //pixmap.setDevicePixelRatio(dpr);
    //label->setPixmap(pixmap);

    QSvgRenderer renderer(svgPath);
    if (!renderer.isValid())
        return;
    qreal dpr = label->devicePixelRatioF();
    QSize baseSize = QSize(size,size) * dpr;
    QSize superSampledSize = baseSize * sampleFactor;
    // 创建超采样Pixmap
    QPixmap superPixmap(superSampledSize);
    superPixmap.fill(Qt::transparent);

    // 大尺寸渲染
    QPainter spPainter(&superPixmap);
    spPainter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    renderer.render(&spPainter, QRect(QPoint(0, 0), superSampledSize));
    spPainter.end();
    // 高质量缩小
    QPixmap finalPixmap = superPixmap.scaled(baseSize,
                                             Qt::KeepAspectRatio,
                                             Qt::SmoothTransformation);

    finalPixmap.setDevicePixelRatio(dpr);
    label->setPixmap(finalPixmap);
}

} // namespace QtNodes
