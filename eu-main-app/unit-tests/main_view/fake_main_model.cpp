// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include "fake_main_model.h"

FakeMainModel::FakeMainModel(QObject *parent)
    : MainModel{parent}
{
}

void FakeMainModel::setEngineSpeed(qreal rpm)
{
    MainModel::setEngineSpeed(Quantity{rpm, u"rpm"_qs});
}
