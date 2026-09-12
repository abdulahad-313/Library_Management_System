#ifndef ALTERNATINGROWDELEGATE_H
#define ALTERNATINGROWDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>

class AlternatingRowDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit AlternatingRowDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override
    {
        QStyleOptionViewItem opt = option;

        if (index.row() % 2 == 0) {
            painter->fillRect(option.rect, QColor(0, 0, 139)); // dark blue
        } else {
            painter->fillRect(option.rect, QColor(0, 100, 0)); // dark green
        }

        opt.palette.setColor(QPalette::Text, Qt::white);
        QStyledItemDelegate::paint(painter, opt, index);
    }
};

#endif // ALTERNATINGROWDELEGATE_H