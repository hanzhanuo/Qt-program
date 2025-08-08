//
// Created by ASUS on 2025/7/9.
//

#ifndef TEST2_H
#define TEST2_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class Test2; }
QT_END_NAMESPACE

class Test2 : public QWidget {
Q_OBJECT

public:
    explicit Test2(QWidget *parent = nullptr);
    ~Test2() override;

private:
    Ui::Test2 *ui;
};


#endif //TEST2_H
