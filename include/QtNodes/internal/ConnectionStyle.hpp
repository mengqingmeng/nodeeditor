#pragma once

#include <QtGui/QColor>

#include "Export.hpp"
#include "Style.hpp"
#include <QColor>

namespace QtNodes {

class NODE_EDITOR_PUBLIC ConnectionStyle : public Style
{
public:
    ConnectionStyle();

    ConnectionStyle(QString jsonText);

    ~ConnectionStyle() = default;

public:
    static void setConnectionStyle(QString jsonText);

public:
    void loadJson(QJsonObject const &json) override;

    QJsonObject toJson() const override;

public:
    QColor constructionColor() const;
    QColor normalColor() const;
    QColor normalColor(QString typeId) const;
    QColor selectedColor() const;
    QColor selectedHaloColor() const;
    QColor hoveredColor() const;

    float lineWidth() const;
    float constructionLineWidth() const;
    float pointDiameter() const;

    bool useDataDefinedColors() const;

    /// @brief 输入箭头样式是否开启
    /// @return true:开启，false:关闭
    bool inArrow() const;

    /// @brief 输出箭头样式是否开启
    /// @return true:开启，false:关闭
    bool outArrow() const;

     void constructionColor(const QColor &color);

    void selectedColor(const QColor &color);

    void selectedHaloColor(const QColor &color);

    void hoveredColor(const QColor &color);

    void lineWidth(float width);

    void constructionLineWidth(float width);

    void pointDiameter(float diameter);

    void useDataDefinedColors(bool use);

    void inArraw(bool show);

    void outArrow(bool show);

private:
    QColor ConstructionColor;
    QColor NormalColor;
    QColor SelectedColor;
    QColor SelectedHaloColor;
    QColor HoveredColor;

    float LineWidth;
    float ConstructionLineWidth;

    /// @brief 圆圈直径
    float PointDiameter;

    bool UseDataDefinedColors;

    /// @brief 输入箭头样式是否开启
    bool InArrow;

    /// @brief 输出箭头样式是否开启
    bool OutArrow;
};
} // namespace QtNodes
