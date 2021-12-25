// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include <memory>

#include <QObject>
#include <QQmlContext>
#include <QQmlEngine>
#include <QtQuickTest>

#include "main_model.h"

class FixtureMainView : public QObject
{
    Q_OBJECT
    Q_PROPERTY(MainModel *mainModel READ mainModel CONSTANT)

public:
    MainModel *mainModel() const;

public slots:
    void qmlEngineAvailable(QQmlEngine *engine);

private:
    std::unique_ptr<MainModel> m_mainModel;
};

MainModel *FixtureMainView::mainModel() const
{
    return m_mainModel.get();
}

void FixtureMainView::qmlEngineAvailable(QQmlEngine *engine)
{
    qmlRegisterType<MainModel>("EmUse.Models", 0, 1, "MainModel");
    m_mainModel.reset(new MainModel{});
    engine->rootContext()->setContextProperty("BusinessLogic", this);
}

QUICK_TEST_MAIN_WITH_SETUP(TestMainView, FixtureMainView)

#include "test_main_view.moc"
