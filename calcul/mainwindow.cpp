#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<cmath>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_err->setVisible(false); //прячем сообщ с ошиб
    ui->label_rez->hide(); //прячем сообщ с рез
    ui->radioButton_sum->click(); //имитация клика в реж слож
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_radioButton_sum_clicked()
{
    ui->label_err->setVisible(false); //прячем сообщ с ошиб
    ui->label_rez->hide(); //прячем сообщ с рез
    ui->label_ope1->setText("Слагаемое 1"); //меняем подпис
    ui->label_ope2->setText("Слагаемое 2"); //меняем пд
    ui->pushButton_rez->setText("Сумма"); //мен пд
    ui->lineEdit_opr2->setVisible(true);
    ui->label_ope2->setVisible(true);
}
void MainWindow::on_radioButton_sub_clicked()
{
    ui->label_err->setVisible(false); //прячем сообщ с ошиб
    ui->label_rez->hide(); //прячем сообщ с рез
    ui->label_ope1->setText("Уменьшаемое"); //меняем подпис
    ui->label_ope2->setText("Вычитаемое"); //меняем пд
    ui->pushButton_rez->setText("Разность"); //мен пд
    ui->lineEdit_opr2->setVisible(true);
    ui->label_ope2->setVisible(true);
}
void MainWindow::on_radioButton_mul_clicked()
{
    ui->label_err->setVisible(false); //прячем сообщ с ошиб
    ui->label_rez->hide(); //прячем сообщ с рез
    ui->label_ope1->setText("Множетель 1"); //меняем подпис
    ui->label_ope2->setText("Множетель 2"); //меняем пд
    ui->pushButton_rez->setText("Произведение"); //мен пд
    ui->lineEdit_opr2->setVisible(true);
    ui->label_ope2->setVisible(true);
}
void MainWindow::on_radioButton_div_clicked()
{
    ui->label_err->setVisible(false); //прячем сообщ с ошиб
    ui->label_rez->hide(); //прячем сообщ с рез
    ui->label_ope1->setText("Делимое"); //меняем подпис
    ui->label_ope2->setText("Делитель"); //меняем пд
    ui->pushButton_rez->setText("Частное"); //мен пд
    ui->lineEdit_opr2->setVisible(true);
    ui->label_ope2->setVisible(true);
}
void MainWindow::on_radioButton_sqrt_clicked()
{
    ui->label_err->setVisible(false); //прячем сообщ с ошиб
    ui->label_rez->hide(); //прячем сообщ с рез
    ui->label_ope1->setText("Подкоренное число"); //меняем подпис
    ui->label_ope2->setVisible(false); //меняем пд
    ui->pushButton_rez->setText("Подкоренное выражение"); //мен пд
    ui->lineEdit_opr2->setVisible(false);
}
void MainWindow::on_pushButton_rez_clicked()
{
    double op1,op2,rez;
    bool fl1;
    QString stroka; //
    if (ui->radioButton_sum->isChecked()) // выбрано сложение
    {
        stroka=ui->lineEdit_opr1->text(); //счит введ слаг 1
        op1=stroka.toDouble(&fl1); //пробуем преобразовать
        if (fl1)
        {
            stroka=ui->lineEdit_opr2->text(); //счит введ слаг 2
            op2=stroka.toDouble(&fl1); //пробуем преобразовать
            if (fl1)
            {
                rez=op1+op2; //сумма
                ui->label_err->hide(); //прячем сообщ об ошиб
                stroka.setNum(rez);  //знаки после зап чтоюы считались числа с е
                ui->label_rez->setText(stroka);
                ui->label_rez->show();// выводим сообщ с рез

                if (qIsInf(rez))
                {
                    ui->label_err->setText("Значение вышло за диапазон допустимых чисел");
                    ui->label_rez->setVisible(false);
                    ui->label_err->setVisible(true);
                }
            }
            else
            {
                ui->label_rez->hide();
                ui->label_err->setText("Ошибка в слагаемом 2");
                ui->label_err->setVisible(true);
            }
        }
        else
        {
            ui->label_rez->hide();
            ui->label_err->setText("Ошибка в слагаемом 1");
            ui->label_err->setVisible(true);
        }
    }

    if (ui->radioButton_sub->isChecked()) // выбрано вычитание
    {
        stroka=ui->lineEdit_opr1->text(); //счит введ слаг 1
        op1=stroka.toDouble(&fl1); //пробуем преобразовать
        if (fl1)
        {
            stroka=ui->lineEdit_opr2->text(); //счит введ слаг 2
            op2=stroka.toDouble(&fl1); //пробуем преобразовать
            if (fl1)
            {
                rez=op1-op2; //разность
                ui->label_err->hide(); //прячем сообщ об ошиб
                stroka.setNum(rez);  //знаки после зап чтоюы считались числа с е
                ui->label_rez->setText(stroka);
                ui->label_rez->show();// выводим сообщ с рез

                if (qIsInf(rez))
                {
                    ui->label_err->setText("Значение вышло за диапазон допустимых чисел");
                    ui->label_rez->setVisible(false);
                    ui->label_err->setVisible(true);
                }
            }
            else
            {
                ui->label_rez->hide();
                ui->label_err->setText("Ошибка в вычитаемом");
                ui->label_err->setVisible(true);
            }

        }
        else
        {
            ui->label_rez->hide();
            ui->label_err->setText("Ошибка в уменьшаемом");
            ui->label_err->setVisible(true);
        }
    }

    if (ui->radioButton_mul->isChecked()) // выбрано умножение
    {
        stroka=ui->lineEdit_opr1->text(); //счит введ множ 1
        op1=stroka.toDouble(&fl1); //пробуем преобразовать
        if (fl1)
        {
            stroka=ui->lineEdit_opr2->text(); //счит введ множ 2
            op2=stroka.toDouble(&fl1); //пробуем преобразовать
            if (fl1)
            {
                rez=op1*op2; //произведение
                ui->label_err->hide(); //прячем сообщ об ошиб
                stroka.setNum(rez);  //знаки после зап чтоюы считались числа с е
                ui->label_rez->setText(stroka);
                ui->label_rez->show();// выводим сообщ с рез

                if (qIsInf(rez))
                {
                    ui->label_err->setText("Значение вышло за диапазон допустимых чисел");
                    ui->label_rez->setVisible(false);
                    ui->label_err->setVisible(true);
                }
            }
            else
            {
                ui->label_rez->hide();
                ui->label_err->setText("Ошибка в множителе 1");
                ui->label_err->setVisible(true);
            }
        }
        else
        {
            ui->label_rez->hide();
            ui->label_err->setText("Ошибка в множителе 2");
            ui->label_err->setVisible(true);
        }
    }

    if (ui->radioButton_div->isChecked()) // выбрано умножение
    {
        stroka=ui->lineEdit_opr1->text(); //счит введ множ 1
        op1=stroka.toDouble(&fl1); //пробуем преобразовать
        if (fl1)
        {
            stroka=ui->lineEdit_opr2->text(); //счит введ множ 2
            op2=stroka.toDouble(&fl1); //пробуем преобразовать
            if (fl1)
            {
                    rez=op1/op2; //произведение
                    ui->label_err->hide(); //прячем сообщ об ошиб
                    stroka.setNum(rez);  //знаки после зап чтоюы считались числа с е
                    ui->label_rez->setText(stroka);
                    ui->label_rez->show();// выводим сообщ с рез

                    if (qIsInf(rez))
                    {
                        ui->label_err->setText("Значение вышло за диапазон допустимых чисел");
                        ui->label_rez->setVisible(false);
                        ui->label_err->setVisible(true);
                    }
            }
            else
            {
                ui->label_rez->hide();
                ui->label_err->setText("Ошибка в делимом");
                ui->label_err->setVisible(true);
            }
        }
        else
        {
            ui->label_rez->hide();
            ui->label_err->setText("Ошибка в делителе");
            ui->label_err->setVisible(true);
        }

    }
    if (ui->radioButton_sqrt->isChecked()) // выбрано кв корень
    {
        stroka=ui->lineEdit_opr1->text(); //счит введ слаг 1
        op1=stroka.toDouble(&fl1); //пробуем преобразовать
        if (fl1)
        {
            ui->lineEdit_opr2->text(); //счит введ слаг 2
            op2=stroka.toDouble(&fl1); //пробуем преобразовать
            if (fl1)
            {
                if(op1>=0) // подкор выраж всегда боль или равн 0
                {
                    double rez=sqrt(op1);
                    ui->label_err->hide(); //прячем сообщ об ошиб
                    stroka.setNum(rez);  //знаки после зап чтоюы считались числа с е
                    ui->label_rez->setText(stroka);
                    ui->label_rez->show();// выводим сообщ с рез

                    if (qIsInf(rez))
                    {
                        ui->label_err->setText("Значение вышло за диапазон допустимых чисел");
                        ui->label_rez->setVisible(false);
                        ui->label_err->setVisible(true);
                    }
                }
                else
                {
                    ui->label_rez->hide();
                    ui->label_err->setText("Ошибка в подкоренном выражении");
                    ui->label_err->setVisible(true);
                }
            }

        }
        else
        {
            ui->label_rez->hide();
            ui->label_err->setText("Ошибка в подкоренном выражении");
            ui->label_err->setVisible(true);
        }

    }
}
