#pragma once

#include <QtCore/QObject>

#include <QtNodes/NodeData>
#include <QtNodes/NodeDelegateModel>

#include <memory>

using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDelegateModel;
using QtNodes::PortIndex;
using QtNodes::PortType;

/// The class can potentially incapsulate any user data which need to
/// be transferred within the Node Editor graph
class MyNodeData : public NodeData
{
public:
    NodeDataType type() const override { return NodeDataType{"MyNodeData", "My Node Data"}; }
};

//------------------------------------------------------------------------------

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class MyDataModel : public NodeDelegateModel
{
    Q_OBJECT
public:
    MyDataModel(){}
    MyDataModel(const QString &uniqueName,
                          const QString &caption = "default caption",
                          const QString &category = "default category",
                            const QString &parentUniqueName = "parent",
                          unsigned int inCount = 1,
                          unsigned int outCount = 1): NodeDelegateModel(uniqueName, caption, category,parentUniqueName,inCount,outCount){}

    ~MyDataModel() = default;

public:

public:
    QJsonObject save() const override
    {
        QJsonObject modelJson;

        modelJson["name"] = uniqueName();

        return modelJson;
    }

public:
    unsigned int nPorts(PortType const) const { return 3; }

    NodeDataType dataType(PortType const, PortIndex const) const override
    {
        return MyNodeData().type();
    }

    std::shared_ptr<NodeData> outData(PortIndex) override { return std::make_shared<MyNodeData>(); }

    void setInData(std::shared_ptr<NodeData>, PortIndex const) override {}

    QWidget *embeddedWidget() override { return nullptr; }
};
