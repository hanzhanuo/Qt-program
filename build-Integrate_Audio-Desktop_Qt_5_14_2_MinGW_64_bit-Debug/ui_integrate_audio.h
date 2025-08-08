/********************************************************************************
** Form generated from reading UI file 'integrate_audio.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTEGRATE_AUDIO_H
#define UI_INTEGRATE_AUDIO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Integrate_Audio
{
public:

    void setupUi(QWidget *Integrate_Audio)
    {
        if (Integrate_Audio->objectName().isEmpty())
            Integrate_Audio->setObjectName(QString::fromUtf8("Integrate_Audio"));
        Integrate_Audio->resize(800, 600);

        retranslateUi(Integrate_Audio);

        QMetaObject::connectSlotsByName(Integrate_Audio);
    } // setupUi

    void retranslateUi(QWidget *Integrate_Audio)
    {
        Integrate_Audio->setWindowTitle(QCoreApplication::translate("Integrate_Audio", "Integrate_Audio", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Integrate_Audio: public Ui_Integrate_Audio {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTEGRATE_AUDIO_H
