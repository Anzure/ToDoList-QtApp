#ifndef TODOITEM_H
#define TODOITEM_H

#include <QString>

class TodoItem {
public:
    TodoItem(const QString &name, bool completed = false);

    QString name() const;
    bool isCompleted() const;

    void setName(const QString &name);
    void setCompleted(bool completed);

private:
    QString m_name;
    bool m_completed;
};

#endif // TODOITEM_H
