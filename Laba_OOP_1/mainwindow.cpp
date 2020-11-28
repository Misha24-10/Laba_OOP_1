#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "tablecell.h"
#include "tablecollection.h"
#include "tablecellfunction.h"
#include <QRegExpValidator>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Table_ = nullptr;
    QRegExp int_exp("[0-9]*");
    ui->coll_n->setValidator(new QRegExpValidator(int_exp, this));
    ui->lineEdit_3->setValidator(new QRegExpValidator(int_exp, this));

    ui->value_col->setValidator(new QRegExpValidator(int_exp, this));
    ui->value_row->setValidator(new QRegExpValidator(int_exp, this));

    ui->value_col_func_st->setValidator(new QRegExpValidator(int_exp, this));
    ui->value_row_func_st->setValidator(new QRegExpValidator(int_exp, this));
    ui->value_row_func_end->setValidator(new QRegExpValidator(int_exp, this));
    ui->value_col_func_end->setValidator(new QRegExpValidator(int_exp, this));
    ui->value_col_2->setReadOnly(true);
    ui->value_col_3->setReadOnly(true);
    ui->value_col_4->setReadOnly(true);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete Table_;
}



void MainWindow::on_create_table_clicked()
{
    if( ui->coll_n->text() != "" || ui->lineEdit_3->text() != "") {


        int row = ui->coll_n->text().toInt();
        int col = ui->lineEdit_3->text().toInt();
        if(Table_ != nullptr){
            delete  Table_;

        }
        this->Table_ = new TableCollection(row,col);
    }
    else{
        QMessageBox::critical(this, "Ошибка", "Введите данные еще раз");
    }

}


void MainWindow::on_pushButton_clicked()
{
    if( ui->coll_n->text() == "" || ui->lineEdit_3->text() == "") {
        QMessageBox::critical(this, "Ошибка", "Введите данные еще раз");
    }
    {
        if( ui->value_col->text() == "" || ui->value_row->text() == "") {
            QMessageBox::critical(this, "Ошибка", "Введите данные еще раз");
        }
        else
        {
            int n = ui->value_row->text().toInt();
            int m = ui->value_col->text().toInt();
            if(n >= Table_->getLength() || m >= Table_->getWidth()){
                QMessageBox::critical(this, "Ошибка", "Выход за пределы таблицы");
            }
            else{
                if((*Table_).getTableCel(n,m) && (*Table_).getTableCel(n,m)->getType() == 0 ) {
                    if(true) {
                        float s= Table_->getTableCel(n,m)->getInt();
                        string strValue = Table_->getTableCel(n,m)->getString();
                        QString  str;
                        str.setNum(s);
                        ui->cell_val_int->setText(str);

                        QString strValue_ = QString::fromStdString(strValue);
                        ui->cell_val->setText(strValue_);


                        ui->cell_val_int->setText(str);
                        string s__ = Table_->getTableCel(n,m)->getString();
                        QString qstr = QString::fromStdString(s__);
                        ui->cell_val->setText(qstr);
                        ui->value_col_2->setText("");
                        ui->value_col_3->setText("");
                        ui->value_col_4->setText("");
                    }
                }
                else if((*Table_).getTableCel(n,m) && (*Table_).getTableCel(n,m)->getType() == 1 ) {
                           QMessageBox::critical(this, "Прудупреждение", "Ячейка с формулой");
                    float s= Table_->getTableCel(n,m)->getInt();
                    string strValue = Table_->getTableCel(n,m)->getString();
                    QString  str;
                    str.setNum(s);
                    ui->cell_val_int->setText(str);

                    QString strValue_ = QString::fromStdString(strValue);
                    ui->cell_val->setText(strValue_);
                    float summ = static_cast<TableCellFunction*>(this->Table_->getTableCel(n,m))->getSumm();
                    float proizv = static_cast<TableCellFunction*>(this->Table_->getTableCel(n,m))->getPr();
                    float SrMean = static_cast<TableCellFunction*>(this->Table_->getTableCel(n,m))->getSt();
                    cout <<"--"<< summ <<"--";
                    QString  str1, str2, str3;
                    str1.setNum(summ);
                    str2.setNum(proizv);
                    str3.setNum(SrMean);
                    ui->value_col_2->setText(str1);
                    ui->value_col_3->setText(str3);
                    ui->value_col_4->setText(str2);

                }
                else
                {
                    ui->cell_val_int->clear();
                    ui->cell_val->clear();
                    QMessageBox::critical(this, "Прудупреждение", "ячейка пуста");
                }
            }
        }
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    if( ui->coll_n->text() == "" || ui->lineEdit_3->text() == "") {
        QMessageBox::critical(this, "Ошибка", "Введите данные еще раз");
    }
    {
        if( ui->value_col->text() == "" || ui->value_row->text() == "") {
            QMessageBox::critical(this, "Ошибка", "Введите данные еще раз");
        }
        else if(ui->value_col_func_st->text() == "" && ui->value_row_func_st->text() == "" &&
                ui->value_col_func_end->text() == "" &&ui->value_row_func_end->text() == "")
        {
            int row_ = ui->value_row->text().toInt();
            int col_ = ui->value_col->text().toInt();
            if(row_  >= Table_->getLength() || col_ >= Table_->getWidth()) {
                QMessageBox::critical(this, "Ошибка", "Выход за пределы таблицы");
            }
            else{
                string  str = ui->cell_val->text().toStdString();
                QString val = ui->cell_val_int->text();
                float s = val.toFloat();
                if(s == 0 && str != "") {
                    TableCell n(str);
                    Table_->setTableCel(row_,col_,&n);
                }
                else{
                    TableCell n(s);
                    Table_->setTableCel(row_,col_,&n);


                }

            }
        }
        else if(ui->value_col_func_st->text() != "" && ui->value_row_func_st->text() != "" &&
                ui->value_col_func_end->text() != "" &&ui->value_row_func_end->text() != "")
        {
            int j_1 = ui->value_col_func_st->text().toInt();
            int i_2 = ui->value_row_func_end->text().toInt();
            int i_1 = ui->value_row_func_st->text().toInt();
            int j_2 = ui->value_col_func_end->text().toInt();
            int row_ = ui->value_row->text().toInt();
            int col_ = ui->value_col->text().toInt();
            int n = this->Table_->getLength();
            int m = this->Table_->getWidth();
            if( i_1 >= n|| i_2 >= n ||
                    j_1 >= m|| j_2 >= m || i_1 > i_2 || j_1 > j_2)

            {
                QMessageBox::critical(this, "Ошибка", "Выход за пределы таблицы");
            }
            else
            {
                TableCellFunction  one((*this->Table_) ,*(this->Table_->getTableCel(i_1,j_1)),*(this->Table_->getTableCel(i_2,j_2)));
                one.setIndex();
                one.setIndexi_1(i_1);
                one.setIndexj_1(j_1);
                one.setIndexi_2(i_2);
                one.setIndexj_2(j_2);


                this->Table_->setTableCel(row_,col_,&one);

            }

        }
        else{
            QMessageBox::critical(this, "Ошибка", "Введите еще раз");
        }

    }
}

void MainWindow::on_save_2_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save", ".", "Text files (*.txt)");
    if (not filename.isEmpty()) {
        if (Table_ && filename.endsWith(".txt"))
            Table_->writeInFile(filename);
        else if (!filename.endsWith(".txt"))
            QMessageBox::critical(this, "Ошибка", "Неверный формат!");
        else
            QMessageBox::critical(this, "Ошибка", "Коллекция не задана!");
    }
}

void MainWindow::on_action_2_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open ", ".", "Text files (*.txt)");
    if (!filename.isEmpty())
        try {
        if(Table_ == nullptr)
            this->Table_ = new TableCollection(1,1);
        Table_->readFromFile(filename);
        QString  str1, str2;
        str1.setNum(Table_->getLength());
        str2.setNum(Table_->getWidth());
        ui->coll_n->setText(str1);
        ui->lineEdit_3->setText(str2);
    }  catch (exception) {
        QMessageBox::critical(this, "Ошибка", "Ошибка при чтении данных");
    }
}
