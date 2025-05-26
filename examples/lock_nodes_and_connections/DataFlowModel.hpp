#include <QtNodes/DataFlowGraphModel>
#include <QtNodes/Definitions>

using QtNodes::ConnectionId;
using QtNodes::DataFlowGraphModel;
using QtNodes::NodeDelegateModelRegistry;
using QtNodes::NodeFlag;
using QtNodes::NodeFlags;
using QtNodes::NodeId;

class DataFlowModel : public DataFlowGraphModel
{
public:
    DataFlowModel(std::shared_ptr<NodeDelegateModelRegistry> registry)
        : DataFlowGraphModel(std::move(registry))
        , _detachPossible{true}
        , _nodesLocked{false}
    {}

    bool detachPossible(ConnectionId const) const override { return _detachPossible; }

    void setDetachPossible(bool d = true) { _detachPossible = d; }

    //----

    NodeFlags nodeFlags(NodeId nodeId) const override
    {
        auto basicFlags = DataFlowGraphModel::nodeFlags(nodeId);

        if (_nodesLocked)
            basicFlags |= NodeFlag::Locked;

        return basicFlags;
    }

    void setNodesLocked(bool b = true)
    {
        _nodesLocked = b;

        for (NodeId nodeId : allNodeIds()) {
            Q_EMIT nodeFlagsUpdated(nodeId);
        }
    }

    
    /// @brief 是否可连接
    /// @param connectionId  连接id
    /// @return
    bool connectionPossible(ConnectionId const connectionId) const override {
        // 获取端口数据类型
        auto getDataType = [&](PortType const portType) {
            return portData(getNodeId(portType, connectionId),
                            portType,
                            getPortIndex(portType, connectionId),
                            PortRole::DataType)
                .value<NodeDataType>();
        };

        // 获取连接策略
        auto portVacant = [&](PortType const portType) {
            NodeId const nodeId = getNodeId(portType, connectionId);
            PortIndex const portIndex = getPortIndex(portType, connectionId);
            auto const connected = connections(nodeId, portType, portIndex);

            auto policy = portData(nodeId, portType, portIndex, PortRole::ConnectionPolicyRole)
                              .value<ConnectionPolicy>();

            return connected.empty() || (policy == ConnectionPolicy::Many);
        };

        // TODO: 1. 环路不可链接
        // TODO: 2. 输入输出类型不可链接
        // TODO: 3. 链接策略判定
        //std::unique_ptr<NodeDelegateModel> model = _models[]
        QString outId = getDataType(PortType::Out).id;
        QString inId = getDataType(PortType::In).id;
        auto outPort = portVacant(PortType::Out);
        auto inPort = portVacant(PortType::In);
        return outId == inId && outPort && inPort;
    }

private:
    bool _detachPossible;

    bool _nodesLocked;
};
