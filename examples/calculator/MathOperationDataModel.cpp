#include "MathOperationDataModel.hpp"

#include "DecimalData.hpp"

MathOperationDataModel::MathOperationDataModel():_label(nullptr) {}


MathOperationDataModel::MathOperationDataModel(const QString &name,
                                               const QString &caption,
                                               const QString &category,
                                               int inCount,
                                               int outCount)
    : NodeDelegateModel(
    name, caption, category, inCount, outCount),_label(nullptr)
{}

unsigned int MathOperationDataModel::nPorts(PortType portType) const
{
    unsigned int result;

    if (portType == PortType::In)
        result = 2;
    else
        result = 1;

    return result;
}

NodeDataType MathOperationDataModel::dataType(PortType, PortIndex) const
{
    return DecimalData().type();
}

std::shared_ptr<NodeData> MathOperationDataModel::outData(PortIndex)
{
    return std::static_pointer_cast<NodeData>(_result);
}

void MathOperationDataModel::setInData(std::shared_ptr<NodeData> data, PortIndex portIndex)
{
    auto numberData = std::dynamic_pointer_cast<DecimalData>(data);

    if (!data) {
        Q_EMIT dataInvalidated(0);
    }

    if (portIndex == 0) {
        _number1 = numberData;
    } else {
        _number2 = numberData;
    }

    compute();
}

QWidget* MathOperationDataModel::embeddedWidget() {
    if (!_label) {
        _label = new QLabel(_operationType);
        _label->setMargin(3);
    }

    return _label;
}
