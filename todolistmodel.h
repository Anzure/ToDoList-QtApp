#ifndef TODOLISTMODEL_H
#define TODOLISTMODEL_H

#include <QAbstractListModel>
#include <QList>
#include "todoitem.h"

class TodoListModel : public QAbstractListModel {
    Q_OBJECT
public:
    enum TodoRoles {
        NameRole = Qt::UserRole + 1,
        CompletedRole
    };

    TodoListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void addTask(const QString &name);
    Q_INVOKABLE void updateTask(int index, bool completed);
    Q_INVOKABLE void deleteTask(int index);

private:
    QList<TodoItem> m_items;
};

#endif // TODOLISTMODEL_H
