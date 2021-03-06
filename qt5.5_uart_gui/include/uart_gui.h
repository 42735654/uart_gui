#ifndef UART_GUI_H
#define UART_GUI_H
#include <QComboBox>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QTextBrowser>
#include <QMainWindow>
#include "uart_handler.h"
#include <QGridLayout>
#include <QWidget>
#include <QStackedLayout>
#include <QFormLayout>
#include <QDebug>
#include <QByteArray>
#include <QTextStream>
#include <QFile>
#include <QMutex>
#include <QMutexLocker>
#include <QCheckBox>

#include "type_def.h"
#include "config.h"
#include "uart_handler.h"

class uart_gui:public QMainWindow
{
    Q_OBJECT
private:
    QComboBox *port_index;      //串口列表
    QWidget *for_cert;                  //用来布局
    QLabel *uart_stat;                    //串口状态
    QLineEdit *send_text;               //发送编辑框
    QCheckBox *send_hex;               //发送16进制
    QCheckBox *if_log_file;             //输出日志到文件
    QPushButton *send;                  //发送按钮
    QPushButton *set_arg;               //设置参数按钮
    QTextBrowser *uart_log;             //终端显示框
    QLabel space;                              //占位控件
    QPushButton *clear;                              //清屏
    QPushButton *pb_pause;                              //暂停输出
    QGridLayout *main_lay;              //主布局
    QFormLayout *widgets_layout;    //控件布局
    QPalette window_bg;
    //自定义布局列表
    widgets_list sw;

    QTextStream* log_stream;
    QFile *log_file;
    QMutex file_mutex;
    QMutex tb_mutex;
    //自动添加控件的数据信息
    int rows;
    int role;
    int count;

    bool text_browser_pause;
private:
    void init_log_file(QString filename);
    void init_base_widgets();       //初始化基础控件
    void init_layout();                     //初始化布局
    void init_connections();                //初始化内部信号与曹
    void add_widget_by_info(status_widgets_info *swi);                      //根据描述添加控件
    virtual void set_ui_by_arg();                   //根据参数设置控件显示
    void stop_log_file();
    void set_pb_background_pic(QPushButton *pb);
    void set_lineedit_background_pic(QLineEdit *pb);

public:
    uart_gui(uart_handler *hd);
    virtual ~uart_gui();
    void add_widgets(QWidget *any_widgets, bool full_row = false);  //向控件布局中添加一个控件
    void add_widgets_by_infos(status_widgets_info *swi, int count);     //根据描述列表添加控件
    void set_text_style(QWidget *pb);


public slots:
    void on_port_index_currentIndexChanged(const QString &arg1);        //串口选择改变时
    void send_line_text();                                                                                  //发送按钮
    void text_browser_text_changed();                                                           //设置textbrower显示始终在最后一行
    void __log_to_ui(QString log, int type = LOG_TYPE_INFO);                                                                  //打印信息到textbrowser中
    void __log_to_file(QString log);                   //打印信息到文件中
    void handle_uart_to_ui_signal(uart_handler::signal_type t);
    virtual void set_arg_by_ui();                   //根据UI控件设置参数
    void clear_browser(){
        uart_log->clear();
        uart_log->setFontPointSize(12);
    }
    void pause_browser();
    void on_checkbox_log_to_file();

protected:
    uart_handler *uhd;                         //串口操作类
};

#endif // UART_GUI_H
