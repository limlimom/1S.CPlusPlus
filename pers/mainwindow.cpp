#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->lineEdit_Points->setReadOnly(true); // блок изменинения только чтение
    ui->pushButton_Clear->click(); //вызов очистки

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Clear_clicked()
{
    // очищаем место резов
    ui->label_HP_Value->clear();
    ui->label_MP_Value->clear();
    ui->label_Att_Value->clear();
    ui->label_Def_Value->clear();
    ui->label_Atra_Value->clear();
    ui->label_Class_Value->clear();
    ui->label_ERROR->clear();

    points=25; //колва очков
    ui->lineEdit_Points->setText(QString::number(points));//перобразуем число в тексти зап его в lineedit

}


void MainWindow::on_pushButton_Create_clicked()
{
    QString name;
    int dlina;
    bool flag; //признак успешности генерации
    int str, dex, intel, luck, cha; // параметры персонажа

    name=ui->lineEdit_Name->text();
    dlina=name.length(); //проверка длинны имени

    if ((dlina<3)||(dlina>20))
    {
        flag=false;
        QMessageBox::warning(this,"Ошибка","Длинна имени должна быть от 3 до 20 символов.");
    }
    else
    {
        flag=true;
    }

    if (flag) // вместо создания множества условий
    {
        if ((!ui->radioButton_Sex_W->isChecked())&&(!ui->radioButton_Sex_m->isChecked()))
        {
            flag=false;
            QMessageBox::warning(this,"Ошибка","Пол не выбран");
        }
        else
        {
            flag=true;
        }
    }
    str=0;
    if (flag) // сила
    {
        str=ui->lineEdit_Str->text().toInt(&flag);
        if (!flag)
            QMessageBox::warning(this, "Ошибка", "Не верное значение пармаетра \"Сила\".");
        else
        {
            if((str<1)||(str>10))
            {
                flag=false;
                QMessageBox::warning(this, "Ошибка","\"Сила\" должна быть от 1 до 10 включительно." );
            }
        }
    }
    dex=0;
    if (flag)
    {
        dex=ui->lineEdit_Dex->text().toInt(&flag);
        if (!flag)
            QMessageBox::warning(this, "Ошибка", "Не верное значение пармаетра \"Ловкость\".");
        else
        {
            if((dex<1)||(dex>10))
            {
                flag=false;
                QMessageBox::warning(this, "Ошибка","\"Ловкость\" должна быть от 1 до 10 включительно." );
            }
        }

    }
    intel=0;
    if (flag)
    {
        intel=ui->lineEdit_Intel->text().toInt(&flag);
        if (!flag)
            QMessageBox::warning(this, "Ошибка", "Не верное значение пармаетра \"Интеллекта\".");
        else
        {
            if((intel<1)||(intel>10))
            {
                flag=false;
                QMessageBox::warning(this, "Ошибка","\"Интеллекта\" должна быть от 1 до 10 включительно." );
            }
        }

    }
    luck=0;
    if (flag)
    {
        luck=ui->lineEdit_Luck->text().toInt(&flag);
        if (!flag)
            QMessageBox::warning(this, "Ошибка", "Не верное значение пармаетра \"Удачи\".");
        else
        {
            if((luck<1)||(luck>10))
            {
                flag=false;
                QMessageBox::warning(this, "Ошибка","\"Удачи\" должна быть от 1 до 10 включительно." );
            }
        }

    }
    cha=0;
    if (flag)
    {
        cha=ui->lineEdit_Cha->text().toInt(&flag);
        if (!flag)
            QMessageBox::warning(this, "Ошибка", "Не верное значение пармаетра \"Очарования\".");
        else
        {
            if((cha<1)||(cha>10))
            {
                flag=false;
                QMessageBox::warning(this, "Ошибка","\"Очарование\" должна быть от 1 до 10 включительно." );
            }
        }

    }
    if (flag) // сумма очков
    {
        int sum = points- (str+dex+intel+luck+cha);
        ui->lineEdit_Points->setText(QString::number(sum));
        if (sum!=0)
        {
            flag=false;
            if (sum>0)
                QMessageBox::warning(this, "Ошибка", "Вы должны потратить все очки способностей.");
            else
                QMessageBox::warning(this, "Ошибка", "Вы не можете потратить больше очков способностей.");
        }
    }
    if (flag)
    {
        int hp, mp, att, def, atra;
        QString sex;
        if (ui->radioButton_Sex_W->isChecked())
        {
            sex = "Женский";
        }
        else if (ui->radioButton_Sex_m->isChecked())
        {
            sex = "Мужской";
        }

        hp=str+dex;
        mp=cha+dex+luck;
        att=str+dex+intel;
        def=intel+luck+str;
        atra=cha+mp;

        ui->label_HP_Value->setNum(hp);
        ui->label_MP_Value->setNum(mp);
        ui->label_Att_Value->setNum(att);
        ui->label_Atra_Value->setNum(atra);
        ui->label_Def_Value->setNum(def);
        if (ui->radioButton_Sex_W->isChecked())
        {
            ui->label_Cha->setText("Очарование");
        }
        else
        {
            ui->label_Cha->setText("Харизма");
        }
        //класс и привлекательность с учетом пола
    if(hp > 10 && mp > 8 && att > 11 && def > 4 && atra > 8)
    {
        if(sex == "Мужской")
        {
            ui->label_Class_Value->setText("Чародей");
        }
        else
        {
            ui->label_Class_Value->setText("Чародейка");
        }
    }
    if(hp > 3 && mp > 8 && att > 5 && def > 7 && atra > 15)
    {
        if(sex == "Мужской")
        {
            ui->label_Class_Value->setText("Соблазнитель");
        }
        else
        {
            ui->label_Class_Value->setText("Соблазнительница");
        }
        if(hp > 16 && mp > 8 && att > 16 && def > 15 && atra > 8)
        {
            if(sex == "Мужской")
            {
                ui->label_Class_Value->setText("Воин");
            }
            else
            {
                ui->label_Class_Value->setText("Воительница");
            }
        }
        if(hp > 10 && mp > 8 && att > 16 && def > 9 && atra > 10)
        {
            if(sex == "Мужской")
            {
                ui->label_Class_Value->setText("Лучник");
            }
            else
            {
                ui->label_Class_Value->setText("Лучница");
            }
        }
    }
    }
    else
    {
        ui->label_HP_Value->clear();
        ui->label_MP_Value->clear();
        ui->label_Att_Value->clear();
        ui->label_Def_Value->clear();
        ui->label_Atra_Value->clear();
        ui->label_Class_Value->clear();
    }

    if (ui->radioButton_Sex_W->isChecked())
    {
        ui->label_Cha->setText("Очарование");
    }
    else
    {
        ui->label_Cha->setText("Харизма");
    }

}

