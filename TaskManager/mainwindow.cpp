#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addbtn_clicked()
{
    QString context=ui->lineEdit->text();
    if(context.isEmpty()){
        QMessageBox::warning(this,"警告","请输入内容");
        return;
    }else{
        ui->list->addItem(context);
        ui->lineEdit->clear();
    }
}
