#ifndef QXBOXCONTROLLERPRIVATE_H
#define QXBOXCONTROLLERPRIVATE_H

#include "qxboxcontroller.h"

#include <QMap>

#include <iostream>
#include <unistd.h>
#include <fcntl.h>
//#include <sstream>
#include <errno.h>
#include <linux/joystick.h>



QT_BEGIN_NAMESPACE



struct QXBoxControllerEventPrivate
{
    Q_DECLARE_PUBLIC(QXBoxControllerEvent)
    QXBoxControllerEventPrivate(QXBoxControllerEvent *q) : q_ptr(q) { }
    QXBoxControllerEvent * const q_ptr;
    uint ControllerId;
};


struct QXBoxControllerButtonEventPrivate : public QXBoxControllerEventPrivate
{
    Q_DECLARE_PUBLIC(QXBoxControllerButtonEvent)
    QXBoxControllerButtonEventPrivate(QXBoxControllerEvent *q) : QXBoxControllerEventPrivate(q) { }
    uint Button;
    bool Pressed;
};

struct QXBoxControllerAxisEventPrivate : public QXBoxControllerEventPrivate
{
    Q_DECLARE_PUBLIC(QXBoxControllerAxisEvent)
    QXBoxControllerAxisEventPrivate(QXBoxControllerEvent *q) : QXBoxControllerEventPrivate(q) { }
    uint Axis;
    float Value;
};



class QXBoxControllerPrivate
{
    Q_DECLARE_PUBLIC(QXBoxController)
public:
    explicit QXBoxControllerPrivate(uint id, QXBoxController *q);
    QXBoxController * const q_ptr;
protected:
    void process_event(js_event e);
public:
    int fd;
    QString Description;
    uint ID;
    bool Valid;
    QMap<uint, float> AxisValues;
    QMap<uint, bool> ButtonValues;
    uint Axis;
    uint Buttons;

    void readXBoxController();
};



QT_END_NAMESPACE


#endif // QXBOXCONTROLLERPRIVATE_H
