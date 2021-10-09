// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include "engine_twin.h"

EngineTwin::EngineTwin(QObject *parent)
    : QObject(parent)
{

}

void EngineTwin::processReceivedFrames()
{
    emit engineSpeed(930.0);
}
