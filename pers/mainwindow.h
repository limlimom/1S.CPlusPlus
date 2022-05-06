#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox> //окошки с ошибками

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


    void on_pushButton_Clear_clicked();

    void on_pushButton_Create_clicked();

    void on_label_Cha_linkActivated(const QString &link);

    void on_radioButton_Sex_W_clicked();

    void on_radioButton_Sex_m_clicked();

private:
    Ui::MainWindow *ui;
    int points; // для хранения очков
};

#endif // MAINWINDOW_H
