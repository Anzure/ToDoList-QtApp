// todoitem.h
#ifndef TODOITEM_H
#define TODOITEM_H

#include <QString>

class TodoItem {
public:
    // Konstruktør
    TodoItem(const QString &name, bool completed = false);

    // Getters
    QString name() const;
    bool isCompleted() const;

    // Setters
    void setName(const QString &name);
    void setCompleted(bool completed);

private:
    // Lokale variabler (bare tilgjengelig i denne klassen)
    QString m_name;
    bool m_completed;
};

#endif // TODOITEM_H
