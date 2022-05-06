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
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void on_lineEditElem_textChanged(const QString &arg1);

    void on_pushButtonEnter_clicked();

    void on_pushButtonRandom_clicked();

    void on_pushButtonMax_clicked();

    void on_pushButtonMin_clicked();

    void on_pushButtonAverage_clicked();

    void on_tableWidget_cellChanged(int row, int column);

    void on_comboBox_currentIndexChanged(int index);

    void on_pushButtonDeleteD_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
