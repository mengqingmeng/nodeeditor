#include "NodeDelegateModel.hpp"

#include "StyleCollection.hpp"

namespace QtNodes {

NodeDelegateModel::NodeDelegateModel()
    : _nodeStyle(StyleCollection::nodeStyle())
    , _inCount(1)
    , _outCount(1)
{
    // Derived classes can initialize specific style here
}

NodeDelegateModel::NodeDelegateModel(const QString &uniqueName,
                                     const QString &caption,
                                     const QString &category,
                                     const QString &parentUniqueName,
                                     unsigned int inCount,
                                     unsigned int outCount)
    : _caption(caption)
    , _uniqueName(uniqueName)
    , _category(category)
    , _parentUniqueName(parentUniqueName)
    , _inCount(inCount)
    , _outCount(outCount){
}

QJsonObject NodeDelegateModel::save() const
{
    QJsonObject modelJson;

    modelJson["model-name"] = uniqueName();

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

QString NodeDelegateModel::uniqueName() const
{
    return _uniqueName;
}

QString NodeDelegateModel::category() const
{
    return _category;
}

QString NodeDelegateModel::parentUniqueName() const
{
    return _parentUniqueName;
}

QSet<PortTransDataType> NodeDelegateModel::getPortTransTypes(const PortId &portId) {
    return _nodePortTransTypes[portId];
}

void NodeDelegateModel::setPortTransTypes(const PortId &portId,const QSet<PortTransDataType> &transTypes)
{
    for (const PortTransDataType type : transTypes) {
        _nodePortTransTypes[portId].insert(type);
    }
}

} // namespace QtNodes
