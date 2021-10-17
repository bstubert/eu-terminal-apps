// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include <QObject>
#include <QQmlContext>
#include <QQmlEngine>
#include <QtQuickTest>

#include "main_model.h"

class TestMainView : public QObject
{
    Q_OBJECT

    MainModel *m_mainModel;

public:
    TestMainView(QObject *parent = nullptr)
        : QObject{parent}
    {
    }

public slots:

    // TODO: Is this function called before every QML test function? Or just before the first?
    void qmlEngineAvailable(QQmlEngine *engine)
    {
        engine->rootContext()->setContextProperty(u"mainModel"_qs, m_mainModel);
    }
};

QUICK_TEST_MAIN(TestMainView)

#include "test_main_view.moc"
