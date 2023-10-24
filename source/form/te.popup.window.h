#pragma once
#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QGraphicsDropShadowEffect>
#include <meojson/json.hpp>

class tePopupWindow : public QWidget
{
    Q_OBJECT

private:
    void setupUi(QWidget *tePopupWindow);

public:
    tePopupWindow(QWidget *parent = nullptr);
    ~tePopupWindow();

private:
    // overload
    void paintEvent(QPaintEvent *event) override;
    struct mouse_move_event
    {
        QPoint flag_pos = {};
        bool flag = false;
    } m_mouse_move_event;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
signals:
    void show_window();
    void hide_window();
    void signal_set_json_params(const char *json_buff, unsigned int buff_size);

private:
    void parse_json_v1_0_0(json::value json);
    void parse_json_v1_0_1(json::value json);
private slots:
    void set_json_params(const char *json_buff, unsigned int buff_size);

private:
    QLabel *m_info;
    // 需要绘制的图标
    std::map<std::string, QPixmap> m_icons;
    std::map<std::string, std::vector<QPointF>> m_icons_pos;
    std::string m_info_text;
    QPixmap m_info_image;
    void add_icon(QPixmap icon, const std::string &icon_name, const QPointF &pos);
    void add_icons(QPixmap icon, const std::string &icon_name, const std::string &icon_url, const std::vector<QPointF> &pos);
    void add_info_text(const std::string &text);
    void add_info_image(const std::string &url);

private:
    // 图标缓存
    std::map<std::string, QPixmap> m_icon_cache;
    QPixmap get_icon(const std::string &icon_url);
    QPixmap get_image(const std::string &image_url);
};