#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QMessageBox>
#include<QString>
#include<vector>
#include<algorithm>
#include <QCloseEvent>
#include<QFile>//文件读写
#include<QTextStream>//文本流读写
#include<QStringList>
#include<QFileDialog>
namespace Ui {
class MainWindow;
}

struct Task {
    QString name;
    QString priority;
    QString deadline;
    bool done;
};
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_addbtn_clicked();//添加任务
    void on_dltbtn_clicked();//删除任务
    void on_list_doubleClicked(const QModelIndex &index);
    void on_searchbtn_clicked();//搜索按钮

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    std::vector<Task> tasks;
    void sortTask();
    int priority(const QString &p);//比较任务程度
    void saveTasks();//保存数据
    void loadTasks();//读取数据
    void refresh();//刷新数据
    void tj();//统计优先级
protected:
    void closeEvent(QCloseEvent *event)override;//关闭窗口
};

#endif // MAINWINDOW_H
