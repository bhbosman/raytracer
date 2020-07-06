#ifndef FUTUREWATCHERCONTAINER_H
#define FUTUREWATCHERCONTAINER_H

#include <QObject>
#include <boost/shared_ptr.hpp>
#include <QtConcurrent/QtConcurrent>
#include <vector>
#include "RayTracingContext_MultiThread.h"
class FutureWatcherContainer: public QObject
{
private:
    Q_OBJECT
    QFutureWatcher<void> m_FutureWatcher;
    RayTracingContext_MultiThread::shared_ptr_vector m_Data;

public:
    FutureWatcherContainer();
    virtual ~FutureWatcherContainer();
    void setFuture(const QFuture<void>& future);
    void add(const RayTracingContext_MultiThread::shared_ptr& data)
    {
        m_Data.push_back(data);
    }
    const RayTracingContext_MultiThread::const_iterator begin() const
    {
        return m_Data.begin();
    }
    const RayTracingContext_MultiThread::const_iterator end() const
    {
        return m_Data.end();
    }
    void clear()
    {
        m_Data.clear();
    }

public slots:
    void futureFinished();
    void futureProgressRangeChanged(int,int);
    void progressValueChanged(int);

signals:
    void OnFinish();
    void OnProgressRangeChanged(int,int);
    void OnProgressValueChanged(int);

public:
    typedef boost::shared_ptr<FutureWatcherContainer> shared_ptr;
    typedef std::vector<shared_ptr> shared_ptr_vec;
};

#endif // FUTUREWATCHERCONTAINER_H
