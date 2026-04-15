#ifndef SKELETONJOINT_P_H
#define SKELETONJOINT_P_H

#include <QtQuick3DJoltPhysics/qtquick3djoltphysicsglobal.h>
#include <QObject>
#include <QtQml/QQmlEngine>

class Q_QUICK3DJOLTPHYSICS_EXPORT SkeletonJoint : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString parentName READ parentName WRITE setParentName NOTIFY parentNameChanged)
    QML_NAMED_ELEMENT(SkeletonJoint)
public:
    explicit SkeletonJoint(QObject *parent = nullptr);
    ~SkeletonJoint() override;

    QString name() const;
    void setName(const QString &name);

    QString parentName() const;
    void setParentName(const QString &parentName);

signals:
    void nameChanged(const QString &name);
    void parentNameChanged(const QString &parentName);
    void changed();

private:
    QString m_name;
    QString m_parentName;
};

#endif // SKELETONJOINT_P_H
