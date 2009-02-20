/********************************************************************************
** Form generated from reading ui file 'url_open.ui'
**
** Created: Thu 19. Feb 16:28:21 2009
**      by: Qt User Interface Compiler version 4.3.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_URL_OPEN_H
#define UI_URL_OPEN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QVBoxLayout>

class Ui_UrlOpen
{
public:
    QVBoxLayout *vboxLayout;
    QFrame *frame;
    QHBoxLayout *hboxLayout;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLabel *label;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *UrlOpen)
    {
    if (UrlOpen->objectName().isEmpty())
        UrlOpen->setObjectName(QString::fromUtf8("UrlOpen"));
    UrlOpen->resize(333, 100);
    vboxLayout = new QVBoxLayout(UrlOpen);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    frame = new QFrame(UrlOpen);
    frame->setObjectName(QString::fromUtf8("frame"));
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
    frame->setSizePolicy(sizePolicy);
    frame->setFrameShape(QFrame::NoFrame);
    frame->setFrameShadow(QFrame::Plain);
    frame->setLineWidth(0);
    hboxLayout = new QHBoxLayout(frame);
    hboxLayout->setSpacing(0);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    hboxLayout->setContentsMargins(0, 0, 0, 0);
    label_2 = new QLabel(frame);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
    label_2->setSizePolicy(sizePolicy1);

    hboxLayout->addWidget(label_2);

    lineEdit = new QLineEdit(frame);
    lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

    hboxLayout->addWidget(lineEdit);


    vboxLayout->addWidget(frame);

    label = new QLabel(UrlOpen);
    label->setObjectName(QString::fromUtf8("label"));
    QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
    label->setSizePolicy(sizePolicy2);

    vboxLayout->addWidget(label);

    buttonBox = new QDialogButtonBox(UrlOpen);
    buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::NoButton|QDialogButtonBox::Ok);

    vboxLayout->addWidget(buttonBox);


    retranslateUi(UrlOpen);
    QObject::connect(buttonBox, SIGNAL(accepted()), UrlOpen, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), UrlOpen, SLOT(reject()));

    QMetaObject::connectSlotsByName(UrlOpen);
    } // setupUi

    void retranslateUi(QDialog *UrlOpen)
    {
    UrlOpen->setWindowTitle(QApplication::translate("UrlOpen", "Open URL", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("UrlOpen", "URL:", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("UrlOpen", "Please enter the URL you want to append", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(UrlOpen);
    } // retranslateUi

};

namespace Ui {
    class UrlOpen: public Ui_UrlOpen {};
} // namespace Ui

#endif // UI_URL_OPEN_H
