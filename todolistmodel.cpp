// todolistmodel.cpp
#include "todolistmodel.h"

TodoListModel::TodoListModel(QObject *parent)
    : QAbstractListModel(parent) {
    // Laster oppgaver fra fil på disk i konstruktøren
    loadTasks();

    // Lytter etter endringer og lagrer dem til fil i onDataChanged funksjonen
    connect(this, &TodoListModel::dataChanged, this, &TodoListModel::onDataChanged);
}

QVariant TodoListModel::data(const QModelIndex &index, int role) const {
    // Sjekker at indeksen er gyldig
    if (!index.isValid() || index.row() >= m_items.count())
        return QVariant();

    // Returnerer data for gitt felt
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
    // Sjekker at indeksen er gyldig
    if (index < 0 || index >= m_items.count())
        return;

    // Fjerner element med gitt indeks fra listen
    beginRemoveRows(QModelIndex(), index, index);
    m_items.removeAt(index);
    endRemoveRows();

    // Sender signal om at data har blitt endret
    emit dataChanged(createIndex(index, 0), createIndex(index, 0), QVector<int>() << CompletedRole);
}



bool TodoListModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    // Sjekker at indeksen er gyldig
    if (!index.isValid() || index.row() >= m_items.count())
        return false;

    // Setter data for gitt felt
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

    // Sender signal om at data har blitt endret
    emit dataChanged(index, index, QVector<int>() << role);
    return true;
}

void TodoListModel::addTask(const QString &name, bool completed) {
    // Legger til element i listen
    const int index = m_items.count();
    beginInsertRows(QModelIndex(), index, index);
    m_items.append(TodoItem(name, completed));
    endInsertRows();

    // Sender signal om at data har blitt endret
    emit dataChanged(createIndex(index, 0), createIndex(index, 0), QVector<int>() << CompletedRole);
}

void TodoListModel::updateTask(int index, bool completed, const QString &name) {
    // Sjekker at indeksen er gyldig
    if (index < 0 || index >= m_items.count())
        return;

    // Oppdaterer element på gitt indeks i listen
    TodoItem &item = m_items[index];
    item.setName(name);
    item.setCompleted(completed);
    emit dataChanged(createIndex(index, 0), createIndex(index, 0), QVector<int>() << CompletedRole);
}

void TodoListModel::loadTasks() {
    // Åpner en read stream til filen
    QFile file("todolist.json");
    if (file.open(QIODevice::ReadOnly)) {
        // Leser JSON dokumentet fra fil
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        QJsonArray array = doc.array();

        // Legger til oppgavene i listen
        for (const QJsonValue &value : array) {
            QJsonObject obj = value.toObject();
            addTask(obj["name"].toString(), obj["completed"].toBool());
        }
        qDebug() << "Loaded " << m_items.count() << " tasks from file.";
    }
}

void TodoListModel::saveTasks() {
    // Åpner en write stream til filen
    QFile file("todolist.json");
    if (file.open(QIODevice::WriteOnly)) {
        // Lager JSON fra listen med oppgaver
        QJsonArray array;
        for (const TodoItem &item : m_items) {
            QJsonObject obj;
            obj["name"] = item.name();
            obj["completed"] = item.isCompleted();
            array.append(obj);
        }
        QJsonDocument doc(array);

        // Skriver JSON dokumentet til fil
        file.write(doc.toJson());
        qDebug() << "Saved " << m_items.count() << " tasks to file.";
    }
}

void TodoListModel::onDataChanged() {
    // Lagrer oppgavene til lokal fil på disk
    saveTasks();
}

QHash<int, QByteArray> TodoListModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[CompletedRole] = "completed";
    return roles;
}

int TodoListModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid())
        return 0;
    return m_items.count();
}

Qt::ItemFlags TodoListModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return Qt::NoItemFlags;
    return Qt::ItemIsEditable | QAbstractListModel::flags(index);
}
