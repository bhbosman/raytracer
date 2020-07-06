#include "affinetransformdialog.h"
#include "ui_affinetransformdialog.h"

AffineTransformDialog::AffineTransformDialog(
        QWidget *parent,
        const Vector &axis) :
    QDialog(parent),
    ui(new Ui::AffineTransformDialog),
    m_Model(nullptr)
{
    ui->setupUi(this);
    ui->tableView->setModel(&m_Model);

    ui->spnAxis_X->setValue(axis.x);
    ui->spnAxis_Y->setValue(axis.y);
    ui->spnAxis_Z->setValue(axis.z);

    m_Model.setAxis_X(ui->spnAxis_X->value());
    m_Model.setAxis_Y(ui->spnAxis_Y->value());
    m_Model.setAxis_Z(ui->spnAxis_Z->value());
}


AffineTransformDialog::~AffineTransformDialog()
{
    delete ui;
}

void AffineTransformDialog::on_spnAxis_X_editingFinished()
{
        m_Model.setAxis_X(ui->spnAxis_X->value());
}

void AffineTransformDialog::on_spnAxis_Y_editingFinished()
{
    m_Model.setAxis_Y(ui->spnAxis_Y->value());
}

void AffineTransformDialog::on_spnAxis_Z_editingFinished()
{
    m_Model.setAxis_Z(ui->spnAxis_Z->value());
}

void AffineTransformDialog::on_spnDegrees_editingFinished()
{
    m_Model.setDegrees(ui->spnDegrees->value());
}

void AffineTransformDialog::on_spnOrigin_X_editingFinished()
{
    m_Model.setOrigin_X(ui->spnOrigin_X->value());
}

void AffineTransformDialog::on_spnOrigin_Y_editingFinished()
{
    m_Model.setOrigin_Y(ui->spnOrigin_Y->value());
}

void AffineTransformDialog::on_spnOrigin_Z_editingFinished()
{
    m_Model.setOrigin_Z(ui->spnOrigin_Z->value());
}

const Matrix &AffineTransformDialog::matrix() const
{
    return m_Model.matrix();
}

