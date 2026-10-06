#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadTasks();
    sortTask();
    setWindowTitle("任务管理器");
}

MainWindow::~MainWindow()
{
    delete ui;
}
//保存数据
void MainWindow::saveTasks(){
    QFile file("tasks.txt");
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text)) return;
    QTextStream out(&file);//out相当于一支笔在文件里写字
    for(auto& t:tasks){
        out << t.priority << "|" << t.name << "|" << t.deadline << "|" << (t.done ? 1 : 0) << "\n";
    }
    file.close();
}
//读取数据
void MainWindow::loadTasks(){
    QFile file("tasks.txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)) return;
    QTextStream in(&file);
    while(!in.atEnd()){
        QString line = in.readLine();
                QStringList parts = line.split("|");
                if (parts.size() != 4) continue;

                Task t;
                t.priority = parts[0];
                t.name = parts[1];
                t.deadline = parts[2];
                t.done = parts[3].toInt() == 1;
                tasks.push_back(t);
    }
    file.close();
}
//添加任务
void MainWindow::on_addbtn_clicked()
{
    Task t;
    QString context=ui->lineEdit->text();
    if(context.isEmpty()){
        QMessageBox::warning(this,"警告","请输入内容");
        return;
    }else{
    t.name=context;
    t.priority=ui->comboBox->currentText();
    t.deadline=ui->date->text();
    t.done=false;
    tasks.push_back(t);
    ui->lineEdit->clear();
    }
    sortTask();
    tj();
}
//任务排序
void MainWindow::sortTask(){
    std::sort(tasks.begin(),tasks.end(),[this](const Task& a,const Task& b){
        return priority(a.priority)<priority(b.priority);
    });
   refresh();
   tj();
}
//返回优先级
int MainWindow::priority(const QString &p){
    if(p=="高") return 0;
    if(p=="中") return 1;
    if(p=="低") return 2;
    return 3;
}
//删除任务
void MainWindow::on_dltbtn_clicked()
{
    int row=ui->list->currentRow();
    if (row < 0) return;
    ui->list->takeItem(row);
    tasks.erase(tasks.begin()+row);
    saveTasks();
    tj();
}
//关闭窗口
void MainWindow::closeEvent(QCloseEvent *event) {
    saveTasks();
    event->accept();
}
//确定任务状态
void MainWindow::on_list_doubleClicked(const QModelIndex &index)
{
    int row=ui->list->currentRow();
    if(row<0||row>tasks.size()) return;
    QMessageBox::StandardButton res=QMessageBox::question(this,"确认","任务已完成？",QMessageBox::Yes|QMessageBox::No);
    if (res == QMessageBox::Yes) {
        tasks[row].done = true;
}else {
        tasks[row].done = false;
    }
    sortTask();
}
//刷新
void MainWindow::refresh(){
    QString key=ui->searchline->text();
    ui->list->clear();
    for(auto &t:tasks){
        if(key.isEmpty()||t.name.contains(key)){
            QString prefix = t.done ? "[✓] " : "";
            QString total=prefix+"["+t.priority+"]"+" "+t.name+"   "+"Deadline"+" "+t.deadline;
            ui->list->addItem(total);
        }
    }
   tj();
}
//搜索关键字
void MainWindow::on_searchbtn_clicked()
{
 refresh();
 tj();
}
void MainWindow::tj(){
    int g=0,z=0,d=0;
    for(auto &p:tasks){
        if(p.priority=="高") g++;
        if(p.priority=="中") z++;
        if(p.priority=="低") d++;
    }
    QString text="高："+QString::number(g)+" 中："+QString::number(z)+" 低："+QString::number(d);
    ui->tjlabel->setText(text);
}
//导出任务清单
void MainWindow::on_pushButton_clicked()
{
   QString path= QFileDialog::getSaveFileName(this,"导出","","CSV文件(*csv)");
   if(path.isEmpty()) return;
   QFile file(path);
   if(!file.open(QIODevice::WriteOnly|QIODevice::Text)) return;
   QTextStream out(&file);
   for(auto& t:tasks){
     out << t.priority << "," << t.name << "," << t.deadline << "," << (t.done ? 1 : 0) << "\n";
    }
      file.close();
}
