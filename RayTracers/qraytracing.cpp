#include "qraytracing.h"
#include "raytracingcontext.h"
#include "RayTracingContext_MultiThread.h"

void hello2(const RayTracingContext_MultiThread::shared_ptr& data)
{
    if (data.get() != nullptr)
    {
        data->runInternal();
    }
}


QRayTracing::QRayTracing(): QObject(), RayTracing()
{

}


void waitForSyncObject(const boost::shared_ptr<QFutureSynchronizer<void>> &synch)
{
    synch->waitForFinished();
    synch->clearFutures();
}

void destroySyncObject(const boost::shared_ptr<QFutureSynchronizer<void>> &synch)
{
    synch->clearFutures();
}


void QRayTracing::cancel()
{
    if (m_Synch.get() != nullptr)
    {
        ///
        /// \brief synch_local
        ///Two steps:
        /// 1. stop all previous futures, and wait for them to finish
        /// 2. destroy previous features on another thread
        ///
        QFutureSynchronizer<void> synch_local;
        QFuture<void> future_local = QtConcurrent::run(waitForSyncObject, m_Synch);
        synch_local.addFuture(future_local);
        synch_local.waitForFinished();
        //
        QtConcurrent::run(destroySyncObject, m_Synch);
    }
}








void QRayTracing::DoMultiThreadedRayTracing(
        const RayTracingBlock::ptr_vec &data,
        const PixelBuffer::ptr &pixelBuffer,
        const Camera::ptr &camera,
        const Scene::ptr &scene,
        const double ie,
        const double f)
{
    cancel();

    m_Synch = boost::shared_ptr<QFutureSynchronizer<void>>(new QFutureSynchronizer<void>());
    m_Synch->setCancelOnWait(true);
    ///
    /// This must be destroyed on the same thread where the connections were made
    ///
//    m_Watchers.clear();

    pixelBuffer->clear();

    boost::shared_ptr<QAtomicInt> atomic_local(new QAtomicInt(0));
    {
        ///
        /// \brief stackVariable
        /// This variable is used to take a reference and then to release is
        /// when the local stack out
        /// \return
        ///

        FutureWatcherContainer* fut = new FutureWatcherContainer();
        m_Watchers = FutureWatcherContainer::shared_ptr(fut);
        QObject::connect(fut, SIGNAL(OnFinish()), this, SLOT(futureFinished()));
        QObject::connect(fut, SIGNAL(OnProgressRangeChanged(int,int)), this, SLOT(onFutureProgressRangeChanged(int,int)));
        QObject::connect(fut, SIGNAL(OnProgressValueChanged(int)), this, SLOT(onFutureProgressValueChanged(int)));


//        RayTracingContext_MultiThread::shared_ptr_vector *seq  = new RayTracingContext_MultiThread::shared_ptr_vector();

        for(
            RayTracingBlock::ptr_vec::const_iterator it = data.begin();
            it != data.end();
            ++it)
        {

            const RayTracingBlock::ptr entry_ptr = *it;
            RayTracingContext_MultiThread* ptr = new RayTracingContext_MultiThread(
                        pixelBuffer,
                        camera,
                        scene,
                        ie,
                        f,
                        entry_ptr,
                        m_DoBumpMapping,
                        m_Shadowing,
                        m_Reflection,
                        m_SuperSampling,
                        m_Interception);
            RayTracingContext_MultiThread::shared_ptr shared_ptr(ptr);
            fut->add(shared_ptr);
        }
        QFuture<void> future = QtConcurrent::map(fut->begin(), fut->end(), hello2);
        m_Synch->addFuture(future);

        fut->setFuture(future);

    }
}


