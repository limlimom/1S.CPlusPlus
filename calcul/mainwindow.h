#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_radioButton_sum_clicked();

    void on_pushButton_rez_clicked();

    void on_radioButton_sub_clicked();

    void on_radioButton_mul_clicked();

    void on_radioButton_div_clicked();

    void on_radioButton_sqrt_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
