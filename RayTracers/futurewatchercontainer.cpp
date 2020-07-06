#include "futurewatchercontainer.h"

FutureWatcherContainer::FutureWatcherContainer()
{
    QObject::connect(&m_FutureWatcher, SIGNAL(finished()), this, SLOT(futureFinished()));
    QObject::connect(&m_FutureWatcher, SIGNAL(progressRangeChanged(int,int)), this, SLOT(futureProgressRangeChanged(int,int)));
    QObject::connect(&m_FutureWatcher, SIGNAL(progressValueChanged(int)), this, SLOT(progressValueChanged(int)));
}

FutureWatcherContainer::~FutureWatcherContainer()
{
    QObject::disconnect(&m_FutureWatcher, SIGNAL(finished()), this, SLOT(futureFinished()));
    QObject::disconnect(&m_FutureWatcher, SIGNAL(progressRangeChanged(int,int)), this, SLOT(futureProgressRangeChanged(int,int)));
    QObject::disconnect(&m_FutureWatcher, SIGNAL(progressValueChanged(int)), this, SLOT(progressValueChanged(int)));
}

void FutureWatcherContainer::setFuture(const QFuture<void> &future)
{
    m_FutureWatcher.setFuture(future);
}

void FutureWatcherContainer::futureFinished()
{
    OnFinish();
}

void FutureWatcherContainer::futureProgressRangeChanged(int a, int b)
{
    OnProgressRangeChanged(a, b);
}

void FutureWatcherContainer::progressValueChanged(int a)
{
    OnProgressValueChanged(a);
}
