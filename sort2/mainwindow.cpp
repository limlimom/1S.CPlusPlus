#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <qdebug.h>
#include <ctime>
#include <QFileInfo>
#include <QtMath>
#define MAX_SIZE 10000 // ограничение массива (директива препроцессора #define)


MainWindow::MainWindow(QWidget *parent) : //конструктор
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    srand( static_cast<unsigned int>(time(nullptr))); //привязка вычисления "рандомного" числа ко времени
    ui->spinBox->setMaximum(MAX_SIZE);
    no_auto_izmen=true;
    ui->lineEdit_val->setEnabled(false);
    ui->lineEdit_line->setEnabled(false);

}

MainWindow::~MainWindow() //деструктор
{
    delete ui;
}

void MainWindow::on_pushButton_num_clicked() //нажатие кнопки "number of elements"
{

    no_auto_izmen=false;
    //<инициализация переменных
    bool ok = false; //объявление логической перем. и присвоение первичного значения
    int size = ui->lineEdit_num->text().toInt(&ok);   //объявление переменной количества значений и присвоение первичного значения
    //инициализация переменных>

    if (!ok)  //проверка успешности чтения/преобразования количества значений
    {
        QMessageBox::information(this, "Ошибка", "Введите корректное число размера массива");//сообщение об ошибке
        return;                     //выход из процедуры при ошибке данных
    }
    if(size < 1) //проверка на отсутствие значений
    {
        QMessageBox::information(this, "Ошибка", "Массив не может быть меньше 1"); //сообщение об отсутствии значений
        return;                       //выход из процедуры при ошибке данных
    }
    if (size > MAX_SIZE)
    {
        QMessageBox::information(this,"Ошибка", "Максимальный размер массива - "  + QString::number(MAX_SIZE));
        return;
    }

    ui->tableWidget->clear();                     //сброс таблицы
    ui->tableWidget->setRowCount(size);           //устанока (вывод) случайного колич. строк
    ui->tableWidget->setColumnCount(1);           //установка количества исходных значений(столбцов)
    ui->lineEdit_min->clear();                    //сброс поля минимум
    ui->lineEdit_mid->clear();                    //сброс поля среднее
    ui->lineEdit_max->clear();                    //сброс поля максимум
    ui->lineEdit_line->clear();                   //сброс поля позиции
    ui->lineEdit_val->clear();                    //сброс поля колич.найденных
    deletedDoubles = false;

    ui->spinBox->setValue(size);

    no_auto_izmen=true;

}

void MainWindow::on_pushButton_min_clicked()   //нажатие кнопки "min"
{
    no_auto_izmen=false;
    int size = ui->tableWidget->rowCount(); //берем колич строк
    if (size == 0)    //проверка задан ли массив
    {
        QMessageBox::information(this, "Ошибка", "Массив не задан");
        return;
    }
    if (size == 1) //если всего одна строка
    {
        if(ui->tableWidget->item(0,0) == nullptr) //проверка на пустоту
        {
            QMessageBox::information(this, "Ошибка", "Нет элемента массива");
            return;
        }
        bool ok = false; //флаг для проверки преобразования
        int num = ui->tableWidget->item(0,0)->text().toInt(&ok);
        if (!ok)
        {
            QMessageBox::information(this, "Ошибка", "Нужно корректное число");
            return;
        }
        ui->lineEdit_min->setText(QString::number(num)); //вывод единственного минимального
        return;
    }
    if(ui->tableWidget->item(0,0) == nullptr) //проверка на пустоту
    {
        //QMessageBox::information(this, "Ошибка", "элемент массива" + QString::number(0+1) + "не задан");
        QMessageBox::information(this, "Ошибка", "Пустой массив" + QString::number(0+1) + "не задан");
        return;
    }
    bool ok = false; //флаг для проверки прреобразования
    int num = ui->tableWidget->item(0,0)->text().toInt(&ok);
    if (!ok)
    {
        QMessageBox::information(this, "Ошибка", "Нужно корректное число");
        return;
    }

    int min = num;
    for (int i=1; i<size; i++)   //цикл перебора значений и определения минимального
    {
        if(ui->tableWidget->item(i,0) == nullptr) //если пустота
        {
            //QMessageBox::information(this, "Ошибка", "элемент массива" + QString::number(i+1) + "не задан");
            QMessageBox::information(this, "Ошибка", "Пустой массив" + QString::number(i+1) + "не задан");
            return;
        }
        bool ok = false; //флаг для проверки преобразования
        int num = ui->tableWidget->item(i,0)->text().toInt(&ok);
        if (!ok)
        {
            QMessageBox::information(this, "Ошибка", "Нужно корректное число");
            return;
        }
        if (min>num ) //если предыдущее минимальное больше настоящего значения
        {
            min=num; //то, перезаписываем минимальное
        }
    }
    ui->lineEdit_min->setText(QString::number(min)); //преобразование и вывод минимального

    no_auto_izmen=true;
}

void MainWindow::on_pushButton_arr_clicked()  //нажатие "fill with random"
{
    no_auto_izmen=false;

    int size = ui->tableWidget->rowCount();
    if (size == 0)
    {
        //QMessageBox::information(this, "Ошибка", "Элемент массива" );
         QMessageBox::information(this, "Ошибка", "Пустой массив" );
        return;
    }
    for (int i=0;i<size; i++) //цикл по заполнению массива
    {
        int random_number = rand()%2000; //получаю рандомное значение 0...2000
        random_number -=1000; //вычитаю 1000, чтобы получить число в диапазоне -1000...+1000

        if (ui->tableWidget->item(i,0) == nullptr) //если память не выделена
        {
            ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(random_number)));
        }
        else //если память выделена
        {
            ui->tableWidget->item(i,0)->setText(QString::number(random_number)); //преобразование и вывод колич.строк
        }
    }
    ui->lineEdit_min->clear();                   //сброс поля минимум
    ui->lineEdit_mid->clear();                   //сброс поля среднее
    ui->lineEdit_max->clear();                       //сброс поля максимум

    sorted = false;
    deletedDoubles = false;
    no_auto_izmen=true;
}

void MainWindow::on_pushButton_mid_clicked()  //нажатие кнопки "mid"
{

    int size = ui->tableWidget->rowCount();
    // int mas[MAX_SIZE];

    if (size == 0)
    {
        QMessageBox::information(this, "Ошибка", "Массив не задан");
        return;
    }

    int *mas = nullptr;
    mas = new int [size];

    for (int i=0; i<size; i++)
    {
        if(ui->tableWidget->item(i,0) == nullptr)
        {
            QMessageBox::information(this, "Ошибка", "Элемент массива"+ QString::number(i+1) + "не задан");
            delete [] mas;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            return;

        }

        bool ok = false;
        int num = ui->tableWidget->item(i,0)->text().toInt(&ok);
        if (!ok)
        {
            QMessageBox::information(this, "Ошибка", "Элемент массива"+ QString::number(i+1) + "не корректный");
            delete [] mas;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            return;
        }
        mas [i] = num;
    }
    double summa = 0.0;
    for (int i=0; i<size; i++)  //цикл по вычислению суммы
    {
        summa += mas [i];
    }
    double sred = summa / static_cast<double>(size);  //вычисление среднего с помощью суммы
    ui->lineEdit_mid->setText(QString::number(sred)); //преобразование и вывод среднего

    delete [] mas; //удаление выделенной ранее памяти
    mas = nullptr; //добавление "nullptr", чтобы точно знать, что указатель пуст
}

void MainWindow::on_pushButton_rand_clicked() //функция генерация рандомного количества строк
{
    int newRowCount;
    newRowCount=1+rand()%(MAX_SIZE-1);
    ui->tableWidget->clear(); //сброс таблицы
    ui->tableWidget->setRowCount(newRowCount); //устанока (вывод) случайного колич. строк
    ui->tableWidget->setColumnCount(1); //установка количества исходных значений(столбцов)
    ui->lineEdit_min->clear(); //сброс поля min
    ui->lineEdit_mid->clear(); //сброс поля mid
    ui->lineEdit_max->clear(); //сброс поля max
    ui->lineEdit_num->clear(); //сброс поля number of elements
    ui->lineEdit_line->clear();//сброс поля позиции
    ui->lineEdit_val->clear(); //сброс поля колич.найденных
    ui->lineEdit_num->setText(QString::number(newRowCount)); //вывод измененного колич.строк
    sorted = false;
    deletedDoubles = false;

    ui->spinBox->setValue(newRowCount);

}

void MainWindow::on_pushButton_max_clicked()   //нажатие "максимум"
{
    int size = ui->tableWidget->rowCount();
    if (size == 0)
    {
        QMessageBox::information(this, "Ошибка", "Массив не задан");
        return;
    }
    if (size == 1)
    {
        if(ui->tableWidget->item(0,0) == nullptr)
        {
            QMessageBox::information(this, "Ошибка", "Нет элемента массива");
            return;
        }
        bool ok = false;
        int num = ui->tableWidget->item(0,0)->text().toInt(&ok);
        if (!ok)
        {
            QMessageBox::information(this, "Ошибка", "Нужно корректное число");
            return;
        }
        ui->lineEdit_max->setText(QString::number(num));
        return;
    }

    if(ui->tableWidget->item(0,0) == nullptr)
    {
        QMessageBox::information(this, "Ошибка", "элемент массива" + QString::number(0+1) + "не задан");
        return;
    }
    bool ok = false;
    int num = ui->tableWidget->item(0,0)->text().toInt(&ok);
    if (!ok)
    {
        QMessageBox::information(this, "Ошибка", "Нужно корректное число");
        return;
    }
    int max=num;
    for (int i=1; i<size; i++) //цикл перебора значений и определения максимального
    {
        if(ui->tableWidget->item(i,0) == nullptr)
        {
            QMessageBox::information(this, "Ошибка", "элемент массива" + QString::number(i+1) + "не задан");
            return;
        }
        bool ok = false; //флаг для проверки успешности преобразования
        int num = ui->tableWidget->item(i,0)->text().toInt(&ok);
        if (!ok)
        {
            QMessageBox::information(this, "Ошибка", "Нужно корректное число");
            return;
        }
        if (max<num) //если максимум меньше настоящего значения
        {
            max=num;//то перезаписываем максимальное
        }
    }
    ui->lineEdit_max->setText(QString::number(max));  //преобразование и вывод максимального
}

void MainWindow::on_pushButton_bubble_clicked() //сортировка Пузырек
{
    int size = 0;
    size = ui->tableWidget->rowCount();
    if(size<=0)
    {
        QMessageBox::information(this, "Ошибка", "Массив отсутствует");
        return;
    }

    double *mas = nullptr;    //создание указателя
    mas = new double [size]; //выделение памяти размера size для массива mas

    bool flagError = false;
    getMassive(mas,size,flagError);
    if (!flagError) // == false, значит ошибка
    {
        return;
    }
    // СОРТИРОВКА

    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (mas[j] > mas[j + 1])
            {
                // меняем элементы местами
                double temp = mas[j];
                mas[j] = mas[j + 1];
                mas[j + 1] = temp;
            }
        }
    }
    // *********

    setMassive(mas, size); //вывод массива
    ui->lineEdit_line->clear();

    sorted = true;

    delete [] mas; //удаление выделенной ранее памяти
    mas = nullptr; //добавление "nullptr", чтобы точно знать, что указатель пуст
}

void MainWindow::getMassive(double *mas, int &size, bool &ok) //функция для проверки массива
{
    {
        if (size <= 0) //если колич строк мньше или равно нулю
        {
            QMessageBox::warning(this,"ошибка","нет строк");
            ok = false;
            return;
        }

        for (int i=0;i<size ;i++ ) //проверка строк на пустоту
        {
            if (ui->tableWidget->item(i,0)==nullptr)
            {
                QMessageBox::warning(this,"ошибка","Необходимо заполнить строки");
                ok = false;
                return;
            }
            QString itemText = ui->tableWidget->item(i,0)->text();
            ok = false;
            double number = itemText.toDouble(&ok);
            if (!ok)
            {   //ui->spinBox->setValue(0); //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                QMessageBox::warning(this,"ошибка","некорректные значения");
                ok = false;
                return;
            }
            mas[i] = number;
        }

    }
    ok = true;
}

void MainWindow::setMassive(double *mas, int size) //цикл для вывода отсортированного массива
{
    for  (int i=0; i<size; i++)
    {
        QString itenText;
        itenText.setNum(mas[i]);
        ui->tableWidget->item(i,0)->setText(itenText);
    }
}

void MainWindow::quicksort(double *mas, int size) //быстрая сортировка
{
    //Указатели в начало и в конец массива
    int i = 0;
    int j = size - 1;

    //Центральный элемент массива
    double mid = mas[size / 2];

    //Делим массив
    do {
        //Пробегаем элементы, ищем те, которые нужно перекинуть в другую часть
        //В левой части массива пропускаем(оставляем на месте) элементы, которые меньше центрального
        while(mas[i] < mid)
        {
            i++;
        }
        //В правой части пропускаем элементы, которые больше центрального
        while(mas[j] > mid)
        {
            j--;
        }

        //Меняем элементы местами
        if (i <= j) {
            double tmp = mas[i];
            mas[i] = mas[j];
            mas[j] = tmp;

            i++;
            j--;
        }
    } while (i <= j);


    //Рекурсивные вызовы, если осталось, что сортировать
    if(j > 0) {
        //"Левый кусок"
        quicksort(mas, j + 1);
    }
    if (i < size) {
        //"Правый кусок"
        quicksort(&mas[i], size - i);
    }
}

void MainWindow::sortgnome(double *mas, int size) //Гномья сортировка
{
    int i = 0;
    while (i < size) //продолжительный цикл с условием
    {
        if (i == 0 || mas[i - 1] <= mas[i]) ++i;
        else
        {
            double tmp = mas[i];
            mas[

                    i] = mas[i - 1];
            mas[i - 1] = tmp;
            --i;
        }
    }
}


bool MainWindow::correct(double *arr, int size)
{
    for (int  i = 0; i<size-1; i++)
    {
        if (arr[i] > arr[i+1])
        {
            return false;
        }
    }
    return true;
}

void MainWindow::shuffle(double *arr, int size) //перебор
{
    for (int  i = 0; i<size-1; i++)
    {
        std::swap(arr[i], arr[(rand() % size)]);
    }
}

void MainWindow::bogoSort(double *arr, int size) // обезьянья сортировка
{
    bool ok = false;
    for (int  i = 0; i<10000000; i++)
    {
        shuffle(arr, size);
        if (correct(arr, size))
        {
            ok = true;
            break;
        }
    }
    if (ok)
    {
        setMassive(arr, size);
    }
    else {
        QMessageBox::warning(this, "Ошибка","Не удалось отсортировать");
        return;
    }
}

void MainWindow::sortbrush(double *mas, int size)  // сортировка Расческой
{
    {
        double factor = 1.2473309; // фактор уменьшения
        int step = size - 1; // шаг сортировки
        while (step >= 1)
        {
            for (int i = 0; i + step < size; i++)
            {
                if (mas[i] > mas[i + step])
                {
                    std::swap(mas[i], mas[i + step]);
                }
            }
            step /= factor;
        }
    }
}

void MainWindow::on_pushButton_quick_clicked() //функция быстрой сортировки
{
    int size = 0;
    size = ui->tableWidget->rowCount();
    if(size<=0)
    {
        QMessageBox::information(this, "Ошибка", "Массив отсутствует");
        return;
    }
    double *mas = nullptr;    //создание указателя
    mas = new double [size]; //выделение памяти размера size для массива mas
    bool flagError = false;
    getMassive(mas,size,flagError);
    if (!flagError) // == false, значит ошибка
    {
        return;
    }
    quicksort(mas, size); //быстрая сортировка
    setMassive(mas, size); //вывод массива
    ui->lineEdit_line->clear();
    sorted = true;
    delete [] mas; //удаление выделенной ранее памяти
    mas = nullptr; //добавление "nullptr", чтобы точно знать, что указатель пуст

}

void MainWindow::on_pushButton_gnome_clicked() //функция гномьей сортировки
{
    int size = 0;
    size = ui->tableWidget->rowCount();
    if(size<=0)
    {
        QMessageBox::information(this, "Ошибка", "Массив отсутствует");
        return;
    }
    double *mas = nullptr;    //создание указателя
    mas = new double [size]; //выделение памяти размера size для массива mas
    bool flagError = false;
    getMassive(mas,size,flagError);
    if (!flagError) //false, значит ошибка
    {
        return;
    }
    sortgnome(mas, size);//гномья сортировка
    setMassive(mas, size); //вывод массива
    ui->lineEdit_line->clear();
    sorted = true; //отсортировано
    delete [] mas; //удаление выделенной ранее памяти
    mas = nullptr; //добавление "nullptr", чтобы точно знать, что указатель пуст

}

void MainWindow::on_pushButton_brush_clicked() //функция для сортировки "раческа"
{
    int size = 0;
    size = ui->tableWidget->rowCount();
    if(size<=0)
    {
        QMessageBox::information(this, "Ошибка", "Массив отсутствует");
        return;
    }
    double *mas = nullptr;    //создание указателя
    mas = new double [size]; //выделение памяти размера size для массива mas
    bool flagError = false;
    getMassive(mas,size,flagError);
    if (!flagError) // == false, значит ошибка
    {
        return;
    }
    sortbrush(mas,size); //сортировка расчёска
    setMassive(mas, size); //вывод массива
    ui->lineEdit_line->clear();
    sorted = true;
    delete [] mas; //удаление выделенной ранее памяти
    mas = nullptr; //добавление "nullptr", чтобы точно знать, что указатель пуст

}


void MainWindow::on_pushButton_bogo_clicked() //функция обезьяньей сортировки
{
    int size = 0;

    size = ui->tableWidget->rowCount();
    if(size<=0)
    {
        QMessageBox::information(this, "Ошибка", "Массив отсутствует");
        return;
    }
    double *mas = nullptr;    //создание указателя
    mas = new double [size]; //выделение памяти размера size для массива mas
    bool flagError = false;
    getMassive(mas,size,flagError);
    if (!flagError) //false, значит ошибка
    {
        return;
    }
    if (size > 5)
    {
        QMessageBox::warning(this,"Ошибка","Можно использовать для массива не более 5 элементов");
        return;
    }
    bogoSort(mas,size); //обезьянья сортировка
    ui->lineEdit_line->clear();
    sorted = true; //отсортировано
    delete [] mas; //удаление выделенной ранее памяти
    mas = nullptr; //добавление "nullptr", чтобы точно знать, что указатель пуст

}


void MainWindow::on_pushButton_del_clicked() //функция для удаления дубликатов
{
    int size = ui->tableWidget->rowCount(); //берем количество строк из таблицы
    if (size == 0) //если количество строк нулевое
    {
        //QMessageBox::information(this, "Ошибка", "Элемент массива" );
         QMessageBox::information(this, "Ошибка", "Пустой массив" );
        return;
    }

    double *mas = nullptr;    //создание указателя
    mas = new double [size]; //выделение памяти размера size для массива mas

    bool flagError = false;
    getMassive(mas,size,flagError);

    if (!flagError) //false, значит ошибка
    {
        return;
    }

    double *maswithoutrepeat = nullptr; //добавление "nullptr", чтобы точно знать, что указатель пуст
    maswithoutrepeat = new double [size]; //выделение памяти

    int sizeBezPovtorov = 0;
    for (int i= 0; i < size; i++)
    {
        bool exist_element = false;
        for (int j=0; j<sizeBezPovtorov; j++)
        {
            if(abs(maswithoutrepeat[j]-mas[i])<=0.0001) // если элемент есть в массиве без повторов
            {
                exist_element = true;
                break;
            }
        }
        if (!exist_element) //в массиве без повтора элемента нет
        {
            maswithoutrepeat[sizeBezPovtorov] = mas[i];
            sizeBezPovtorov++;
        }
    }
    ui->tableWidget->clear(); //очищаем таблицу
    ui->tableWidget->setRowCount(sizeBezPovtorov); //задаем новое колич сток
    for (int i = 0; i < sizeBezPovtorov; i++) //цикл для вывода эл с проверкой
    {
        if (ui->tableWidget->item(i,0) == nullptr) //если память не выделена
        {
            ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(maswithoutrepeat[i])));
        }
        else //если память выделена
        {
            ui->tableWidget->item(i,0)->setText(QString::number(maswithoutrepeat[i])); //преобразование и вывод колич.строк
        }
    }
    size = ui->tableWidget->rowCount(); //задаем колич строк
    ui->lineEdit_num->setText(QString::number(size)); //вывод измененного колич.строк
    deletedDoubles = true; // сохранение удаления дкбликатов

    delete [] mas; //удаление выделенной ранее памяти
    mas = nullptr; //добавление "nullptr", чтобы точно знать, что указатель пуст

    delete [] maswithoutrepeat; //удаление выделенной ранее памяти
    maswithoutrepeat = nullptr;//добавление "nullptr", чтобы точно знать, что указатель пуст
}

void MainWindow::on_pushButton_search_clicked() //функция поиска данных о заданном элементе
{
    bool ok = false; //флаг для проверки успешности преобразования
    double searchNumber = ui->lineEdit_search->text().toDouble(&ok);
    if (!ok)
    {
        QMessageBox::warning(this, "Ошибка", "введите корректное число");
        return;
    }
    int size = ui->tableWidget->rowCount();
    if (size == 0)
    {
        //QMessageBox::information(this, "Ошибка", "Элемент массива" );
        QMessageBox::information(this, "Ошибка", "Пустой массив" );
        return;
    }

    double *mas=nullptr;
    mas = new double [size];

    bool flagError = false;
    size = ui->tableWidget->rowCount();
    // mas = new double [size] ;
    getMassive(mas,size,flagError);

    if (!flagError) // == false, значит ошибка
    {
        delete [] mas;
        mas = nullptr;
        return;
    }

    int count = 0; // сколько совпадений
    QString linesNumbers = "";

    if (!sorted)  // если не сортирован
    {
        QMessageBox::information(this, "Предупреждение", "массив не сортирован, испоользуется перебор" );

        for (int i = 0; i < size; ++i)
        {
            if (abs((mas[i]-searchNumber)) <= 0.0001)
            {
                count++;
                if (!linesNumbers.isEmpty())
                {
                    linesNumbers.append(", ");
                }
                linesNumbers.append(QString::number(i+1));
            }
        }
        if (count == 0)
        {
            ui->lineEdit_val->setText("не найдено");
            ui->lineEdit_line->setText("не найдено");

        }
        else
        {
            QString countText;
            countText.setNum(count);
            ui->lineEdit_val->setText(countText);
            ui->lineEdit_line->setText(linesNumbers);
        }
    }
    else
    {
        int size_search=size;
        int granLeft = 0;
        int grandRihgt = size_search;
        size_search = grandRihgt - granLeft;
        int seredina =((size_search)/2)+granLeft;

        while ((abs(mas[seredina] - searchNumber)>0.0001) && (size_search > 1))
        {
            if (mas[seredina] > searchNumber)
            {
                grandRihgt = seredina;
            }
            else
            {
                granLeft = seredina;
            }
            size_search = grandRihgt - granLeft;
            seredina =((size_search)/2)+granLeft;

        }
        if ( size_search == 0)
        {
            ui->lineEdit_val->setText("не найдено");
            ui->lineEdit_line->setText("не найдено");
        }
        else
        {
            count = 1; // найдено одно число
            if (deletedDoubles) // если дубликаты удалены
            {
                ui->lineEdit_val->setText("1");
                ui->lineEdit_line->setText(QString::number(seredina));
            }
            else
            {
                linesNumbers = QString::number(seredina+1); //внос номера строки в которой содерж найденный лемент
                int i = 0;
                if (seredina>0)
                {
                    i = seredina-1;
                }
                while (i>=0) // добавка дубликатов слева от середины
                {
                    if(abs(mas[i] - searchNumber)<=0.0001)
                    {
                        count++;
                        QString lineNum;
                        lineNum.setNum(i+1);
                        linesNumbers = lineNum + "," + linesNumbers;
                    }
                    else
                    {
                        break;
                    }
                    i--;
                }
                if (seredina< size-1)
                {
                    i = seredina + 1;
                }
                while (i<size) // добавка дубликатов слева от середины
                {
                    if (abs((mas[i]-searchNumber)) <= 0.0001)
                    {
                        count++;
                        QString lineNum;
                        lineNum.setNum(i+1);
                        linesNumbers =linesNumbers  + "," +lineNum ;
                    }
                    else
                    {
                        break;
                    }
                    i++;
                }
                QString countText;
                countText.setNum(count);
                ui->lineEdit_val->setText(countText); //выводим количество значений в массиве
                ui->lineEdit_line->setText(linesNumbers);//выводим колич строк с элементами
            }
        }
    }
    delete [] mas; //очищаем выделенную память
    mas = nullptr; //задаем, что массив nullptr
}


void MainWindow::on_tableWidget_itemChanged(QTableWidgetItem *item)
{
    bool ok = false; //флаг для проверки преобразования
    double num = item->text().toDouble(&ok); //преобразование к Double
    sorted = false;
    if (!ok) //если преобразование неудачное
    {
        deletedDoubles = false;
        return;
    }
    deletedDoubles = false;
    ui->lineEdit_min->clear(); //сброс поля min
    ui->lineEdit_mid->clear(); //сброс поля mid
    ui->lineEdit_max->clear(); //сброс поля max
    ui->lineEdit_line->clear();//сброс поля lines with given number
    ui->lineEdit_val->clear(); //сброс поля number of values in array

    Q_UNUSED(num);

}

void MainWindow::on_spinBox_valueChanged(int arg1) //функция для работы со spinBox
{
    ui->tableWidget->setRowCount(arg1); //задаем в таблицу количество строк из spinBox
    ui->tableWidget->setColumnCount(1); //выбираем колич столбцов
    ui->lineEdit_num->setText(QString::number(arg1));//выводим значение из spinBox в lineEdit_element
}

void MainWindow::on_pushButton_savetxt_clicked() // функция сохранения данных в txt
{

    int size = ui->tableWidget->rowCount(); //берем колич строк из таблицы
    if (size == 0) //если колич строк нулевое
    {
        QMessageBox::information(this, "Ошибка", "Нельзя сохранить пустоту" );
        return;
    }

    for (int i=0;i<size;i++) //Цикл прохода по всем элементам
    {
        if (ui->tableWidget->item(i,0)==nullptr) //Если ячейка не инициализирована
        {
            QMessageBox::warning(this,"Ошибка","Нельзя сохранить пустые ячейки"); //Сообщение об ошибке
            return;
        }
    }
    double *mas = nullptr;    //создание указателя
    mas = new double [size]; //выделение памяти размера size для массива mas
    bool flagError = false;
    getMassive(mas,size,flagError);

    if (!flagError) // == false, значит ошибка
    {
        return;
    }

    QString fileName; //Путь к файлу

    if ((!(size == 0)) ||flagError) //если ячейки не пустые
    {
        fileName=QFileDialog::getSaveFileName(this,tr("Сохранить как .txt"),QDir::currentPath(),tr("Text files (*.txt)"));
        if (fileName.isEmpty()) //Если файл не выбран
        {
            QMessageBox::warning(this,"Ошибка","Файл не выбран"); //Сообщение об ошибке
            return;
        }
        else //Если файл выбран
        {
            QFile file;
            file.setFileName(fileName); //Установка названия файла
            file.open(QIODevice::WriteOnly); //Открыть только для записи

            QString str;
            int size=ui->spinBox->value(); //Количество элементов
            str.setNum(size); //Установка размера

            str.append("\n"); //Перенос строки

            file.write(str.toUtf8()); //Запись в файл

            for (int i=0;i<size;i++) //Цикл прохода по всем элементам
            {
                if (ui->tableWidget->item(i,0)==nullptr) //Если ячейка не инициализирована
                {
                    QTableWidgetItem * ti;
                    ti = new QTableWidgetItem; //Создание новой ячейки
                    ui->tableWidget->setItem(i,0,ti);
                }
                str=ui->tableWidget->item(i,0)->text(); //Значение в i'ой ячейке
                str.append("\n"); //Перенос строки

                file.write(str.toUtf8()); //Запись в файл
            }
            QStringList parts = fileName.split("/");
            QString lastBit = parts.at(parts.size()-1); //Название файла
            setWindowTitle(lastBit); //Изменение названия окна
            currentFile = fileName; //Текущий файл
            fl1 = true;
            file.close(); //Закрытие окна
        }
    }
    else
    {
        QMessageBox::warning(this,"Ошибка","Все ячейки должны быть заполнены");
        return;
    }

    delete [] mas; //удаление выделенной ранее памяти
    mas = nullptr; //добавление "nullptr", чтобы точно знать, что указатель пуст
}

void MainWindow::on_pushButton_opentxt_clicked() //функция открытия файла txt
{
    QString fileName; //путь к файлу
    fileName=QFileDialog::getOpenFileName(this,tr("Открыть .txt"),QDir::currentPath(),tr("Text files (*.txt)"));

    if (fileName.isEmpty()) //Если файл не выбран
    {
        QMessageBox::warning(this,"Ошибка","Файл не выбран"); //Сообщение об ошибке
        return;
    }
    else //если файл выбран
    {
        if(!fileName.endsWith(".txt"))
        {
            QMessageBox::warning(this,"Ошибка","Это не txt файл");
            return;
        }
        QFile file;
        file.setFileName(fileName); //Установка названия файла
        file.open(QIODevice::ReadOnly); //Открыть только для чтения
        if(file.size() <= 0)
        {
            QMessageBox::warning(this,"Ошибка","Файл пустой");
            return;
        }
        QString str;
        QByteArray ba;
        bool flag;
        int size;
        ba=file.readLine(); //Чтение значения количества элементов
        str.append(ba); //Добавление значения количества элементов
        str.remove("\n"); //Удаление переноса строки
        size=str.toInt(&flag); //Проверка значения количества элементов

        if (!flag) //Если значение количества элементов не из диапазона int
        {
            QMessageBox::warning(this,"Ошибка","Неверный формат файла");
        }
        else
        {
            if(size <=0)
            {  ui->spinBox->setValue(0);
                file.close(); //Закрытие окна
                QMessageBox::warning(this,"Ошибка","Неверный размер");
                //Размер
                return;
            }
            ui->spinBox->setValue(size); //Установка количества ячеек
            int kol=0;
            for (int i=0;i<size and !file.atEnd();i++) //Цикл прохода по всем элементам
            {
                kol++;
                if (ui->tableWidget->item(i,0)==nullptr) //Если ячейка не инициализирована
                {
                    QTableWidgetItem * ti;
                    ti = new QTableWidgetItem; //Создание новой ячейки
                    ui->tableWidget->setItem(i,0,ti);
                }
                ba=file.readLine(); //Чтение строки
                str.clear(); //Очистка значения
                str.append(ba); //Добавление значения
                str.remove("\n"); //Удаление переноса строки
                ui->tableWidget->item(i,0)->setText(str); //Запись значения в ячейку
            }
            if(kol != size) //если нет соответствия
            { ui->spinBox->setValue(0);
                file.close(); //Закрытие окна
                QMessageBox::warning(this,"Ошибка","Нет соответствия количества элементов");
                //Указанный размер меньше фактических элементов
                return;
            }


            int size = ui->tableWidget->rowCount(); //берем колич строк из таблицы
            if (size == 0) //если колич строк нулевое
            {
                QMessageBox::information(this, "Ошибка", "Нулевое колич строк" );
                return;
            }

            double *mas = nullptr;    //создание указателя
            mas = new double [size]; //выделение памяти размера size для массива mas

            bool flagError = false;
            getMassive(mas,size,flagError); //выполнение функции по проверке ячеек массива на корректность данных

            if (!flagError) // == false, значит ошибка
            {
                ui->spinBox->setValue(0); //сбрасываем таблицу
                return;
            }

            if(!file.atEnd())
            { ui->spinBox->setValue(0);
                file.close(); //Закрытие окна
                QMessageBox::warning(this,"Ошибка","Нет соответствия количества элементов");        
               return;
            }
            QStringList parts = fileName.split("/");
            QString lastBit = parts.at(parts.size()-1); //Название файла
            setWindowTitle(lastBit); //Изменение названия окна
            currentFile = fileName; //Текущий файл
            fl1 = true; //ставим что сохранение было
        }
        file.close(); //Закрытие окна
    }
}

void MainWindow::on_pushButton_savebin_clicked() //бинарное сохранение
{

    int size = ui->tableWidget->rowCount(); //берем количество строк из таблицы
    if (size == 0) //если количество строк нулевое
    {
        QMessageBox::information(this, "Ошибка", "Нельзя сохранить пустоту" );
        return;
    }
    for (int i=0;i<size;i++) //Цикл прохода по всем элементам
    {
        if (ui->tableWidget->item(i,0)==nullptr) //Если ячейка не инициализирована
        {
            QMessageBox::warning(this,"Ошибка","нельзя сохранить пустые ячейки"); //Сообщение об ошибке
            return;
        }
    }
    double *mas = nullptr; //создание указателя
    mas = new double [size]; //выделение памяти размера size для массива mas
    bool flagError = false; //создаем флаг для последующей проверки
    getMassive(mas,size,flagError); //выполнение функции по проверке ячеек массива на корректность данных
    if (!flagError) // == false, значит ошибка
    {
        return;
    }

    QString fileName; //путь к файлу
    if ((!(size == 0)) ||flagError) //если ячейки не пустые //если нет пустоты
    {
        fileName=QFileDialog::getSaveFileName(this,tr("Сохранить bin"),QDir::currentPath(),tr("Binary files (*.bin)")); //откуда открываем файл
        if (fileName.isEmpty()) //Если файл не выбран
        {
            QMessageBox::warning(this,"Ошибка","Файл не выбран"); //Сообщение об ошибке
        }
        else //Если файл выбран
        {
            QFile file;
            file.setFileName(fileName); //Установка названия файла
            file.open(QIODevice::WriteOnly); //Открыть только для записи

            char*mas;
            int sz_int=sizeof(int);
            mas = new char[sz_int];
            int size=ui->spinBox->value(); //Количество элементов
            memcpy(mas,&size,size_t(sz_int));
            file.write(mas,sz_int); //Запись
            for (int i=0;i<size;i++) //Цикл прохода по всем элементам
            {
                if (ui->tableWidget->item(i,0)==nullptr) //Если ячейка не инициализирована
                {
                    QTableWidgetItem * ti;
                    ti = new QTableWidgetItem; //Создание новой ячейки
                    ui->tableWidget->setItem(i,0,ti);
                }
                int tmp=ui->tableWidget->item(i,0)->text().toInt(); //Преобразование в int
                memcpy(mas,&tmp,size_t(sz_int));
                file.write(mas,sz_int); //Запись в файл
            }
            currentFile = fileName; //Текущий файл
            fl1 = true;//ставим что сохранение было

            file.close(); //Закрытие окна
            delete [] mas;
        }
    }
    else
    {   //ui->tableWidget->setRowCount(0);//!!!!
        ui->spinBox->setValue(0);
        QMessageBox::warning(this,"Ошибка","Все ячейки должны быть заполнены");
        return;
    }
}

void MainWindow::on_pushButton_openbin_clicked() //открытие файла bin
{
    QString fileName; //Путь к файлу
    fileName=QFileDialog::getOpenFileName(this,tr("Открыть bin"),QDir::currentPath(),tr("Binary files (*.bin)")); //откуда открываем файл

    if (fileName.isEmpty()) //Если файл не выбран
    {
        QMessageBox::warning(this,"Ошибка","Файл не выбран"); //Сообщение об ошибке
        return;
    }
    else //если файл выбран
    {
        if(!fileName.endsWith(".bin"))
        {
            QMessageBox::warning(this,"Ошибка","Это не bin файл");
            return;
        }

//    if (fileName.isEmpty()) //Если файл не выбран
//    {
//        QMessageBox::warning(this,"Ошибка","Файл не выбран"); //Сообщение об ошибке
//    }
//    else //Если файл выбран
//    {


        QFile file;
        bool flag;
        file.setFileName(fileName); //Установка названия файла
        file.open(QIODevice::ReadOnly); //Открыть только для чтения
        int file_size = file.size(); //получаем размер файла в байтах


        if (!flag) //Если значение количества элементов не из диапазона int
        {
            QMessageBox::warning(this,"Ошибка","Неверный формат файла");
        }
        else
        {
            if(file_size <=0)
            {  ui->spinBox->setValue(0);
                file.close(); //Закрытие окна
                QMessageBox::warning(this,"Ошибка","Неверный размер");
                //Размер
                return;
            }
//        if(file_size <=0)
//        {
//            QMessageBox::warning(this, "Ошибка", "Файл пустой");
//            return;
//        }
//        int ost=file_size%4; //находим остаток
//        if (ost !=0) //если остаток не равен нулю
//        {
//            QMessageBox::warning(this, "Ошибка", "Файл поврежд"); //ошибка при несоответствии кратности размера 4
//            return;
//        }

        char*mas;
        int sz_int=sizeof(int);
        mas = new char[sz_int];
        int size;              //Инициализация размера массива !!! тут получаем колич строк
        file.read(mas,sz_int); //Чтение
        memcpy(&size,mas,size_t(sz_int));
        int strochek=(file_size/4)-1; //получаем количество зашифрованных строчек.

        if(strochek!=size) //если есть несоответствие строчек
        {
            QMessageBox::warning(this, "Ошибка", "Файл поврежден"); //эту ошибку выводим когда есть отличия между фактическим размером строк и считанным
            return;
        }
        ui->spinBox->setValue(size); //Установка количества ячеек
        for (int i=0;i<size;i++) //Цикл прохода по всем элементам
        {
            if (ui->tableWidget->item(i,0)==nullptr) //Если ячейка не инициализирована
            {
                QTableWidgetItem * ti;
                ti = new QTableWidgetItem; //Создание новой ячейки
                ui->tableWidget->setItem(i,0,ti);
            }
            int tmpi;
            file.read(mas,sz_int); //Чтение
            memcpy(&tmpi,mas,size_t(sz_int));
            ui->tableWidget->item(i,0)->setText(QString::number(tmpi)); //Запись значения в ячейку
        }
        currentFile = fileName; //Текущий файл
        fl1 = true;
        file.close(); //Закрытие окна
        delete [] mas; //освобождаем выделенную память
    }
}


