#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>  // 或 QWidget

namespace Ui
{
class Calculator;
}

class Calculator : public QMainWindow
{
    Q_OBJECT
public:
    explicit Calculator(QWidget *parent = nullptr);
    ~Calculator();

private slots:
    void onDigitClicked();      // 数字按钮点击
    void onOperatorClicked();   // 运算符（+ - * /）点击
    void onEqualClicked();      // 等于 (=) 点击
    void onClearClicked();      // 清除 (C) 点击

private:
    Ui::Calculator *ui;
    QString currentInput;       // 当前输入的数字
    QString pendingOperator;    // 缓存的运算符（+ - * /）


    double result;              // 存储计算结果——————一定一定要注意，这里使用的是double，所以是真枪实弹进行运算操作了，而不是QString摆样子了
    bool waitingForOperand;     // 是否等待新的操作数。
    //我之前一直把这个标志位理解为是在看是否有运算符，但其实竟然是在看是否需求新的操作数
    // !!!注意:这里是看是否需求，而不是是否拥有。
    //是否拥有只取决于点击，是否需要取决于当前有没有运算符，是不是整个操作数为空？

    //只要能理解这些数据成员是用来干什么的，所有的流程就全都能理解了
};

#endif // CALCULATOR_H
