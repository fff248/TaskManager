# TaskManager

基于 C++ 和 Qt 开发的个人任务管理器。

## 功能

- 添加任务（支持优先级和截止时间）
- 按优先级自动排序
- 双击任务标记完成 / 取消完成
- 按关键词搜索过滤
- 统计各优先级任务数量
- 删除选中任务
- 清空已完成任务
- 导出任务列表为 CSV 文件
- 数据保存到本地文件，程序启动时自动读取

## 技术点

- C++ / Qt Widgets
- STL vector / sort 自定义排序
- 结构体存储任务数据
- 文件读写（QFile + QTextStream）
- Qt 信号槽机制
- 自定义排序与过滤逻辑
- CSV 导出

## 运行方式

1. 安装 Qt Creator
2. 用 Qt Creator 打开 `TaskManager.pro`
3. 编译运行

## 项目结构

- `mainwindow.h`：主窗口类定义、Task 结构体
- `mainwindow.cpp`：主窗口逻辑实现
- `mainwindow.ui`：界面布局
- `tasks.txt`：任务数据文件（程序运行时自动生成）

## 截图

![运行截图](screenshot.png)

## 后续计划

- 支持任务分类标签
- 支持按截止时间排序
- 支持导入 CSV
- 支持任务提醒
