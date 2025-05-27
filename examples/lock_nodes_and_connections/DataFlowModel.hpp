#include <QtNodes/DataFlowGraphModel>

using QtNodes::ConnectionId;
using QtNodes::DataFlowGraphModel;
using QtNodes::NodeDelegateModelRegistry;
using QtNodes::NodeFlag;
using QtNodes::NodeFlags;
using QtNodes::NodeId;
using QtNodes::PortType;
using QtNodes::NodeDataType;

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
        return !connectionLoop(connectionId);
    }

private:
    bool _detachPossible;

    bool _nodesLocked;
};
