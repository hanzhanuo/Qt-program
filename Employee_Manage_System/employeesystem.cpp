#include "employeesystem.h"

EmployeeSystem::EmployeeSystem(QWidget *parent)

    : QWidget(parent)
{
    setWindowTitle("员工管理系统");
    resize(600, 500);

    //进行部件布局
    setWidgetLayout();
    connectSignals();
    addTestData();

    //这里直接在构造函数中调用这些函数了，但其实是可以在main函数中直接调用这些函数的，写起来是等效的
}

EmployeeSystem::~EmployeeSystem()
{

}

//进行部件布局
void EmployeeSystem::setWidgetLayout()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    m_searchEdit = new QLineEdit;
    m_searchEdit->setPlaceholderText("搜索员工...");   //占位提示符

    m_employeeList = new QListWidget;

    QHBoxLayout *buttonLayout = new QHBoxLayout;

    //这里就不再是使用变量的方法来设计数据成员了，而是使用数据成员。
    //之前讲cpp的时候也说过，如果想要跨多个函数使用同一个数据成员，最好的方法就是使用数据成员来代替变量的方法实现

    m_addButton = new QPushButton("添加员工");
    m_removeButton = new QPushButton("删除选中");

    buttonLayout->addWidget(m_addButton);
    buttonLayout->addWidget(m_removeButton);

    mainLayout->addWidget(m_searchEdit);
    mainLayout->addWidget(m_employeeList);
    mainLayout->addLayout(buttonLayout);
}

void EmployeeSystem::connectSignals()
//所以在这种非常大型的综合题中，槽函数都是不使用lambda表达式的
//(除非是一些独立不被别的内容影响的，非常简单的槽函数)
//然后都是先对槽函数进行非常麻烦的设计，然后使用一个大的connect函数对所有的connect函数进行封装(这里就是典型的进行封装的方法)
{
    connect(m_addButton, &QPushButton::clicked, this, &EmployeeSystem::addEmployee);
    connect(m_removeButton, &QPushButton::clicked, this, &EmployeeSystem::removeEmployee);
    connect(m_searchEdit, &QLineEdit::textChanged, this, &EmployeeSystem::filterEmployees);
}

void EmployeeSystem::addTestData()
{
    m_employeeList->addItems({"张三", "李四", "王五", "赵六", "钱七", "孙八"});
    //这种方式和通过QStringList进行添加的方式一模一样，两者属于等价的操作
    //即和如下的三步走的方式是完全等价的方式，只不过这里相当于是传入右值了
    /*
    QStringList lst;
    lst << "锄禾日当午" << "汗滴禾下土" << "谁知盘中餐" << "粒粒皆辛苦";
    listWidget->addItems(lst);
    */
}


void EmployeeSystem::addEmployee()
{
    bool ok;
    QString name = QInputDialog::getText(this, "添加员工", "请输入员工姓名:",
                                         QLineEdit::Normal, "", &ok);

    //上面这句就是专属于InputDialog的创建方式了，其实其效果和文件对话框的getOpenFileName是一模一样的
    //两者都是一大长条然后最终返回一个QString。
    //只不过两者从含义上来说，确实是一个用来获取路径，一个用来获取名称。
    //所以很多时候重点不仅仅是形式，形式只是程序开发者设计模式哲学的体现。更多的是关乎于函数的具体含义
    //参数列表和返回值，这两个配合函数名，才是一个函数真正的含义的体现
    //作为函数调用开发者，重点一定是对函数的含义的体会，而不是函数的参数列表这种形式的体会

    if (ok && !name.isEmpty())
        //因为对话框没法直接使用信号槽系统，所以这里就通过if语句实现信号槽的等价了
    {
        m_employeeList->addItem(name);
    }
}

void EmployeeSystem::removeEmployee()
{
    delete m_employeeList->takeItem(m_employeeList->currentRow());
    //这里的写法非常非常值得学习：因为这里并不是等待着对象树销毁它才销毁，而是需要在remove之后就立刻销毁
    //所以为了实现这种立刻销毁，就要格外注意这种对于堆对象提取出来(逻辑销毁)之后的直接delete(物理销毁)
}


void EmployeeSystem::filterEmployees(const QString &text)
{
    //m_employeeList->count()获取列表的项总数。
    for (int i = 0; i < m_employeeList->count(); ++i)
    {
        QListWidgetItem *item = m_employeeList->item(i);
        //检查文本是否包含text，忽略大小写
        //控制项的显示/隐藏状态
        item->setHidden(!item->text().contains(text, Qt::CaseInsensitive));


        //上面这个语句非常非常精彩，体现了对于各种函数的组合使用。
        //这个就像上面的delete语句一样，都体现了Qt对于函数的组合使用的强大效果
        //这里只有组合使用contains和hidden，才能有效实现自己想要实现的过滤操作。
        //所以这是一件很吃业务逻辑思路和函数积累功底的能力

    }
}
