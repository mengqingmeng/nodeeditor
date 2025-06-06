#pragma once

#include <QtCore/QObject>

#include <QtNodes/NodeData>
#include <QtNodes/NodeDelegateModel>

#include <memory>
#include <QLabel>
#include <QPixmap>
#include <QSvgWidget>

using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDelegateModel;
using QtNodes::PortIndex;
using QtNodes::PortType;
using QtNodes::PortTransDataType;

class CameraModelData : public NodeData
{
public:
    NodeDataType type() const override { return NodeDataType{"SimpleData", "Simple Data"}; }
};

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class CameraModel : public NodeDelegateModel
{
    Q_OBJECT

public:

    CameraModel()
        : _svgWidget(nullptr)
    { 
        auto& style = nodeStyle();
        QColor color = style.ConnectionPointColor;
    }

    CameraModel(const QString &uniqueName,
                    const QString &caption = "default caption",
                    const QString &category = "default category",
                    const QString &parentUniqueName = "parent",
                    int inCount = 1,
                    int outCount = 1)
        : NodeDelegateModel(uniqueName, caption, category, parentUniqueName, inCount, outCount)
        , _svgWidget(nullptr)

    {
        auto &style = nodeStyle();
        QColor color = style.ConnectionPointColor;
        setPortTransTypes({PortType::In, 0}, {PortTransDataType::Int, PortTransDataType::Bool});
        setPortTransTypes({PortType::Out, 0}, {PortTransDataType::String, PortTransDataType::Bool});
    }

    ~CameraModel() { 
        if (_svgWidget) {
            delete _svgWidget;
        }
    }

private:
    QSvgWidget *_svgWidget;

public:

    NodeDataType dataType(PortType const portType, PortIndex const portIndex) const override
    {
        if (portType == PortType::In) {
            return NodeDataType{uniqueName(), "Input"};
        } else if (portType == PortType::Out) {
            return NodeDataType{uniqueName(), "Output"};
        } else {
            return NodeDataType{"Default", "Default"};
        }
    }

    std::shared_ptr<NodeData> outData(PortIndex const port) override
    {
        return std::make_shared<CameraModelData>();
    }

    bool portCaptionVisible(PortType, PortIndex) const override {
        return false; 
    }

    void setInData(std::shared_ptr<NodeData>, PortIndex const) override {}

    QWidget *embeddedWidget() override
    {
        if (!_svgWidget) {
            _svgWidget = new QSvgWidget(":/images/images/default.svg");
            _svgWidget->setStyleSheet("QSvgWidget {"
                                 "  background: transparent;"
                                 "}");
            _svgWidget->setFixedSize(18, 18 ); // 设置显示尺寸
        }

        return _svgWidget;
    }
};
