// todolistmodel.h
#ifndef TODOLISTMODEL_H
#define TODOLISTMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include "todoitem.h"

class TodoListModel : public QAbstractListModel {
    Q_OBJECT
public:
    // Konstruktør
    TodoListModel(QObject *parent = nullptr);

    // ListModel avhengige metoder
    enum TodoRoles {
        NameRole = Qt::UserRole + 1,
        CompletedRole
    };
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QHash<int, QByteArray> roleNames() const override;

    // Metoder for å legge til, oppdatere og slette oppgaver
    Q_INVOKABLE void addTask(const QString &name, bool completed = false);
    Q_INVOKABLE void updateTask(int index, bool completed, const QString &name);
    Q_INVOKABLE void deleteTask(int index);

    // Metoder for å laste og lagre oppgaver til fil
    void loadTasks();
    void saveTasks();

public slots:
    // Metode som kalles når listen med oppgaver endres
    void onDataChanged();

private:
    // Lokal liste (medlemsvariabel) med oppgaver
    QList<TodoItem> m_items;
};

#endif // TODOLISTMODEL_H
