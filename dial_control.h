#ifndef CDIALCONTROL_H
#define CDIALCONTROL_H

#include <QWidget>
#include "animation.h"

class CDialControl : public QWidget
{
    Q_OBJECT
public:
    explicit CDialControl(QWidget *parent = nullptr);    

    Q_PROPERTY(qreal angle READ angle WRITE setAngle NOTIFY angleChanged)

    void SetValue(qreal qValue);

signals:

protected:
    void paintEvent(QPaintEvent *event);

    void setAngle(double rAngle);
    qreal angle() const { return m_rAngleCur; }

signals:
    void angleChanged(qreal);

private:
    void startAnimation();

private:
    qreal m_rAngleMin = -132;
    qreal m_rAngleMax = 135;
    qreal m_rAngleCur = 0.0;

    qreal m_rValue = 60.0;

    Animation *m_anim = nullptr;
};

#endif // CDIALCONTROL_H
