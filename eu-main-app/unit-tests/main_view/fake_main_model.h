// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#pragma once

#include "main_model.h"

class FakeMainModel : public MainModel
{
    Q_OBJECT

public:
    FakeMainModel(QObject *parent = nullptr);

public slots:
    void setEngineSpeed(qreal rpm);
};
