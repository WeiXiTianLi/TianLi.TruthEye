#include "te.popup.window.h"

// 3rd
#include <spdlog/spdlog.h>
#include <cpr/cpr/cpr.h>
#include <cpr/curl/curl.h>
// qt
#include <QApplication>
#include <QMetaType>
#include <QGraphicsDropShadowEffect>
// std
#include <future>
#include <mutex>
#include <atomic>

bool is_utf8(const std::string &string)
{
    int len = MultiByteToWideChar(CP_UTF8, 0, string.c_str(), -1, NULL, 0);
    wchar_t *wstr = new wchar_t[len + 1];
    memset(wstr, 0, len * 2 + 2);
    MultiByteToWideChar(CP_UTF8, 0, string.c_str(), -1, wstr, len);
    len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
    char *str = new char[len + 1];
    memset(str, 0, len + 1);
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
    std::string ret_string = str;
    delete[] str;
    delete[] wstr;
    return (ret_string == string);
}

std::string utf8_to_gbk(const std::string &utf8_string)
{
    std::string ret_string;
    int len = MultiByteToWideChar(CP_UTF8, 0, utf8_string.c_str(), -1, NULL, 0);
    wchar_t *gbk_wstring = new wchar_t[len + 1];
    memset(gbk_wstring, 0, len * 2 + 2);
    MultiByteToWideChar(CP_UTF8, 0, utf8_string.c_str(), -1, gbk_wstring, len);
    len = WideCharToMultiByte(CP_ACP, 0, gbk_wstring, -1, NULL, 0, NULL, NULL);
    char *gbk_string = new char[len + 1];
    memset(gbk_string, 0, len + 1);
    WideCharToMultiByte(CP_ACP, 0, gbk_wstring, -1, gbk_string, len, NULL, NULL);
    ret_string = gbk_string;
    delete[] gbk_string;
    delete[] gbk_wstring;
    return ret_string;
}

std::string gbk_to_utf8(const std::string &gbk_string)
{
    std::string ret_string;
    int len = MultiByteToWideChar(CP_ACP, 0, gbk_string.c_str(), -1, NULL, 0);
    wchar_t *utf8_wstring = new wchar_t[len + 1];
    memset(utf8_wstring, 0, len * 2 + 2);
    MultiByteToWideChar(CP_ACP, 0, gbk_string.c_str(), -1, utf8_wstring, len);
    len = WideCharToMultiByte(CP_UTF8, 0, utf8_wstring, -1, NULL, 0, NULL, NULL);
    char *utf8_string = new char[len + 1];
    memset(utf8_string, 0, len + 1);
    WideCharToMultiByte(CP_UTF8, 0, utf8_wstring, -1, utf8_string, len, NULL, NULL);
    ret_string = utf8_string;
    delete[] utf8_string;
    delete[] utf8_wstring;
    return ret_string;
}

std::string to_utf8(const std::string &string)
{
    if (is_utf8(string))
    {
        return string;
    }
    else
    {
        return gbk_to_utf8(string);
    }
}

void tePopupWindow::setupUi(QWidget *tePopupWindow)
{
    tePopupWindow->setObjectName(QString::fromUtf8("tePopupWindow"));
    tePopupWindow->resize(232, 232 * 2 + 48);

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

    QLabel *text_label = new QLabel(tePopupWindow);
    text_label->setGeometry(10, 232 + 10, 212, 48);
    text_label->setAlignment(Qt::AlignCenter);
    text_label->setObjectName(QString::fromUtf8("text_label"));
    text_label->setStyleSheet("QLabel{color:rgba(255,255,255,0.8);font-size:20px;font-weight:bold;font-family:Microsoft YaHei;}");
    m_info = text_label;
    // text_label->setText("Hello World");

    QLabel *picture_label = new QLabel(tePopupWindow);
    picture_label->setGeometry(10, 232 + 10 + 48, 212, 212);
    picture_label->setAlignment(Qt::AlignCenter);
    picture_label->setObjectName(QString::fromUtf8("picture_label"));
}

tePopupWindow::tePopupWindow(QWidget *parent)
{
    setupUi(this);
    // 设置无边框
    setWindowFlags(Qt::FramelessWindowHint);
    // 设置背景透明
    setAttribute(Qt::WA_TranslucentBackground);
    // 设置窗口置顶
    SetWindowPos((HWND)this->winId(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
    spdlog::get("trace")->info("窗口置顶：{:X}", (int64_t)this->winId());
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
            auto p = pos + QPointF(232 / 2, 232 / 2) - QPointF(icon.width() / 2, icon.height() / 2);
            // 绘制icon
            painter.drawPixmap(p, icon);
        }
    }

    if (m_info_text.empty() == false)
    {
        // QPen pen(QColor(255, 255, 255, 200));
        // painter.setPen(pen);
        // painter.drawText(QRect(10, 232 + 10, 212, 48), Qt::AlignCenter, QString::fromStdString(m_info_text));
        m_info->setText(QString::fromStdString(m_info_text));
    }

    if (m_info_image.isNull() == false)
    {
        painter.drawPixmap(10, 232 + 10 + 48, m_info_image);
    }

    SetWindowPos((HWND)this->winId(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
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

void tePopupWindow::add_info_text(const std::string &text)
{
    m_info_text = text;
}

void tePopupWindow::add_info_image(const std::string &url)
{
    m_info_image = get_image(url);
}

QPixmap tePopupWindow::get_icon(const std::string &icon_url)
{
    if (icon_url.empty())
        return QPixmap();
    // 缓存直接返回
    auto it = m_icon_cache.find(icon_url);
    if (it != m_icon_cache.end())
        return it->second;
    // 下载
    auto res = cpr::Get(cpr::Url{icon_url});
    if (res.status_code != 200)
    {
        spdlog::warn("下载图标失败 {} {}", icon_url, res.status_code);
        return QPixmap();
    }
    // 转换
    QPixmap pixmap;
    pixmap.loadFromData((unsigned char *)res.text.c_str(), res.text.size());
    // 缩放
    pixmap = pixmap.scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    // 缓存
    m_icon_cache[icon_url] = pixmap;
    return pixmap;
}

QPixmap tePopupWindow::get_image(const std::string &image_url)
{
    if (image_url.empty())
        return QPixmap();
    // 缓存直接返回
    auto it = m_icon_cache.find(image_url);
    if (it != m_icon_cache.end())
        return it->second;
    // 下载
    auto res = cpr::Get(cpr::Url{image_url});
    if (res.status_code != 200)
    {
        spdlog::warn("下载图片失败 {} {}", image_url, res.status_code);
        return QPixmap();
    }
    // 转换
    QPixmap pixmap;
    pixmap.loadFromData((unsigned char *)res.text.c_str(), res.text.size());
    // 缩放
    pixmap = pixmap.scaled(212, 212, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    // 缓存
    m_icon_cache[image_url] = pixmap;
    return pixmap;
}

// TODO: 版本分发调用
void tePopupWindow::parse_json_v1_0_0(json::value json)
{
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
        auto pix = get_icon(item.url);
        add_icons(pix, item.name, item.url, item.points);
    }
}
void tePopupWindow::parse_json_v1_0_1(json::value json)
{
    struct tePoint
    {
        float x;
        float y;
    };
    struct content_info
    {
        std::string text;
        std::string picture_url;
    };
    struct item_set
    {
        std::string name;
        std::string url;
        std::vector<QPointF> points;
        content_info content_info;
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
        item_set.content_info.text = "";
        item_set.content_info.picture_url = "";
        if (item["content_info"].is_object())
        {
            try
            {
                item_set.content_info.text = to_utf8(item["content_info"]["text"].as_string());
                item_set.content_info.picture_url = item["content_info"]["picture_url"].as_string();
            }
            catch (const std::exception &e)
            {
                spdlog::error("json解析[content_info][text]/[picture_url]失败 {}", e.what());
            }
        }
        items.push_back(item_set);
    }
    // download image
    for (auto &item : items)
    {
        auto pix = get_icon(item.url);
        add_icons(pix, item.name, item.url, item.points);
        add_info_text(item.content_info.text);
        add_info_image(item.content_info.picture_url);
    }
}

void tePopupWindow::set_json_params(const char *json_buff, unsigned int buff_size)
{
    // copy buff to string
    auto json_buff_copy = std::make_unique<char[]>(buff_size);
    memcpy(json_buff_copy.get(), json_buff, buff_size);

    std::string json_str(json_buff_copy.get(), buff_size);
    spdlog::get("trace")->trace("set_json_params {}", json_str);
    auto json_res = json::parse(json_str);
    if (json_res.has_value() == false)
    {
        spdlog::warn("json解析失败 {}", json_str);
        return;
    }

    auto json = json_res.value();
    auto version = json["version"].as_string();

    if (version == "1.0.0")
    {
        this->resize(232, 232);
        try
        {
            parse_json_v1_0_0(json);
        }
        catch (const std::exception &e)
        {
            spdlog::error("json解析失败 parse_json_v1_0_0: {}", e.what());
        }
    }
    else if (version == "1.0.1")
    {
        this->resize(232, 232 * 2 + 48);
        try
        {
            parse_json_v1_0_1(json);
        }
        catch (const std::exception &e)
        {
            spdlog::error("json解析失败 parse_json_v1_0_1: {}", e.what());
        }
    }
    else
    {
        spdlog::warn("不支持的版本 {}", json["version"].as_string());
    }

    update();
}