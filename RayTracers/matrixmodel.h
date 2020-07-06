#ifndef MATRIXMODEL_H
#define MATRIXMODEL_H

#include <QTableView>
#include "matrix.h"
#include "rotation.h"

class MatrixModel : public QAbstractTableModel
 {
private:
    typedef QAbstractTableModel inherited;
    Matrix m_Matrix;
    Vector m_Axis;
    Vector m_Origin;
    Vector m_L;
    double m_Degrees;

 public:
     MatrixModel(QObject *parent);
     void calculate();
     const Matrix& matrix() const;
     void setAxis_X(double X);
     void setAxis_Y(double Y);
     void setAxis_Z(double Z);
     void setOrigin_X(double X);
     void setOrigin_Y(double Y);
     void setOrigin_Z(double Z);
     void setDegrees(double degrees);
     virtual QVariant headerData(
             int section, Qt::Orientation orientation,
             int role = Qt::DisplayRole) const;
     virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
     virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
     virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
 };



#endif // MATRIXMODEL_H
