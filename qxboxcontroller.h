#ifndef QXBOXCONTROLLER_H
#define QXBOXCONTROLLER_H

#include "qxboxcontroller_global.h"
#include <QObject>

QT_BEGIN_NAMESPACE
class QXBoxControllerPrivate;
class QXBoxControllerEventPrivate;
class QXBoxControllerAxisEventPrivate;
class QXBoxControllerButtonEventPrivate;

class  QXBoxControllerEvent
{
    Q_DECLARE_PRIVATE(QXBoxControllerEvent)
public:
    QXBoxControllerEvent(uint controllerId);
    uint controllerId();
    ~QXBoxControllerEvent();
protected:
    QXBoxControllerEvent(uint controllerId, QXBoxControllerEventPrivate &d);
    QXBoxControllerEventPrivate* const d_ptr;
};

class  QXBoxControllerButtonEvent : public QXBoxControllerEvent
{
    Q_DECLARE_PRIVATE(QXBoxControllerButtonEvent)
public:
    QXBoxControllerButtonEvent(uint controllerId, uint button, bool pressed);
    uint button();
    bool pressed();
};

class  QXBoxControllerAxisEvent : public QXBoxControllerEvent
{
    Q_DECLARE_PRIVATE(QXBoxControllerAxisEvent)
public:
    QXBoxControllerAxisEvent(uint controllerId, uint axis, float value);
    uint axis();
    float value();
};

class  QXBoxController : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QXBoxController)
public:
    explicit QXBoxController(uint id = 0, QObject *parent = 0);
    uint axisCount();
    uint buttonCount();
    float axisValue(uint axis);
    bool buttonValue(uint button);
    QString description();
    uint id();
    bool isValid();
signals:

public slots:
    void readXBoxController();
signals:
    void XBoxControllerEvent(QXBoxControllerEvent *event);
    void XBoxControllerButtonEvent(QXBoxControllerButtonEvent *event);
    void XBoxControllerAxisEvent(QXBoxControllerAxisEvent *event);
private:
    QXBoxControllerPrivate* const d_ptr;
    Q_DISABLE_COPY(QXBoxController)
};

QT_END_NAMESPACE
#endif // QXBOXCONTROLLER_H
