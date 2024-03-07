#ifndef FLUTREEMODEL_H
#define FLUTREEMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <QJsonArray>
#include <QtQml/qqml.h>
#include "stdafx.h"

/**
 * @brief The FluNode class
 */
class FluNode : public QObject{
    Q_OBJECT
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
            p = p->_parent;
        }
        if(p->_parent->_children.indexOf(p) == p->_parent->_children.count()-1){
            return false;
        }
        return true;
    }
    Q_INVOKABLE bool checked(){
        if(!hasChildren()){
            return _checked;
        }
        foreach (auto item, _children) {
            if(!item->checked()){

                return false;
            }
        }
        return true;
    };
    Q_INVOKABLE bool hideLineFooter(){
        if(_parent){
            auto childIndex =  _parent->_children.indexOf(this);
            if(childIndex==_parent->_children.count()-1){
                return true;
            }
            if(_parent->_children.at(childIndex+1)->hasChildren()){
                return true;
            }
            return false;
        }
        return false;
    };
    bool isShown(){
        auto p = _parent;
        while (p) {
            if(!p->_isExpanded){
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
    bool _isExpanded=true;
    QList<FluNode*> _children;
    FluNode* _parent = nullptr;
};

class FluTreeModel : public QAbstractItemModel
{
    Q_OBJECT
    Q_PROPERTY(int max_depth READ max_depth CONSTANT)
    Q_PROPERTY_AUTO(int,dataSourceSize)
    Q_PROPERTY_AUTO(QList<FluNode*>,selectionModel)
    QML_NAMED_ELEMENT(FluTreeModel)
    QML_ADDED_IN_MINOR_VERSION(1)
public:
    explicit FluTreeModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    QModelIndex parent(const QModelIndex &child) const override;
    QModelIndex index(int row, int column,const QModelIndex &parent = QModelIndex()) const override;

    Q_INVOKABLE int max_depth(){return _max_depth;};
    Q_INVOKABLE void removeRows(int row,int count);
    Q_INVOKABLE void insertRows(int row,QList<FluNode*> data);
    Q_INVOKABLE QObject* getRow(int row);
    Q_INVOKABLE void setData(QList<FluNode*> data);
    Q_INVOKABLE void setDataSource(QList<QMap<QString,QVariant>> data);
    Q_INVOKABLE void collapse(int row);
    Q_INVOKABLE void expand(int row);
    Q_INVOKABLE void dragAnddrop(int dragIndex,int dropIndex,bool isDropTopArea);
    Q_INVOKABLE FluNode* getNode(int row);
    Q_INVOKABLE void refreshNode(int row);
    Q_INVOKABLE void checkRow(int row,bool chekced);
    Q_INVOKABLE bool hitHasChildrenExpanded(int row);
    Q_INVOKABLE void allExpand();
    Q_INVOKABLE void allCollapse();

    Q_INVOKABLE void update(char* data);
private:
    QList<FluNode*> _rows;
    QList<FluNode*> _dataSource;
    FluNode* _root = nullptr;
    int _max_depth = 0;
    QMap<int, QMetaType> _map;
    void WriteIndex();
    QString CopyValues(char* data, QMetaType& type, int offset);
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
