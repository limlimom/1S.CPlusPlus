#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTabWidget>
#include <QTableWidgetItem>


bool isSorted(int a[], int n)
{
    while( --n > 0 )
        if(a[n] < a[n-1])
            return false;
    return true;
}

void shuffle(int a[], int n)
{
    for(int i=0; i < n; i++)
    {
        std::swap(a[i], a[rand()%n]);
    }
}

void bogosort(int a[], int n)
{

    while( !isSorted(a, n) )
        shuffle(a, n);
}


void bubblesort(int *num, int size)
{
    for (int  i=0; i<size-1; i++)
    {
        for (int j=(size-1); j>i; j--)
        {
            if (num[j-1]>num[j])
            {
                int temp=num[j-1];
                num[j-1]=num[j];
                num[j]=temp;
            }
        }
    }
}
void gnomesort(int n, int ar[])
{
    int i=0;
    int j=0;
    int vrem=0;
    while (i<n)
    {
        if((i==0)or(ar[i-1]<=ar[i]))
        {
            i=i+1;
        }
        else
        {
            j=i-1;
            vrem=ar[i];
            ar[i]=ar[j];
            ar[j]=vrem;
            i=i-1;
        }
    }
}

void brush(int *num, int size)
{
    int jump=size;
    double ju=jump;
    bool go=true;
    while ((ju>1)||(go==true))
    {
        if (ju>1)
        {
            ju=ju/1.247;
            jump=int(ju);

        }
        go=false;
        int i=0;

        while ((i+jump)<size)
        {

            if (num[i]>num[i+jump])
            {
                int temp=num[i];
                num[i]=num[i+jump];
                num[i+jump]=temp;
                go=true;
            }
            i=i+1;
        }
    }
}

void quicksort (int *num, int left, int right)
{
    int w;
    int x;
    int i=left;
    int j=right;
    x=num[(left+right)/2];
    do
    {
        while (num[i]<x)
            i++;
        while (x<num[j])
            j--;
        if (i<=j)
        {
            w=num[i];
            num[i]=num[j];
            num[j]=w;
            i++;
            j--;
        }
    } while (i<=j);
    if (left<j)
        quicksort(num,left,j);
    if (right>i)
        quicksort(num,i,right);
}



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->lineEditElem->setPlaceholderText("Enter the number of rows (from 1 to 200)");
    ui->pushButtonEnter->setEnabled(false);
    ui->labelMax->setVisible(0);
    ui->labelMin->setVisible(0);
    ui->pushButtonAverage->setVisible(0);
    ui->tableWidget->setVisible(0);
    ui->pushButtonMax->setVisible(0);
    ui->pushButtonMin->setVisible(0);
    ui->labelAverage->setVisible(0);
    ui->pushButtonRandom->setVisible(0);
    ui->comboBox->setVisible(0);
    ui->pushButtonDeleteD->setVisible(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_lineEditElem_textChanged(const QString &arg1)
{
    bool flag;
    QPalette y=ui->lineEditElem->palette();
    int r=arg1.toInt(&flag);
    if ((r>0)&&(r<201))
    {
        y.setColor(QPalette::Text, Qt::green);
        ui->pushButtonEnter->setEnabled(true);
    }
    else
    {
        y.setColor(QPalette::Text, Qt::red);
        ui->pushButtonEnter->setEnabled(false);
    }
    ui->lineEditElem->setPalette(y);
}

void MainWindow::on_pushButtonEnter_clicked()
{
    ui->tableWidget->setColumnCount(1);
    int razmer=ui->lineEditElem->text().toInt();
    ui->labelMax->setVisible(1);
    ui->labelMin->setVisible(1);
    ui->pushButtonAverage->setVisible(1);
    ui->tableWidget->setVisible(1);
    ui->pushButtonMax->setVisible(1);
    ui->pushButtonMin->setVisible(1);
    ui->labelAverage->setVisible(1);
    ui->pushButtonRandom->setVisible(1);
    ui->comboBox->setVisible(1);
    ui->tableWidget->setRowCount(razmer);
    ui->labelMax->clear();
    ui->labelMin->clear();
    ui->labelAverage->clear();
    ui->pushButtonDeleteD->setVisible(0);

    for (int i=0; i<ui->tableWidget->rowCount(); i++)
    {
        ui->tableWidget->clear();
    }
}

void MainWindow::on_pushButtonRandom_clicked()
{
    for (int i=0; i<ui->tableWidget->rowCount(); i++)
    {
        int new_item=rand();
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(new_item)));


    }

}

void MainWindow::on_pushButtonMax_clicked()
{
    int razmer=ui->tableWidget->rowCount();
    int mas[razmer];
    ui->labelMax->setHidden(false);
    for (int k=0; k<razmer; k++)
    {
        if (ui->tableWidget->item(k,0)==NULL)
        {
            QTableWidgetItem * new_item;
            new_item=new QTableWidgetItem;
            ui->tableWidget->setItem(k,0,new_item);
        }
    }


    for (int i=0;i<razmer;i++)
    {

        if (ui->tableWidget->item(i,0)==NULL)
        {
            QTableWidgetItem * new_item;
            new_item=new QTableWidgetItem;
            ui->tableWidget->setItem(i,0,new_item);
        }


        bool flag;
        mas[i]=ui->tableWidget->item(i,0)->text().toInt(&flag);
        if  (!flag)
        {
            ui->tableWidget->item(i,0)->setBackground(Qt::red);
            ui->tableWidget->scrollToItem(ui->tableWidget->item(i,0));
            ui->labelMax->setHidden(true);
        }
        int n_row=ui->tableWidget->rowCount();
        for (int j=0; j<n_row; j++)
        {
            bool yup;
            int hey=ui->tableWidget->item(j,0)->text().toInt(&yup);
            if (!yup)
            {
                ui->tableWidget->setCurrentCell(j,0);
                ui->tableWidget->scrollToItem(ui->tableWidget->item(j,0));
                break;
            }
        }

    }

    int max=mas[0];
    for (int i=0;i<razmer;i++)
    {
        if(mas[i]>max)
        {
            max=mas[i];
        }
    }
    ui->labelMax->setText(QString::number(max));

}

void MainWindow::on_pushButtonMin_clicked()
{
    int razmer=ui->tableWidget->rowCount();
    int mas[razmer];
    ui->labelMin->setHidden(false);

    for (int k=0; k<razmer; k++)
    {
        if (ui->tableWidget->item(k,0)==NULL)
        {
            QTableWidgetItem * new_item;
            new_item=new QTableWidgetItem;
            ui->tableWidget->setItem(k,0,new_item);
        }
    }

    for (int i=0;i<razmer;i++)
    {

        if (ui->tableWidget->item(i,0)==NULL)
        {
            QTableWidgetItem * new_item;
            new_item=new QTableWidgetItem;
            ui->tableWidget->setItem(i,0,new_item);
        }


        bool flag;
        mas[i]=ui->tableWidget->item(i,0)->text().toInt(&flag);
        if  (!flag)
        {
            ui->tableWidget->item(i,0)->setBackground(Qt::red);
            ui->tableWidget->scrollToItem(ui->tableWidget->item(i,0));
            ui->labelMin->setHidden(true);
        }
        int n_row=ui->tableWidget->rowCount();
        for (int j=0; j<n_row; j++)
        {
            bool yup;
            int hey=ui->tableWidget->item(j,0)->text().toInt(&yup);
            if (!yup)
            {
                ui->tableWidget->setCurrentCell(j,0);
                ui->tableWidget->scrollToItem(ui->tableWidget->item(j,0));
                break;
            }
        }


    }

    int min=mas[0];
    for (int i=0;i<razmer;i++)
    {
        if(mas[i]<min)
        {
            min=mas[i];
        }
    }
    ui->labelMin->setText(QString::number(min));
}

void MainWindow::on_pushButtonAverage_clicked()
{
    bool aga;
    float n_row=ui->tableWidget->rowCount();
    float sum=0;
    float kolichestvo=ui->tableWidget->rowCount();

    ui->labelAverage->setHidden(false);
    for (int k=0; k<n_row; k++)
    {
        if (ui->tableWidget->item(k,0)==NULL)
        {
            QTableWidgetItem * new_item;
            new_item=new QTableWidgetItem;
            ui->tableWidget->setItem(k,0,new_item);
        }
    }
    for (int i=0; i<n_row; i++)
    {

        if (ui->tableWidget->item(i,0)==NULL)
        {
            QTableWidgetItem * new_item;
            new_item=new QTableWidgetItem;
            ui->tableWidget->setItem(i,0,new_item);
        }

        sum+=ui->tableWidget->item(i,0)->text().toFloat(&aga);
        float average=sum/kolichestvo;
        ui->labelAverage->setNum(average);


        if (!aga)
        {
            ui->tableWidget->item(i,0)->setBackground(Qt::red);
            ui->labelAverage->setHidden(true);
            ui->tableWidget->scrollToItem(ui->tableWidget->item(i,0));
        }
        int n_row=ui->tableWidget->rowCount();
        for (int j=0; j<n_row; j++)
        {
            bool yup;
            int hey=ui->tableWidget->item(j,0)->text().toInt(&yup);
            if (!yup)
            {
                ui->tableWidget->setCurrentCell(j,0);
                ui->tableWidget->scrollToItem(ui->tableWidget->item(j,0));
                break;
            }
        }
    }

}

void MainWindow::on_tableWidget_cellChanged(int row, int column)
{
    if(ui->tableWidget->item(row,column)==NULL)
    {
        ui->tableWidget->setItem(row,column,new QTableWidgetItem(""));
    }
    bool flag;
    int a=ui->tableWidget->item(row,column)->text().toInt(&flag);
    if(flag)
    {
        ui->tableWidget->item(row,column)->setBackground(Qt::white);
        ui->comboBox->setVisible(1);
    }
    else
    {
        ui->comboBox->setVisible(0);
        ui->tableWidget->item(row,column)->setBackground(Qt::red);
        ui->labelMax->setHidden(1);
        ui->labelMin->setHidden(1);
        ui->labelAverage->setHidden(1);
        ui->pushButtonDeleteD->setVisible(0);
    }

}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    int razmer=ui->tableWidget->rowCount();
    int mas[razmer];
    for (int i=0; i<razmer; i++)
    {
        if(ui->tableWidget->item(i,0)==NULL)
        {
            ui->tableWidget->item(i,0)->setBackground(Qt::red);
            ui->tableWidget->scrollToItem(ui->tableWidget->item(i,0));
        }
        bool flag;
        mas[i]=ui->tableWidget->item(i,0)->text().toInt(&flag);
        if  (!flag)
        {
            ui->tableWidget->item(i,0)->setBackground(Qt::red);
            ui->tableWidget->scrollToItem(ui->tableWidget->item(i,0));
        }

    }
    switch(index)
    {
    case 0:
    {
        bubblesort(mas,razmer);
        for(int i=0; i<razmer; i++)
        {
            ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(mas[i])));
        }
        ui->pushButtonDeleteD->setVisible(1);
    }
        break;
    case 1:
    {
        gnomesort(razmer,mas);
        for(int i=0; i<razmer; i++)
        {
            ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(mas[i])));
        }
        ui->pushButtonDeleteD->setVisible(1);
    }
        break;
    case 2:
    {
        brush(mas, razmer);
        for(int i=0; i<razmer; i++)
        {
            ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(mas[i])));
        }
        ui->pushButtonDeleteD->setVisible(1);
    }
        break;
    case 3:
    {
        quicksort(mas, 0, razmer-1);
        for(int i=0; i<razmer; i++)
        {
            ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(mas[i])));
        }
        ui->pushButtonDeleteD->setVisible(1);
    }
        break;
    case 4:
    {
        bogosort(mas, razmer);
        for(int i=0; i<razmer; i++)
        {
            ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(mas[i])));
        }
        ui->pushButtonDeleteD->setVisible(1);

    }
        break;
    }
}

void MainWindow::on_pushButtonDeleteD_clicked()
{
    int razmer=ui->tableWidget->rowCount();
    int mas[razmer];
    for (int i=0;i<razmer;i++)
    {
        ui->tableWidget->item(i,0)->setBackground(Qt::white);

        if (ui->tableWidget->item(i,0)==NULL)
        {
            QTableWidgetItem * new_item;
            new_item=new QTableWidgetItem;
            ui->tableWidget->setItem(i,0,new_item);
        }

        bool flag;
        mas[i]=ui->tableWidget->item(i,0)->text().toInt(&flag);
        if  (!flag)
        {
            ui->tableWidget->item(i,0)->setBackground(Qt::red);
            ui->tableWidget->scrollToItem(ui->tableWidget->item(i,0));
            ui->labelMin->setHidden(true);
        }
        int n_row=ui->tableWidget->rowCount();
        for (int j=0; j<n_row; j++)
        {
            bool yup;
            int hey=ui->tableWidget->item(j,0)->text().toInt(&yup);
            if (!yup)
            {
                ui->tableWidget->setCurrentCell(j,0);
                break;
            }
        }
    }

    for (int i=0; i<razmer-1; i++)
    {
        for(int j=i; j<razmer-1; j++)
        {
            if (mas[j]!=NULL)
            {
                if(mas[i]==mas[j+1])
                {
                    mas[j+1]=NULL;
                }
            }
        }
    }

    int new_razmer=0;
    for(int i=0;i<razmer; i++)
    {
        if(mas[i]!=NULL)
            new_razmer++;
    }
    ui->tableWidget->setRowCount(new_razmer);
    int j=0;
    for (int i=0; i<razmer; i++)
    {
        if (mas[i]!=NULL)
        {
            ui->tableWidget->setItem(j,0, new QTableWidgetItem(QString::number(mas[i])));
            j++;
        }
    }


}
