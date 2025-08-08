//
// Created by ASUS on 2025/7/9.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Test2.h" resolved

#include "test2.h"
#include "ui_Test2.h"


Test2::Test2(QWidget *parent) :
    QWidget(parent), ui(new Ui::Test2) {
    ui->setupUi(this);
}

Test2::~Test2() {
    delete ui;
}
