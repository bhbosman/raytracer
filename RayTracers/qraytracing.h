#ifndef QRAYTRACING_H
#define QRAYTRACING_H
#include <QObject>
#include <boost/shared_ptr.hpp>
#include "raytracing.h"
#include <qfuture.h>
#include <QtConcurrent/QtConcurrent>
#include <QFutureSynchronizer>
#include "raytracingcontext.h"
#include <vector>
//#include <QAtomicInt>
#include "FutureWatcherContainer.h"


class QRayTracing : public QObject, public RayTracing
{
private:
    Q_OBJECT
    boost::shared_ptr<QFutureSynchronizer<void>> m_Synch;
    FutureWatcherContainer::shared_ptr m_Watchers;

protected:

    virtual void DoMultiThreadedRayTracing(
            const RayTracingBlock::ptr_vec &data,
            const PixelBuffer::ptr& pixelBuffer,
            const Camera::ptr &camera,
            const Scene::ptr &scene,
            const double ie,
            const double f)  override;

public:
    QRayTracing();
    virtual ~QRayTracing()
    {

    }
    void cancel();

public slots:
    void futureFinished()
    {
        OnFinish();
        m_Watchers->clear();
//        m_Watchers = FutureWatcherContainer::shared_ptr(nullptr);

    }
    void onFutureProgressRangeChanged(int a,int b)
    {
        OnProgressRangeChanged(a, b);
    }

    void onFutureProgressValueChanged(int a)
    {
        OnProgressValueChanged(a);
    }

signals:
    void OnFinish();
    void OnProgressRangeChanged(int,int);
    void OnProgressValueChanged(int);

public:
    typedef boost::shared_ptr<QRayTracing> shared_ptr;
};

#endif // QRAYTRACING_H
