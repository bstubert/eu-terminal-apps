// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#pragma once

#include <QObject>

#include "quantity.h"

class MainModel : public QObject
{
    Q_OBJECT

public:
    explicit MainModel(QObject *parent = nullptr);

    void setEngineSpeed(const Quantity &rpm);
    Quantity engineSpeed() const;

private:
    Quantity m_engineSpeed;
};
