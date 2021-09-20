#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>

#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_refresh_btn_clicked();
    void on_open_btn_clicked();
    void on_start_stop_btn_clicked();
    void on_calibrate_btn_clicked();
    void on_user_expect_slider_valueChanged(int value);

    void on_speed_kp_slider_valueChanged(int value);

    void on_speed_ki_slider_valueChanged(int value);

    void on_speed_kd_slider_valueChanged(int value);

    void on_speed_summax_slider_valueChanged(int value);

public slots:
    void serial_received();
    void slider_timer_timeout();

private:
    Ui::MainWindow *ui;
    QSerialPort *serial;
    bool expect_slider_change_flag = false;
    bool speed_slider_change_flag[4];
    bool angle_slider_change_flag[4];
    float expect_slider_value = 0;
    float speed_slider_value[4];
    float angle_slider_value[4];
    QTimer *slider_timer;
    uint64_t curve_counter = 0;
    QVector<double> curve_velocity, curve_angle, curve_x;
    void refresh_serial_port();
    bool set_serial_badurate();
    void setup_custom_plot();
    void mdtp_receive_handler(unsigned char data);
    void mdtp_data_transmit(unsigned char pid, const unsigned char *data);
    void mdtp_callback_handler(unsigned char pid, const unsigned char *data);
};
#endif // MAINWINDOW_H
