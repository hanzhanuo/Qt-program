#ifndef EMPLOYEESYSTEM_H
#define EMPLOYEESYSTEM_H

#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QInputDialog>

class EmployeeSystem : public QWidget
{
    Q_OBJECT
public:
    EmployeeSystem(QWidget *parent = nullptr) ;

    ~EmployeeSystem();

private:
    void setWidgetLayout();
    void connectSignals();
    void addTestData();

private slots:
    void addEmployee();
    void removeEmployee();
    void filterEmployees(const QString &text);

private:

    //在Qt中，m_都是在设计数据成员(member)，所以以后数据成员就都写为m_即可
    //以后在cpp编程的时候，也可以使用m_的方法来替代_,感觉这样代码的可读性更强
    QListWidget *m_employeeList;

    QLineEdit *m_searchEdit;

    QPushButton *m_addButton;

    QPushButton *m_removeButton;
};
#endif // EMPLOYEESYSTEM_H
