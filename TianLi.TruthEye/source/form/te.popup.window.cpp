#include "te.popup.window.h"

// 3rd
#include <meojson/include/json.hpp>
#include <cpp-httplib/include/httplib.h>
#include <cpr/include/cpr/cpr.h>
#include <cpr/include/curl/curl.h>
// qt
#include <QApplication>
#include <QMetaType>
#include <QGraphicsDropShadowEffect>
// std
#include <future>
#include <mutex>
#include <atomic>
void tePopupWindow::setupUi(QWidget *tePopupWindow)
{
    tePopupWindow->setObjectName(QString::fromUtf8("tePopupWindow"));
    tePopupWindow->resize(232, 232);

    QLabel *label = new QLabel(tePopupWindow);
    // label->setText("Hello World");
    label->setGeometry(10, 10, 212, 212);
    label->setAlignment(Qt::AlignCenter);
    label->setObjectName(QString::fromUtf8("label"));
    label->setStyleSheet("QLabel{background-color:rgba(0,0,0,0.1);color:rgb(255,255,255);font-size:20px;font-weight:bold;font-family:Microsoft YaHei;border-radius:106px;}");
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(label);
    shadow->setOffset(0, 0);
    shadow->setColor(Qt::white);
    shadow->setBlurRadius(10);
    label->setGraphicsEffect(shadow);
}

tePopupWindow::tePopupWindow(QWidget *parent)
{
    setupUi(this);
    // 设置无边框
    setWindowFlags(Qt::FramelessWindowHint);
    // 设置背景透明
    setAttribute(Qt::WA_TranslucentBackground);
    SetWindowPos((HWND)this->winId(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
    // 设置窗口置顶
    // setWindowFlags(Qt::WindowStaysOnTopHint);

    // add shadow

    connect(this, &tePopupWindow::show_window, this, &tePopupWindow::show);
    connect(this, &tePopupWindow::hide_window, this, &tePopupWindow::hide);
    connect(this, &tePopupWindow::signal_set_json_params, this, &tePopupWindow::set_json_params);
}

tePopupWindow::~tePopupWindow()
{
}

void tePopupWindow::paintEvent(QPaintEvent *event)
{
    // 根据icons_pos绘制icon
    QPainter painter(this);
    for (auto &[name, icon] : m_icons)
    {
        for (auto &pos : m_icons_pos[name])
        {
            // 以窗口中心为原点 以icon的中心为绘制点
            auto p = pos + QPointF(width() / 2, height() / 2) - QPointF(icon.width() / 2, icon.height() / 2);
            // 绘制icon
            painter.drawPixmap(p, icon);
        }
    }
}

void tePopupWindow::mousePressEvent(QMouseEvent *event)
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

void tePopupWindow::mouseMoveEvent(QMouseEvent *event)
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

void tePopupWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        // 鼠标左键释放
        // 清除鼠标按下标志
        m_mouse_move_event.flag = false;
    }
}

void tePopupWindow::add_icon(QPixmap icon, const std::string &icon_name, const QPointF &pos)
{
    m_icons[icon_name] = icon;
    m_icons_pos[icon_name].push_back(pos);
}

void tePopupWindow::add_icons(QPixmap icon, const std::string &icon_name, const std::string &icon_url, const std::vector<QPointF> &pos)
{
    m_icons[icon_name] = icon;
    m_icons_pos[icon_name] = pos;
}

QPixmap tePopupWindow::get_icon(const std::string &icon_name, const std::string &icon_url)
{
    // 缓存直接返回
    auto it = m_icon_cache.find(icon_name);
    if (it != m_icon_cache.end())
    {
        return it->second;
    }
    // 下载
    auto res = cpr::Get(cpr::Url{icon_url});
    if (res.status_code != 200)
    {
        return QPixmap();
    }
    // 转换
    QPixmap pixmap;
    pixmap.loadFromData((unsigned char *)res.text.c_str(), res.text.size());
    // 缓存
    m_icon_cache[icon_name] = pixmap;
    return pixmap;
}

void tePopupWindow::set_json_params(const char *json_buff, unsigned int buff_size)
{
    // copy buff to string
    auto json_buff_copy = std::make_unique<char[]>(buff_size);
    memcpy(json_buff_copy.get(), json_buff, buff_size);

    std::string json_str(json_buff_copy.get(), buff_size);
    auto json_res = json::parse(json_str);
    if (json_res.has_value() == false)
    {
        return;
    }
    auto json = json_res.value();

    if (json["version"] != "1.0.0")
    {
        return;
    }
    struct tePoint
    {
        float x;
        float y;
    };
    struct item_set
    {
        std::string name;
        std::string url;
        std::vector<QPointF> points;
    };

    std::vector<item_set> items;
    for (auto &item : json["content"].as_array())
    {
        item_set item_set;
        item_set.name = item["name"].as_string();
        item_set.url = item["url"].as_string();
        for (auto &point : item["points"].as_array())
        {
            QPointF qpoint;
            qpoint.setX(point["x"].as_float());
            qpoint.setY(point["y"].as_float());
            item_set.points.push_back(qpoint);
        }
        items.push_back(item_set);
    }
    // download image
    for (auto &item : items)
    {
        auto pix = get_icon(item.name, item.url);
        add_icons(pix, item.name, item.url, item.points);
    }
    update();
}
