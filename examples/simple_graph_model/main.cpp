#include <QtNodes/BasicGraphicsScene>
#include <QtNodes/ConnectionStyle>
#include <QtNodes/GraphicsView>
#include <QtNodes/StyleCollection>

#include <QAction>
#include <QScreen>
#include <QtWidgets/QApplication>
#include <QVBoxLayout>
#include <QPushButton>
#include "SimpleGraphModel.hpp"

using QtNodes::BasicGraphicsScene;
using QtNodes::ConnectionStyle;
using QtNodes::GraphicsView;
using QtNodes::NodeRole;
using QtNodes::StyleCollection;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget* mainWidget = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(mainWidget);

    SimpleGraphModel graphModel;

    // Initialize and connect two nodes.
    {
        NodeId id1 = graphModel.addNode();
        graphModel.setNodeData(id1, NodeRole::Position, QPointF(-800,-600));

        NodeId id2 = graphModel.addNode();
        graphModel.setNodeData(id2, NodeRole::Position, QPointF(300, 300));

        graphModel.addConnection(ConnectionId{id1, 0, id2, 0});
    }

    auto scene = new BasicGraphicsScene(graphModel);

    GraphicsView view(scene);

    // Setup context menu for creating new nodes.
    view.setContextMenuPolicy(Qt::ActionsContextMenu);
    QAction createNodeAction(QStringLiteral("Create Node"), &view);
    QObject::connect(&createNodeAction, &QAction::triggered, [&]() {
        // Mouse position in scene coordinates.
        QPointF posView = view.mapToScene(view.mapFromGlobal(QCursor::pos()));

        NodeId const newId = graphModel.addNode();
        graphModel.setNodeData(newId, NodeRole::Position, posView);
    });
    view.insertAction(view.actions().front(), &createNodeAction);

    view.setWindowTitle("Simple Node Graph");
    view.resize(800, 600);



    // Center window.
    //view.move(QApplication::primaryScreen()->availableGeometry().center() - view.rect().center());

    layout->addWidget(&view);

    QPushButton* btn = new QPushButton("center",mainWidget);

    QObject::connect(btn,&QPushButton::clicked,[&](){
        QPointF center = graphModel.nodesCenter();

        qDebug() << "before,center x:" << center.x() << " center y:" << center.y();

        view.centerScene(center);

        QPointF newCenter = graphModel.nodesCenter();
        qDebug() << "after,center x:" << newCenter.x() << " center y:" << newCenter.y();
    });

    layout->addWidget(btn);

    mainWidget->showNormal();

    return app.exec();
}
