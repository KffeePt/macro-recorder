#include "event_delegate.h"
#include <QPainter>
#include <QApplication>
#include <QMouseEvent>

EventDelegate::EventDelegate(QObject *parent) : QStyledItemDelegate(parent)
{
}

void EventDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyledItemDelegate::paint(painter, option, index);

    if (index.column() == index.model()->columnCount() - 1) {
        QIcon deleteIcon = QApplication::style()->standardIcon(QStyle::SP_TrashIcon);
        QRect iconRect = option.rect;
        int iconSize = 16;
        int x = option.rect.right() - 20 + (20 - iconSize) / 2;
        int y = option.rect.top() + (option.rect.height() - iconSize) / 2;
        iconRect.setRect(x, y, iconSize, iconSize);
        deleteIcon.paint(painter, iconRect);
    }
}

QSize EventDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSize size = QStyledItemDelegate::sizeHint(option, index);
    if (index.column() == 0) {
        size.setWidth(size.width() + 20);
    }
    return size;
}

bool EventDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if (event->type() == QEvent::MouseButtonRelease) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (index.column() == index.model()->columnCount() - 1) {
            QRect iconRect = option.rect;
            int iconSize = 16;
            int x = option.rect.right() - 20 + (20 - iconSize) / 2;
            int y = option.rect.top() + (option.rect.height() - iconSize) / 2;
            iconRect.setRect(x, y, iconSize, iconSize);
            if (iconRect.contains(mouseEvent->pos())) {
                emit deleteIndex(index.siblingAtColumn(0));
                return true;
            }
        }
    }
    return QStyledItemDelegate::editorEvent(event, model, option, index);
}