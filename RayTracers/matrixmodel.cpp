#include "matrixmodel.h"


MatrixModel::MatrixModel(QObject *parent):
    inherited(parent),
    m_Matrix(),
    m_Axis(0, 0, 0),
    m_L(0),
    m_Degrees(0)
{

}

void MatrixModel::calculate()
{
    Vector n = m_Axis.normalisedCopy();
    m_Matrix = MatrixHelper::AffineTransform(Rotation::Rotation::RotationAroundAxisAtOrigin(n, m_Degrees, m_Origin), m_L) ;
    dataChanged(QModelIndex(), QModelIndex());
}

const Matrix &MatrixModel::matrix() const
{
    return m_Matrix;
}

void MatrixModel::setAxis_X(double X)
{
    m_Axis.x = X;
    calculate();
}

void MatrixModel::setAxis_Y(double Y)
{
    m_Axis.y = Y;
    calculate();
}

void MatrixModel::setAxis_Z(double Z)
{
    m_Axis.z = Z;
    calculate();
}

void MatrixModel::setOrigin_X(double X)
{
    m_Origin.x = X;
    calculate();
}

void MatrixModel::setOrigin_Y(double Y)
{
    m_Origin.y = Y;
    calculate();
}

void MatrixModel::setOrigin_Z(double Z)
{
    m_Origin.z = Z;
    calculate();
}

void MatrixModel::setDegrees(double degrees)
{
    m_Degrees = degrees;
    calculate();
}

QVariant MatrixModel::headerData(int section, Qt::Orientation /*orientation*/, int role) const
{
    switch(role)
    {
    case Qt::DisplayRole:
        return QString("");
        break;
    case Qt::SizeHintRole:
        if (section == 0)
        {
            return QSize(10, 10);
        }
        else
        {
            return QSize(10, 10);
        }
        break;

    }
    return QVariant();
}

int MatrixModel::rowCount(const QModelIndex &/*parent*/) const
{
    return 4;
}

int MatrixModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 4;

}

QVariant MatrixModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();
    // generate a log message when this method gets called
    switch(role){
    case Qt::DisplayRole:
    {
        double d = (m_Matrix).m_data[row][col];
        return QString("%1").arg(d);
    }
        break;
    case Qt::TextAlignmentRole:
        return Qt::AlignRight + Qt::AlignVCenter;
        break;
    }
    return QVariant();
}
