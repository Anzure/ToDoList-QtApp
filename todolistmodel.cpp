#include "todolistmodel.h"

TodoListModel::TodoListModel(QObject *parent)
    : QAbstractListModel(parent) {
}

int TodoListModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid())
        return 0;

    return m_items.count();
}

QVariant TodoListModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= m_items.count())
        return QVariant();

    const TodoItem &item = m_items[index.row()];

    switch (role) {
    case NameRole:
        return item.name();
    case CompletedRole:
        return item.isCompleted();
    default:
        return QVariant();
    }
}

void TodoListModel::deleteTask(int index) {
    if (index < 0 || index >= m_items.count())
        return;

    beginRemoveRows(QModelIndex(), index, index);
    m_items.removeAt(index);
    endRemoveRows();
}

bool TodoListModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (!index.isValid() || index.row() >= m_items.count())
        return false;

    TodoItem &item = m_items[index.row()];

    switch (role) {
    case NameRole:
        item.setName(value.toString());
        break;
    case CompletedRole:
        item.setCompleted(value.toBool());
        break;
    default:
        return false;
    }

    emit dataChanged(index, index, QVector<int>() << role);
    return true;
}

Qt::ItemFlags TodoListModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable | QAbstractListModel::flags(index);
}

QHash<int, QByteArray> TodoListModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[CompletedRole] = "completed";
    return roles;
}

void TodoListModel::addTask(const QString &name) {
    const int index = m_items.count();
    beginInsertRows(QModelIndex(), index, index);
    m_items.append(TodoItem(name));
    endInsertRows();
}

void TodoListModel::updateTask(int index, bool completed, const QString &name) {
    if (index < 0 || index >= m_items.count())
        return;

    TodoItem &item = m_items[index];
    item.setName(name);
    item.setCompleted(completed);
    emit dataChanged(createIndex(index, 0), createIndex(index, 0), QVector<int>() << CompletedRole);
}
