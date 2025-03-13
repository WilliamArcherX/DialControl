#include "dial_control.h"
#include <QPainter>
#include <QImage>

CDialControl::CDialControl(QWidget *parent) : QWidget(parent)
{
    m_anim = new Animation(this, "angle");
    m_anim->setEasingCurve(QEasingCurve::OutBounce);

    startAnimation();
}

void CDialControl::startAnimation()
{
    m_anim->setStartValue(0.0);
    m_anim->setEndValue(m_rValue);
    m_anim->setDuration(1000);
    //m_anim->setLoopCount(-1);
    m_anim->start();
}

void CDialControl::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.save();

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.setBrush(QBrush(QColor(84, 84, 84)));
    painter.drawRect(rect());

    int nCenterX = rect().width() / 2;
    int nCenterY = rect().height() / 2;
    painter.translate(nCenterX, nCenterY);

    QImage imageBK(":/rc/background.png");
    int nBKLeft = - imageBK.width() / 2 + 3;
    int nBKTop = - imageBK.height() / 2 + 9;
    QRect rcBK(nBKLeft, nBKTop, imageBK.width(), imageBK.height());
    painter.drawImage(rcBK, imageBK);

    painter.save();
    QImage imageNeedle(":/rc/needle.png");
    QImage imageNeedleShadow(":/rc/needle_shadow.png");
    int nNeedleLeft = - imageNeedle.width() / 2;
    int nNeedleTop = - imageNeedle.height();
    QRect rcNeedle(nNeedleLeft, nNeedleTop, imageNeedle.width(), imageNeedle.height());
    int nNeedleShadowLeft = - imageNeedleShadow.width() / 2;
    int nNeedleShadowTop = - imageNeedleShadow.height();
    QRect rcNeedleShadow(nNeedleShadowLeft, nNeedleShadowTop, imageNeedleShadow.width(), imageNeedleShadow.height());
    painter.rotate(m_rAngleCur);
    painter.drawImage(rcNeedleShadow, imageNeedleShadow);
    painter.drawImage(rcNeedle, imageNeedle);
    painter.restore();

    QImage imageOverlay(":/rc/overlay.png");
    int nOverlayLeft = - imageOverlay.width() / 2 - 7;
    int nOverlayTop = - imageOverlay.height() / 2 - 27;
    QRect rcOverlay(nOverlayLeft, nOverlayTop, imageOverlay.width(), imageOverlay.height());
    painter.drawImage(rcOverlay, imageOverlay);

    painter.restore();
}

void CDialControl::SetValue(qreal qValue)
{
    m_anim->setStartValue(qValue - 10);
    m_anim->setEndValue(qValue);
    m_anim->setDuration(500);
    m_anim->start();
}

void CDialControl::setAngle(double rAngle)
{
    //if (rAngle >= 0.0 && rAngle <= 120.0)
    {
        qreal rAngleNew = m_rAngleMin + rAngle * (m_rAngleMax - m_rAngleMin) / 120.0;
        m_rAngleCur = rAngleNew;

        update();

        qDebug() << "angle" << rAngle;

        emit angleChanged(m_rAngleCur);
    }
}
