#ifndef EXAMPLECHARACTERCONTACTLISTENER_H
#define EXAMPLECHARACTERCONTACTLISTENER_H

#include <QtQuick3DJoltPhysics/abstractcharactercontactlistener.h>

class ExampleCharacterContactListener : public AbstractCharacterContactListener
{
    Q_OBJECT
    Q_PROPERTY(QList<int> rampBlockIDs READ rampBlockIDs WRITE setRampBlockIDs NOTIFY rampBlockIDsChanged)
    Q_PROPERTY(bool allowSliding READ allowSliding WRITE setAllowSliding NOTIFY allowSlidingChanged)
    Q_PROPERTY(int characterBlockID READ characterBlockID WRITE setCharacterBlockID NOTIFY characterBlockIDChanged)
public:
    explicit ExampleCharacterContactListener(QObject *parent = nullptr);

    QList<int> rampBlockIDs() const;
    void setRampBlockIDs(const QList<int> &rampBlockIDs);

    bool allowSliding() const;
    void setAllowSliding(bool allowSliding);

    int characterBlockID() const;
    void setCharacterBlockID(int blockID);

    void onAdjustBodyVelocity(int bodyID2, QVector3D &linearVelocity, QVector3D &angularVelocity) override;
    void onContactAdded(const Contact &contact, CharacterContactSettings &settings) override;
    void onContactSolve(const Contact &contact, const QVector3D &contactVelocity, const QVector3D &characterVelocity, QVector3D &newCharacterVelocity, bool isSlopeToSteep) override;
    void onCharacterContactAdded(const Contact &contact, CharacterContactSettings &settings) override;
    void onCharacterContactSolve(const Contact &contact, const QVector3D &contactVelocity, const QVector3D &characterVelocity, QVector3D &newCharacterVelocity) override;

signals:
    void rampBlockIDsChanged(const QList<int> &rampBlockIDs);
    void allowSlidingChanged(bool allowSliding);
    void characterBlockIDChanged(int blockID);
    void enableSliding(bool canPushCharacter, int bodyID2);

private:
    bool m_allowSliding = false;
    QList<int> m_rampBlockIDs;
    int m_characterBlockID = 0;
};

#endif // EXAMPLECHARACTERCONTACTLISTENER_H
