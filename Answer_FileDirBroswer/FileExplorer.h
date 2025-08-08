#ifndef FILEEXPLORER_H
#define FILEEXPLORER_H

#include <QApplication>
#include <QSplitter>
#include <QTreeWidget>
#include <QTableWidget>
#include <QHeaderView>
#include <QFileSystemModel>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QMessageBox>
#include <QVBoxLayout>

class FileExplorer : public QWidget
{
    Q_OBJECT
public:
    FileExplorer(QWidget *parent = nullptr);


private:
    //这每个函数都是根据大致都有什么setter设置行为所创建的，
    //所以以后我在设计Qt代码逻辑的时候，也要学会写private的setter和getter函数，
    //函数的设计都必须遵循业务都需要分为几大板块从而实现设计

    void setWidgetLayout();
    //每次的整个布局系统的设计，都是应该在这个函数中实现的，以后对于所有布局的需求都无脑在这个函数中实现


    void setupConnections();
    //果然只要是设计为是setconnect的函数，就都是用来存放所有connect函数的集合的
    //一定要再次注意：1.connect函数不是到了某句话才会被调用触发
    void setupContextMenu();

    //所以可以看出：在Qt中的类的设计时：基本上除了是有的setter和getter函数，其他的函数基本上都是自定义信号函数和槽函数了
    //现在学了事件可能有更多的函数需要定义，慢慢再在认知上向上添加



private slots:


    void showDirectoryContents(QTreeWidgetItem *item, int);   //显示文件详细信息
    void openFile(QTableWidgetItem *item);   //文件打开功能
    void showTreeContextMenu(const QPoint &pos);   //显示树形目录
    void showTableContextMenu(const QPoint &pos);  //显示目录文件的详细信息的

    void refreshTree();   //对目录结构进行刷新，
    void openSelectedFile();   //打开选中的文件的功能
    void deleteSelectedFile();  //删除选中的文件的功能

private:
    QTreeWidget *dirTree;
    QTableWidget *fileTable;
    QMenu *treeMenu;
    QMenu *tableMenu;
};

#endif // FILEEXPLORER_H
