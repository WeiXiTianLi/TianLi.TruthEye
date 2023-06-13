#include "te.popup.window.h"

void tePopupWindow::setupUi(QWidget* tePopupWindow)
{
    tePopupWindow->setObjectName(QString::fromUtf8("tePopupWindow"));
    tePopupWindow->resize(232, 232);

    QLabel* label = new QLabel(tePopupWindow);
    label->setText("Hello World");
    label->setGeometry(10, 10, 212, 212);
    label->setAlignment(Qt::AlignCenter);
    label->setObjectName(QString::fromUtf8("label"));
    label->setStyleSheet("QLabel{background-color:rgba(0,0,0,0.5);color:rgb(255,255,255);font-size:20px;font-weight:bold;font-family:Microsoft YaHei;border-radius:8px;}");
    QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect(label);
    shadow->setOffset(0, 0);
    shadow->setColor(Qt::white);
    shadow->setBlurRadius(10);
    label->setGraphicsEffect(shadow);
}

tePopupWindow::tePopupWindow(QWidget* parent)
{
    setupUi(this);
    // 设置无边框
    setWindowFlags(Qt::FramelessWindowHint);
    // 设置背景透明
    setAttribute(Qt::WA_TranslucentBackground);
    // 设置窗口置顶
    //setWindowFlags(Qt::WindowStaysOnTopHint);

    // add shadow

    connect(this, &tePopupWindow::show_window, this, &tePopupWindow::show);
    connect(this, &tePopupWindow::hide_window, this, &tePopupWindow::hide);
}

tePopupWindow::~tePopupWindow()
{
}

void tePopupWindow::paintEvent(QPaintEvent* event)
{
    // draw effect
    //QPainter painter(this);
    //painter.setRenderHint(QPainter::Antialiasing, true);
    //painter.setPen(Qt::NoPen);
    //painter.setBrush(QColor(0, 0, 0, 0));
    //painter.drawRect(rect());
    //painter.setBrush(QColor(0, 0, 0, 200));
    //painter.drawRoundedRect(rect(), 10, 10);
    //QWidget::paintEvent(event);
}

void tePopupWindow::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        // 鼠标左键按下
        // 记录当前鼠标位置
        m_mouse_move_event.flag_pos = event->globalPos();
        // 设置鼠标按下标志
        m_mouse_move_event.flag = true;
    }
}

void tePopupWindow::mouseMoveEvent(QMouseEvent* event)
{
    if (m_mouse_move_event.flag)
    {
        // 鼠标左键按下的情况下移动
        // 计算鼠标位置偏移量
        QPoint offset = event->globalPos() - m_mouse_move_event.flag_pos;
        // 将窗口移动到鼠标移动后的位置
        move(pos() + offset);
        // 更新flag_pos
        m_mouse_move_event.flag_pos = event->globalPos();
    }
}

void tePopupWindow::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        // 鼠标左键释放
        // 清除鼠标按下标志
        m_mouse_move_event.flag = false;
    }
}
