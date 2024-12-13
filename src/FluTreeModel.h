#pragma once

#include <QObject>
#include <QAbstractTableModel>
#include <QJsonArray>
#include <QVariant>
#include <QtQml/qqml.h>
#include "stdafx.h"


/**
 * @brief The FluTreeNode class
 */
class FluTreeNode : public QObject {
    Q_OBJECT
    Q_PROPERTY(QVariantMap data READ data CONSTANT)
    Q_PROPERTY(QString key READ key CONSTANT)
    Q_PROPERTY(QString title READ title CONSTANT)
    Q_PROPERTY(QString type READ type CONSTANT)
    Q_PROPERTY(QString value READ value CONSTANT)
    Q_PROPERTY(int depth READ depth CONSTANT)
    Q_PROPERTY(bool isExpanded READ isExpanded CONSTANT)
    Q_PROPERTY(bool checked READ checked CONSTANT)
public:
    explicit FluNode(QObject *parent = nullptr);
    Q_INVOKABLE QString key(){return _key;};
    Q_INVOKABLE QString title(){return _title;};
    Q_INVOKABLE QString type(){return _type;};
    Q_INVOKABLE QString value(){return _value;};
    Q_INVOKABLE int depth(){return _depth;};
    Q_INVOKABLE bool isExpanded(){return _isExpanded;};
    Q_INVOKABLE bool hasChildren(){ return !_children.isEmpty();};
    Q_INVOKABLE bool hasNextNodeByIndex(int index){
        FluNode* p = this;
        for(int i=0;i<(_depth - index -1);i++){
    explicit FluTreeNode(QObject *parent = nullptr);

    [[nodiscard]] Q_INVOKABLE int depth() const {
        return _depth;
    };

    [[nodiscard]] Q_INVOKABLE bool isExpanded() const {
        return _isExpanded;
    };

    [[nodiscard]] Q_INVOKABLE QVariantMap data() const {
        return _data;
    };

    [[nodiscard]] Q_INVOKABLE bool hasChildren() const {
        return !_children.isEmpty();
    };

    Q_INVOKABLE bool hasNextNodeByIndex(int index) {
        FluTreeNode *p = this;
        for (int i = 0; i <= _depth - index - 1; i++) {
            p = p->_parent;
        }
        if (p->_parent->_children.indexOf(p) == p->_parent->_children.count() - 1) {
            return false;
        }
        return true;
    }

    [[nodiscard]] Q_INVOKABLE bool checked() const {
        if (!hasChildren()) {
            return _checked;
        }
        for (int i = 0; i <= _children.size() - 1; ++i) {
            auto item = _children.at(i);
            if (!item->checked()) {
                return false;
            }
        }
        return true;
    };

    Q_INVOKABLE bool hideLineFooter() {
        if (_parent) {
            auto childIndex = _parent->_children.indexOf(this);
            if (childIndex == _parent->_children.count() - 1) {
                return true;
            }
            if (_parent->_children.at(childIndex + 1)->hasChildren()) {
                return true;
            }
            return false;
        }
        return false;
    };

    [[nodiscard]] bool isShown() const {
        auto p = _parent;
        while (p) {
            if (!p->_isExpanded) {
                return false;
            }
            p = p->_parent;
        }
        return true;
    }

public:
    QString _key="";
    QString _title="";
    QString _type="";
    QString _value="";
    QString _raw_type="";
    int _depth=0;
    bool _checked = false;
    bool _isExpanded = true;
    QVariantMap _data;
    QList<FluTreeNode *> _children;
    FluTreeNode *_parent = nullptr;
};

class FluTreeModel : public QAbstractTableModel {
    Q_OBJECT
    Q_PROPERTY(int max_depth READ max_depth CONSTANT)
    Q_PROPERTY_AUTO(int,dataSourceSize)
    Q_PROPERTY_AUTO(QList<FluNode*>,selectionModel)
    Q_PROPERTY_AUTO(QList<QVariantMap>, columnSource)
    QML_NAMED_ELEMENT(FluTreeModel)
public:
    enum TreeModelRoles { RowModel = 0x0101, ColumnModel = 0x0102 };

    explicit FluTreeModel(QObject *parent = nullptr);

    [[nodiscard]] int rowCount(const QModelIndex &parent = {}) const override;

    [[nodiscard]] int columnCount(const QModelIndex &parent = {}) const override;

    [[nodiscard]] QVariant data(const QModelIndex &index,
                                int role = Qt::DisplayRole) const override;

    [[nodiscard]] QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE int max_depth(){return _max_depth;};
    Q_INVOKABLE void removeRows(int row, int count);

    Q_INVOKABLE void insertRows(int row, const QList<FluTreeNode *> &data);

    Q_INVOKABLE QObject *getRow(int row);

    Q_INVOKABLE void setRow(int row, QVariantMap data);

    Q_INVOKABLE void setData(QList<FluTreeNode *> data);

    Q_INVOKABLE void setDataSource(QList<QMap<QString, QVariant>> data);
    Q_INVOKABLE void collapse(int row);

    Q_INVOKABLE void expand(int row);

    Q_INVOKABLE FluTreeNode *getNode(int row);

    Q_INVOKABLE void refreshNode(int row);

    Q_INVOKABLE void checkRow(int row, bool checked);

    Q_INVOKABLE bool hitHasChildrenExpanded(int row);

    Q_INVOKABLE void allExpand();

    Q_INVOKABLE void allCollapse();

    Q_INVOKABLE void update(char* data);

    Q_INVOKABLE QVariant selectionModel();

private:
    QList<FluNode*> _rows;
    QList<FluNode*> _dataSource;
    FluNode* _root = nullptr;
    int _max_depth = 0;
    QMap<int, QMetaType> _map;
    void WriteIndex();
    QString CopyValues(char* data, QMetaType& type, int offset);
    QList<FluTreeNode *> _rows;
    QList<FluTreeNode *> _dataSource;
    FluTreeNode *_root = nullptr;
};

inline QString FluTreeModel::CopyValues(char* data, QMetaType& type, int offset)
{
    int size = type.sizeOf();
    switch (type.id()) {
    case QMetaType::Bool:{
        bool res = false;
        memcpy(&res, data+offset, size);
        return QString::number(res);
    }
    case QMetaType::Int:{
        int res = 0;
        memcpy(&res, data+offset, size);
        return QString::number(res);
    }
    case QMetaType::Double:{
        double res = 0;
        memcpy(&res, data+offset, size);
        return QString::number(res);
    }
    case QMetaType::Char:{
        char res = 0;
        memcpy(&res, data+offset, size);
        return QString::number(res);
    }
    case QMetaType::UChar:{
        unsigned char res = 0;
        memcpy(&res, data+offset, size);
        return QString::number(res);
    }
    case QMetaType::Float:{
        float res = 0;
        memcpy(&res, data+offset, size);
        return QString::number(res);
    }
    }
    return QString();
}

#endif // FLUTREEMODEL_H
