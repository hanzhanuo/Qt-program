#include <QApplication>
#include <QSplitter>
#include <QTreeWidget>
#include "FileExplorer.h"


FileExplorer::FileExplorer(QWidget *parent )
    : QWidget(parent)
{
    setWindowTitle("文件浏览器");
    resize(800, 600);


    //构造函数进行直接调用属于类内调用，根据面相对象设计原则，就只需要设计为private的函数即可
    setWidgetLayout();
    setupConnections();
    setupContextMenu();
}

void FileExplorer::setWidgetLayout()
//这个函数的作用就是根据题目描述，进行布局设置。所以其本身是没有难点的，就是要熟练三大布局widget的使用方法
//所以这个是应该自己默写的，默写不出来哪里就自己惩罚自己多写几遍

{
    //创建一个可调整大小的分割窗口组件
    QSplitter *splitter = new QSplitter(this);

    //一定要注意每个组件之间的组织关系，比如这里就是spliter是组织的树状图和表格之间的关系所创建的对象
    //而下面的dirTree是为了单纯组织树状图内部的关系所创建的对象
    //所以在Qt中主要需要注意的主体问题就是：每个对象是对于哪个层面的内容进行处理的
    //这个分不清楚就完全不知道诶个对象该怎么用了

    // 左侧目录树
    dirTree = new QTreeWidget;
    dirTree->setHeaderLabel("目录");
    dirTree->setColumnCount(1);
    dirTree->setContextMenuPolicy(Qt::CustomContextMenu);
    //想起来了：所有的已知部件的构造函数都是使用官方定义的setter函数来实现初始化的


    // 右侧文件表
    fileTable = new QTableWidget;
    //设置表格的列数为 3
    fileTable->setColumnCount(3);
    fileTable->setHorizontalHeaderLabels({"文件名", "大小", "修改日期"});
    //让最后一列（“修改日期”）自动拉伸填充剩余空间。
    fileTable->horizontalHeader()->setStretchLastSection(true);
    //允许为表格 自定义右键菜单（如“打开”“删除”“重命名”等操作)
    fileTable->setContextMenuPolicy(Qt::CustomContextMenu);
    //设置选中模式为 整行选中（而非单个单元格）
    fileTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    splitter->addWidget(dirTree);
    splitter->addWidget(fileTable);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(splitter);

    //这里是splitter专属的操作方式：即到最后了还不是setlayout，而是借助layout进行addWidget操作

    // 初始化目录树
    QTreeWidgetItem *root = new QTreeWidgetItem(dirTree, {"我的电脑"});
    QTreeWidgetItem *documents = new QTreeWidgetItem(root, {"文档"});
    QTreeWidgetItem *desktop = new QTreeWidgetItem(root, {"桌面"});
    QTreeWidgetItem *downloads = new QTreeWidgetItem(root, {"下载"});


    // 展开根节点——————这里表示的是默认对根节点就是进行展开效果的
    dirTree->expandItem(root);
}

void FileExplorer::setupConnections()
{
    connect(dirTree, &QTreeWidget::itemClicked, this, &FileExplorer::showDirectoryContents);
    connect(fileTable, &QTableWidget::itemDoubleClicked, this, &FileExplorer::openFile);
    connect(dirTree, &QTreeWidget::customContextMenuRequested,
            this, &FileExplorer::showTreeContextMenu);
    connect(fileTable, &QTableWidget::customContextMenuRequested,
            this, &FileExplorer::showTableContextMenu);
}

void FileExplorer::setupContextMenu()
//这是设置右键菜单栏，因为也是题目中必须要求的行为，所以就也要单独摘出一个函数来实现了
{


    //这里用于表示的是：对哪部分进行菜单的添加。然后这里的第一步是进行初始化的操作，
    //以我的习惯，我会把这个初始化的步骤放在头文件中直接实现
    treeMenu = new QMenu(this);
    QAction *refreshAction = new QAction("刷新", this);

/*
将动作添加到树形目录结构菜单
这个是让我困扰了一晚上的东西，这句就是具体把菜单添加到哪个位置的函数
但是这个是怎么确定是在哪个对应的界面中打开的菜单呢？——————原来是在槽函数中写了啊
所以这个给了我非常非常大的设计启发
——————对于Qt的设计，一定是先设计出每个部件的最终效果，然后再设计每个部件的放置位置和触发方式的
上面说的这种设计思维和先整体后局部的设计思维非常像，但是这个是先设计其局部实现，再设计其整体布局。所以Qt和cpp编程的思维是完全反过来的
一定要适应这种思维——————即先把每个具体部件都给设计出来，然后再对部件的摆放位置和部件的信号槽进行设计
*/

    //所以按上面所说，这里就是在设计菜单的具体内容，然后布局位置和信号槽触发都是后面再进行思考的
    //(但是一定一定不能忘，这个忘了也是非常常见的，所以在写代码的时候要在注释中写TODO，这个是天明老师教过的知识点)
    treeMenu->addAction(refreshAction);

    //点击“刷新”时调用函数
    connect(refreshAction, &QAction::triggered, this, &FileExplorer::refreshTree);

    tableMenu = new QMenu(this);
    //创建“打开”或者"删除"动作
    QAction *openAction = new QAction("打开", this);
    QAction *deleteAction = new QAction("删除", this);

    //将这两个动作添加到文件显示菜单
    tableMenu->addAction(openAction);
    tableMenu->addAction(deleteAction);
    //连接"打开"信号槽,打开选中的文集N
    connect(openAction, &QAction::triggered, this, &FileExplorer::openSelectedFile);
    //连接"删除"信号槽,删除选中的文件
    connect(deleteAction, &QAction::triggered, this, &FileExplorer::deleteSelectedFile);
}


//从这开始下面全是槽函数了
//所以槽函数一般都是放在所有成员函数后面实现的

/*
要让我自己写的话，我肯定想不到这个设计为一个槽函数来使用。所以其实Qt最强的就是万物都可以信号槽
因此不要把信号槽当作必杀技，而是要把信号槽作为最常规手段，信号槽体系解决不了的，就再思考事件系统
一些能让自己肌肉记忆想到信号槽来解决的技巧:
1.只要不是一打开就立马显示的，而是一种类似于和用户交互来实现显示的，就都使用信号槽来实现
2.经过计算器那个作业，我能体会到:槽函数是需要抽象归类的
——————即尽可能把多个比较类似(注意只要类似即可)的内容通过if-else分支结构抽象到一个槽函数中，或者作为cpp编程，所以其实直接使用继承多态的方式写槽函数也不是不可以
*/
void FileExplorer::showDirectoryContents(QTreeWidgetItem *item, int)

{
    // 模拟显示目录内容，此时是固定行号为第0行，然后对第0行进行显示
    fileTable->setRowCount(0);

    QStringList mockFiles;
    //这里的对于mockFiles的处理又是——————先进行精细的内容的设计，然后再对其布局进行设计
    //并且只要是对于QStringList进行初始化，就一定是进行这样连续的<<形式的初始化

    if (item->text(0) == "文档")    //text就是cout函数的含义，所以这里就是在进行cout的等号比较
    {
        mockFiles << "简历.doc" << "报告.pdf" << "笔记.txt";

    }
    else if (item->text(0) == "桌面")
    {
        mockFiles << "快捷方式.lnk" << "图片.png" << "项目文件.pro";
    }
    else if (item->text(0) == "下载")
    {
        mockFiles << "安装包.exe" << "电影.mp4" <<"音乐.mp3";
    }
    else
    {
        return;
    }

    //foreach (const QString &fileName, mockFiles)
    for (const QString &fileName : mockFiles)
    {
        //获取当前表格行数——————这个函数的作用效果和test函数的效果是一样的，都是像cout一样的效果
        //切记这里是对于表格式结构，而不是对于简单的list列表式的结构
        //所以以后显示目录信息的时候，可以优先选择这种表格式的结构进行操作，这个灵活度比价高
        //使用list形式的结构进行显示，只能显示出一行行的纯文本
        //然后table项目部件的另一个灵活之处是：可以使用row和column(行和列)的各种获取函数

        /*
        并且table结构是非常常用这种for循环的方式来实现对于所有内容的快速初始化的，
        而剩下两种项目部件都没法实现这种效果
        */

        int row = fileTable->rowCount();
        //在尾部插入行
        fileTable->insertRow(row);
        //在第0列设置文件名
        fileTable->setItem(row, 0, new QTableWidgetItem(fileName));
        //在第一列设置文件大小
        fileTable->setItem(row, 1, new QTableWidgetItem("100 KB"));
        //在第二列设置修改日期
        fileTable->setItem(row, 2, new QTableWidgetItem("2023-01-01"));
    }
}


void FileExplorer::openFile(QTableWidgetItem *item)
{
    QMessageBox::information(this, "文件打开", "尝试打开: " + item->text());
    //这种text和字符串进行加法操作的操作，非常常用，我又给忘了
}

//在目录树上显示右键上下文菜单（即之前定义的 treeMenu，包含“刷新”选项）。
void FileExplorer::showTreeContextMenu(const QPoint &pos)
{
    treeMenu->exec(dirTree->mapToGlobal(pos));
}


//在文件列表上显示右键上下文菜单（tableMenu，包含“打开”和“删除”选项）。
void FileExplorer::showTableContextMenu(const QPoint &pos)
{
    tableMenu->exec(fileTable->mapToGlobal(pos));
}

void FileExplorer::refreshTree()
{
    QMessageBox::information(this, "刷新", "目录树已刷新");
}

//当用户点击文件列表的 “打开” 菜单项时，尝试打开当前选中的文件
void FileExplorer::openSelectedFile()
{
    //获取当前选中的表格项
    if (fileTable->currentItem()){
        openFile(fileTable->currentItem());
    }

}

//当用户点击文件列表的 “删除” 菜单项时，删除当前选中的文件行
void FileExplorer::deleteSelectedFile()
{
    if (fileTable->currentItem())
    {
        //获取当前选中行的索引
        int row = fileTable->currentRow();
        //获取当前选中行的索引
        fileTable->removeRow(row);
    }
}
