// mymodel.cpp
#include "mymodel.hpp"

MyModel::MyModel(QObject *parent)
        : QAbstractTableModel(parent)
{
}

int MyModel::rowCount(const QModelIndex & /*parent*/) const
{
    return 4;
}

int MyModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 5;
}

QVariant MyModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
        return QString("Row%1, Column%2")
                .arg(index.row() + 1)
                .arg(index.column() +1);

    return QVariant();
}