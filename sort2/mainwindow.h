#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QFileDialog>
//#include <QFileInfo>

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
    void on_pushButton_num_clicked();

    void on_pushButton_min_clicked();

    void on_pushButton_rand_clicked();

    void on_pushButton_arr_clicked();

    void on_pushButton_mid_clicked();

    void on_pushButton_max_clicked();

    void on_pushButton_bubble_clicked();

    void on_pushButton_quick_clicked();

    void on_pushButton_gnome_clicked();

    void on_pushButton_brush_clicked();

    void on_pushButton_bogo_clicked();

    void on_pushButton_del_clicked();

    void on_pushButton_search_clicked();

    void on_tableWidget_itemChanged(QTableWidgetItem *item);

    void on_pushButton_savetxt_clicked();

    void on_spinBox_valueChanged(int arg1);

    void on_pushButton_opentxt_clicked();

    void on_pushButton_savebin_clicked();

    void on_pushButton_openbin_clicked();

   // void on_checking_cell_(int row, int column);

private:
    Ui::MainWindow *ui;
    void getMassive(double *mas, int &size, bool &ok);
    void setMassive (double *mas, int size);
    void quicksort(double *mas, int size);
    void sortgnome (double *mas, int size);
    void sortbrush (double *mas, int size);


    bool correct(double *arr, int size);
    void shuffle(double *arr, int size);
    void bogoSort(double *arr, int size);

    bool sorted = false; //была ли сортировка
    bool deletedDoubles = false; // было ли удаление дубликатов

    bool fl1=false, fl2=false;//fl1 true если сохранено; fl2 true если есть незаполненные ячейки
    QString currentFile= "";
    bool no_auto_izmen;
};

#endif // MAINWINDOW_H
