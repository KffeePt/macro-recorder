#ifndef EVENT_DELEGATE_H
#define EVENT_DELEGATE_H

#include <QStyledItemDelegate>

class EventDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit EventDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;

signals:
    void deleteIndex(const QModelIndex &index);
};

#endif // EVENT_DELEGATE_H