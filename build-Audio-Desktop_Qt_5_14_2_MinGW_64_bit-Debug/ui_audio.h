/********************************************************************************
** Form generated from reading UI file 'audio.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUDIO_H
#define UI_AUDIO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Audio
{
public:

    void setupUi(QWidget *Audio)
    {
        if (Audio->objectName().isEmpty())
            Audio->setObjectName(QString::fromUtf8("Audio"));
        Audio->resize(800, 600);

        retranslateUi(Audio);

        QMetaObject::connectSlotsByName(Audio);
    } // setupUi

    void retranslateUi(QWidget *Audio)
    {
        Audio->setWindowTitle(QCoreApplication::translate("Audio", "Audio", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Audio: public Ui_Audio {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUDIO_H
