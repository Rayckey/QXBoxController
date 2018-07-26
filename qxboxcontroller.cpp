#include "qxboxcontroller.h"
#include "qxboxcontrollerprivate.h"

#include <QDebug>


QXBoxControllerEvent::QXBoxControllerEvent(uint controllerId):
    d_ptr(new QXBoxControllerEventPrivate(this))
{
    Q_D(QXBoxControllerEvent);
    d->ControllerId=controllerId;
}


QXBoxControllerEvent::QXBoxControllerEvent(uint controllerId, QXBoxControllerEventPrivate &d)
    :d_ptr(&d)
{
    d.ControllerId=controllerId;
}

uint QXBoxControllerEvent::controllerId()
{
    Q_D(QXBoxControllerEvent);
    return d->ControllerId;
}

QXBoxControllerEvent::~QXBoxControllerEvent()
{
    delete d_ptr;
}

QXBoxControllerButtonEvent::QXBoxControllerButtonEvent(uint controllerId, uint button, bool pressed)
    : QXBoxControllerEvent(controllerId, *new QXBoxControllerButtonEventPrivate(this))
{
    Q_D(QXBoxControllerButtonEvent);
    d->Button=button;
    d->Pressed=pressed;
}

uint QXBoxControllerButtonEvent::button()
{
    Q_D(QXBoxControllerButtonEvent);
    return d->Button;
}

bool QXBoxControllerButtonEvent::pressed()
{
    Q_D(QXBoxControllerButtonEvent);
    return d->Pressed;
}

QXBoxControllerAxisEvent::QXBoxControllerAxisEvent(uint controllerId, uint axis, float value)
    : QXBoxControllerEvent(controllerId, *new QXBoxControllerAxisEventPrivate(this))
{
    Q_D(QXBoxControllerAxisEvent);
    d->Axis=axis;
    d->Value=value;
}

uint QXBoxControllerAxisEvent::axis()
{
    Q_D(QXBoxControllerAxisEvent);
    return d->Axis;
}

float QXBoxControllerAxisEvent::value()
{
    Q_D(QXBoxControllerAxisEvent);
    return d->Value;
}

QXBoxController::QXBoxController(uint id, QObject *parent) :
    QObject(parent), d_ptr(new QXBoxControllerPrivate(id, this))
{

}

uint QXBoxController::axisCount()
{
    Q_D(QXBoxController);
    return d->Axis;
}

uint QXBoxController::buttonCount()
{
    Q_D(QXBoxController);
    return d->Buttons;
}

float QXBoxController::axisValue(uint axis)
{
    Q_D(QXBoxController);
    return d->AxisValues.value(axis);
}

bool QXBoxController::buttonValue(uint button)
{
    Q_D(QXBoxController);
    return d->ButtonValues.value(button);
}

QString QXBoxController::description()
{
    Q_D(QXBoxController);
    return d->Description;
}

uint QXBoxController::id()
{
    Q_D(QXBoxController);
    return d->ID;
}

bool QXBoxController::isValid()
{
    Q_D(QXBoxController);
    return d->Valid;
}

void QXBoxController::readXBoxController()
{
    Q_D(QXBoxController);
    d->readXBoxController();
}
