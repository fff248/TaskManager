# TaskManager
a tool that can control my daily tasks

基于 C++ 和 Qt 开发的个人任务管理器。

## 功能

- 添加任务（支持优先级和截止时间）
- 按优先级自动排序
- 删除选中任务
- 数据保存到本地文件
- 程序启动时自动读取上次保存的任务

## 技术点

- C++ / Qt Widgets
- STL vector / sort 自定义排序
- 文件读写（QFile + QTextStream）
- 结构体存储任务数据

## 运行方式

1. 安装 Qt Creator
2. 用 Qt Creator 打开 `TaskManager.pro`
3. 编译运行
