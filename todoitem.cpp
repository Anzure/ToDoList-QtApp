// todoitem.cpp
#include "todoitem.h"

TodoItem::TodoItem(const QString &name, bool completed)
    : m_name(name), m_completed(completed) {
}

QString TodoItem::name() const {
    return m_name;
}

bool TodoItem::isCompleted() const {
    return m_completed;
}

void TodoItem::setName(const QString &name) {
    m_name = name;
}

void TodoItem::setCompleted(bool completed) {
    m_completed = completed;
}
