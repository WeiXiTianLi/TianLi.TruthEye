#pragma once
#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QGraphicsDropShadowEffect>

class tePopupWindow : public QWidget
{
    Q_OBJECT

private:
    void setupUi(QWidget* tePopupWindow);
public:
    tePopupWindow(QWidget* parent = nullptr);
    ~tePopupWindow();
private:
    // overload
    void paintEvent(QPaintEvent* event) override;
    struct mouse_move_event
    {
        QPoint flag_pos = {};
        bool flag = false;
    } m_mouse_move_event;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event)override;
signals:
    void show_window();
    void hide_window();


};