#include "qxboxcontrollerprivate.h"
#include "qxboxcontroller.h"

#include <QDebug>


QXBoxControllerPrivate::QXBoxControllerPrivate(uint id, QXBoxController *q) :
    q_ptr(q)
{
    ID=id;
    Valid=false;
    Axis=0;
    Buttons=0;
//    qDebug("QXBoxController::QXBoxController(%i)", ID);
    char number_of_axes=0;
    char number_of_buttons=0;
    QString filename = QString("/dev/input/js%1").arg(QString::number(id));
    qDebug() << "Opening" << filename.toUtf8().data();
    if( ( fd = open( filename.toUtf8().data() , O_NONBLOCK)) == -1 )
    {
        qDebug( "Couldn't open joystick\n" );
        return;
    }
    Valid=true;
    ioctl (fd, JSIOCGAXES, &number_of_axes);
    ioctl (fd, JSIOCGBUTTONS, &number_of_buttons);
    Axis=number_of_axes;
    Buttons=number_of_buttons;
    char name_of_stick[80];
    ioctl (fd, JSIOCGNAME(80), &name_of_stick);
    Description=name_of_stick;
    qDebug("Joystick: \"%s\" has %i axis and %i buttons", name_of_stick, number_of_axes, number_of_buttons);
    readXBoxController();
}

void QXBoxControllerPrivate::readXBoxController()
{
    if (!Valid)
        return;
//    qDebug() << "readJoystick";
    struct js_event e;
    while (read (fd, &e, sizeof(e)) > 0) {
        process_event (e);
    }
    /* EAGAIN is returned when the queue is empty */
    if (errno != EAGAIN) {
        qDebug() << "Error";
        Valid=false;
    }
//    else
//        qDebug() << "No event";
}

void QXBoxControllerPrivate::process_event(js_event e)
{
    Q_Q(QXBoxController);
    QXBoxControllerEvent *event = NULL;
    if (e.type & JS_EVENT_INIT)
    {
//        qDebug() << "process_event" << "event was a JS_EVENT_INIT" << e.number << e.value << e.type;
    }
    qint16 value = e.value;
//    qDebug() << "process_event" << e.number << value << e.type;
    if (e.type & JS_EVENT_BUTTON)
    {
        if (e.value==1)
        {
//            qDebug("Button %i pressed.", e.number);
        }
        else
        {
//            qDebug("Button %i released.", e.number);
        }
        event=new QXBoxControllerButtonEvent(ID, e.number, value);
        ButtonValues.insert(e.number, value);
        emit(q->XBoxControllerButtonEvent((QXBoxControllerButtonEvent*)event));
    } else if (e.type & JS_EVENT_AXIS) {
        float Value;
        if (value<0)
            Value = (float)value/32768.0;
        else
            Value = (float)value/32767.0;
        AxisValues.insert(e.number, Value);
        event=new QXBoxControllerAxisEvent(ID, e.number, Value);
//        qDebug("Axis %i moved to %f.", e.number , Value);
        emit(q->XBoxControllerAxisEvent((QXBoxControllerAxisEvent*)event));
    }
    emit(q->XBoxControllerEvent(event));
    return;
}
