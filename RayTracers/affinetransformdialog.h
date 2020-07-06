#ifndef AFFINETRANSFORMDIALOG_H
#define AFFINETRANSFORMDIALOG_H

#include <QDialog>
#include <QTableView>
#include "matrixmodel.h"
namespace Ui {
class AffineTransformDialog;
}

class AffineTransformDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AffineTransformDialog(
            QWidget *parent = 0,
            const Vector& axis = 0);
    ~AffineTransformDialog();

private slots:


    void on_spnAxis_X_editingFinished();

    void on_spnAxis_Y_editingFinished();

    void on_spnAxis_Z_editingFinished();

    void on_spnDegrees_editingFinished();

    void on_spnOrigin_X_editingFinished();

    void on_spnOrigin_Y_editingFinished();

    void on_spnOrigin_Z_editingFinished();

private:
    Ui::AffineTransformDialog *ui;
    MatrixModel m_Model;
public:
    const Matrix& matrix() const;
};


#endif // AFFINETRANSFORMDIALOG_H
