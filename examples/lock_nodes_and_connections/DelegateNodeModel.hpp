#pragma once

#include <QtCore/QObject>

#include <QtNodes/NodeData>
#include <QtNodes/NodeDelegateModel>

#include <memory>
#include <QLabel>
#include <QPixmap>

using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDelegateModel;
using QtNodes::PortIndex;
using QtNodes::PortType;

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
        : _label(nullptr)
    { 
        auto& style = nodeStyle();
        QColor color = style.ConnectionPointColor;
    }

    CameraModel(const QString &name,
                    const QString &caption = "default caption",
                    const QString &category = "default category",
                    int inCount = 1,
                    int outCount = 1)
        : NodeDelegateModel(name, caption, category, inCount, outCount)
        , _label(nullptr)
    {
        auto &style = nodeStyle();
        QColor color = style.ConnectionPointColor;
    }

    ~CameraModel() { 
        if (_label) {
            delete _label;
        }
    }

private:
    QLabel *_label;

public:

    NodeDataType dataType(PortType const portType, PortIndex const portIndex) const override
    {
        if (portType == PortType::In) {
            return NodeDataType{name(), "Input"};
        } else if (portType == PortType::Out) {
            return NodeDataType{name(), "Output"};
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
        if (!_label) {
            _label = new QLabel();
            _label->setStyleSheet("QLabel {"
                                 "  background: transparent;"
                                 "}");
            _label->setAttribute(Qt::WA_TranslucentBackground);

            _label->setMargin(1);


            setSvgToLabel(_label, ":/images/images/default-operator.svg");
        }

        return _label;
    }
};
