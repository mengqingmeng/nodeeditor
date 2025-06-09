#include <QtNodes/DataFlowGraphicsScene>
#include <QtNodes/GraphicsView>
#include <QtNodes/NodeDelegateModelRegistry>
#include <QtNodes/ConnectionStyle>
#include <QAction>
#include <QScreen>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>

#include "DataFlowModel.hpp"
#include "DelegateNodeModel.hpp"
using QtNodes::ConnectionStyle;
using QtNodes::DataFlowGraphicsScene;
using QtNodes::GraphicsView;
using QtNodes::NodeDelegateModelRegistry;
using QtNodes::NodeRole;

struct MenuItem
{
    /// @brief 标题
    QString caption;
    /// @brief 唯一名称
    QString uniqueName;
    /// @brief 子菜单
    QList<MenuItem> subItems;
};

static std::shared_ptr<NodeDelegateModelRegistry> registerDataModels()
{
    auto ret = std::make_shared<NodeDelegateModelRegistry>();

    QList<MenuItem> operators = {
        {("图像采集"), "capture", {{("相机"), "camera"}, {("本地"), "localImage"}}},
            {("定位"),
             "locate",
             {{("斑点检测"), "dot"},
              {("找圆"), "findCircle"},
              {("模板匹配"), "templateMatch"},
              {("模板比对"), "templateCompare"},
              {("轮廓比对"), "contourCompare"},
              {("找顶点"), "findVertex"},
              {("找多边"), "findSides"}}},
         {("图像处理"),
             "imageProcessing",
             {
                 {("滤波"), "filter"},
                 {("二值化"), "threshold"},
                 {("裁剪"), "cut"},
                 {("灰度转换"), "gray"},
                 {("颜色提取"), "colorExtract"},
                 {("仿射变换"), "affineTransform"},
                 {("形态学"), "morphology"},
                 {("边缘梯度"), "edgeGradient"},
                 {("亮度"), "brightness"},
                 {("对比度"), "contrastRatio"},
                 {("像素计数"), "pixelCount"},
                 {("图像运算"), "imageOperate"},
                 {("圆展开"), "unfoldCircle"},
                 {("图像拼接"), "imageStitch"},
             }},
            {("标定"), "calibration"},
            {("测量"), "measure"},
            {("识别"), "identify"},
            {("深度学习"), "deepLearning"},
            {("逻辑"), "judge"},
            {("生成工具"), "generate"},
            {("通讯"), "communication"},
            {("辅助工具"), "assistant"},
            {("其它"), "other"}};


    for (const auto &parentItem : operators) {
        for (const auto &subItem : parentItem.subItems) {
                ret->registerModel<CameraModel>(subItem.uniqueName,
                                            subItem.caption,
                                            parentItem.caption,
                                            parentItem.uniqueName);
        }
    }



    return ret;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

     ConnectionStyle::setConnectionStyle(
        R"(
            {
            "ConnectionStyle": {
                "InArrow" : true,
                "OutArrow" : false,
                "ConstructionColor":"darkcyan",
                "PointDiameter": 8.0
            }
            }
  )");

    DataFlowModel graphModel(registerDataModels());
    
    auto scene = new DataFlowGraphicsScene(graphModel);

    scene->setOrientation(Qt::Vertical);

    QWidget window;

    QHBoxLayout *l = new QHBoxLayout(&window);

    GraphicsView view(scene);

    l->addWidget(&view);

    QGroupBox *groupBox = new QGroupBox("Options");

    QCheckBox *cb1 = new QCheckBox("Nodes are locked");
    QCheckBox *cb2 = new QCheckBox("Connections detachable");
    cb2->setChecked(true);

    QVBoxLayout *vbl = new QVBoxLayout;
    vbl->addWidget(cb1);
    vbl->addWidget(cb2);
    vbl->addStretch();
    groupBox->setLayout(vbl);

    QObject::connect(cb1, &QCheckBox::stateChanged, [&graphModel](int state) {
        graphModel.setNodesLocked(state == Qt::Checked);
    });

    QObject::connect(cb2, &QCheckBox::stateChanged, [&graphModel](int state) {
        graphModel.setDetachPossible(state == Qt::Checked);
    });

    QObject::connect(scene, &DataFlowGraphicsScene::nodeClicked, [&](NodeId const nodeId) {
        qDebug() << "node clicked:" << nodeId;    
    });

    l->addWidget(groupBox);

    window.setWindowTitle("Locked Nodes and Connections");
    window.resize(800, 600);

    // Center window.
    window.move(QApplication::primaryScreen()->availableGeometry().center() - view.rect().center());
    window.showNormal();

    return app.exec();
}
