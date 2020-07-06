/********************************************************************************
** Form generated from reading UI file 'affinetransformdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AFFINETRANSFORMDIALOG_H
#define UI_AFFINETRANSFORMDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AffineTransformDialog
{
public:
    QDialogButtonBox *buttonBox;
    QTableView *tableView;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QDoubleSpinBox *spnAxis_X;
    QDoubleSpinBox *spnAxis_Y;
    QDoubleSpinBox *spnAxis_Z;
    QLabel *label_2;
    QDoubleSpinBox *spnOrigin_X;
    QDoubleSpinBox *spnOrigin_Y;
    QDoubleSpinBox *spnOrigin_Z;
    QLabel *label_3;
    QDoubleSpinBox *spnDegrees;

    void setupUi(QDialog *AffineTransformDialog)
    {
        if (AffineTransformDialog->objectName().isEmpty())
            AffineTransformDialog->setObjectName(QStringLiteral("AffineTransformDialog"));
        AffineTransformDialog->resize(520, 310);
        AffineTransformDialog->setCursor(QCursor(Qt::ArrowCursor));
        buttonBox = new QDialogButtonBox(AffineTransformDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(140, 260, 341, 32));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(buttonBox->sizePolicy().hasHeightForWidth());
        buttonBox->setSizePolicy(sizePolicy);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        tableView = new QTableView(AffineTransformDialog);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(60, 110, 441, 141));
        tableView->setFocusPolicy(Qt::NoFocus);
        tableView->setShowGrid(true);
        layoutWidget = new QWidget(AffineTransformDialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(60, 10, 438, 94));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        spnAxis_X = new QDoubleSpinBox(layoutWidget);
        spnAxis_X->setObjectName(QStringLiteral("spnAxis_X"));
        spnAxis_X->setContextMenuPolicy(Qt::NoContextMenu);
        spnAxis_X->setDecimals(6);
        spnAxis_X->setMinimum(-500);
        spnAxis_X->setMaximum(500);
        spnAxis_X->setValue(0);

        gridLayout->addWidget(spnAxis_X, 0, 1, 1, 1);

        spnAxis_Y = new QDoubleSpinBox(layoutWidget);
        spnAxis_Y->setObjectName(QStringLiteral("spnAxis_Y"));
        spnAxis_Y->setDecimals(6);
        spnAxis_Y->setMinimum(-500);
        spnAxis_Y->setMaximum(500);

        gridLayout->addWidget(spnAxis_Y, 0, 2, 1, 1);

        spnAxis_Z = new QDoubleSpinBox(layoutWidget);
        spnAxis_Z->setObjectName(QStringLiteral("spnAxis_Z"));
        spnAxis_Z->setDecimals(6);
        spnAxis_Z->setMinimum(-500);
        spnAxis_Z->setMaximum(500);

        gridLayout->addWidget(spnAxis_Z, 0, 3, 1, 1);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        spnOrigin_X = new QDoubleSpinBox(layoutWidget);
        spnOrigin_X->setObjectName(QStringLiteral("spnOrigin_X"));
        spnOrigin_X->setDecimals(6);
        spnOrigin_X->setMinimum(-500);
        spnOrigin_X->setMaximum(500);
        spnOrigin_X->setValue(0);

        gridLayout->addWidget(spnOrigin_X, 1, 1, 1, 1);

        spnOrigin_Y = new QDoubleSpinBox(layoutWidget);
        spnOrigin_Y->setObjectName(QStringLiteral("spnOrigin_Y"));
        spnOrigin_Y->setDecimals(6);
        spnOrigin_Y->setMinimum(-500);
        spnOrigin_Y->setMaximum(500);

        gridLayout->addWidget(spnOrigin_Y, 1, 2, 1, 1);

        spnOrigin_Z = new QDoubleSpinBox(layoutWidget);
        spnOrigin_Z->setObjectName(QStringLiteral("spnOrigin_Z"));
        spnOrigin_Z->setDecimals(6);
        spnOrigin_Z->setMinimum(-500);
        spnOrigin_Z->setMaximum(500);

        gridLayout->addWidget(spnOrigin_Z, 1, 3, 1, 1);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        spnDegrees = new QDoubleSpinBox(layoutWidget);
        spnDegrees->setObjectName(QStringLiteral("spnDegrees"));
        spnDegrees->setDecimals(6);
        spnDegrees->setMinimum(-360);
        spnDegrees->setMaximum(360);
        spnDegrees->setValue(0);

        gridLayout->addWidget(spnDegrees, 2, 1, 1, 1);

        layoutWidget->raise();
        buttonBox->raise();
        tableView->raise();

        retranslateUi(AffineTransformDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), AffineTransformDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), AffineTransformDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(AffineTransformDialog);
    } // setupUi

    void retranslateUi(QDialog *AffineTransformDialog)
    {
        AffineTransformDialog->setWindowTitle(QApplication::translate("AffineTransformDialog", "Dialog", 0));
        label->setText(QApplication::translate("AffineTransformDialog", "Axis", 0));
        label_2->setText(QApplication::translate("AffineTransformDialog", "Origin", 0));
        label_3->setText(QApplication::translate("AffineTransformDialog", "Degrees", 0));
    } // retranslateUi

};

namespace Ui {
    class AffineTransformDialog: public Ui_AffineTransformDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AFFINETRANSFORMDIALOG_H
