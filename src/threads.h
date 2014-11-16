#ifndef __RDC_THREADS__
#define __RDC_THREADS__
#include <loki/SmartPtr.h>
#include <loki/Threads.h>

namespace Zen
{
    /**
         * @brief Стратегия без синзронизации
         */
    class NoLock
    {
    public:
        NoLock() {};
        ~NoLock() {};
    };

    extern std::mutex logMtx;
    /**
     * @brief Синхронизация через std::mutex
     */
    class MutexLock
    {
    public:
        MutexLock()
            : mLock(logMtx) {};
        ~MutexLock()
        {};

    private:
        std::lock_guard<std::mutex> mLock;
    };


    template < class Host, class MutexPolicy >
    class MutexLockerPolicy
    {
        struct Initializer
        {
            bool init_;
            std::mutex mtx_;

            Initializer() : init_(false), mtx_()
            {
                init_ = true;
            }

            ~Initializer()
            {
                assert(init_);
            }
        };

        static Initializer initializer_;

    public:

        class Lock;
        friend class Lock;

        ///  \struct Lock
        ///  Lock class to lock on class level
        class Lock
        {
        public:

            /// Lock class
            Lock()
            {
                assert(initializer_.init_);
                initializer_.mtx_.lock();
            }

            /// Lock class
            explicit Lock(const MutexLockerPolicy &)
            {
                assert(initializer_.init_);
                initializer_.mtx_.lock();
            }

            /// Lock class
            explicit Lock(const MutexLockerPolicy *)
            {
                assert(initializer_.init_);
                initializer_.mtx_.lock();
            }

            /// Unlock class
            ~Lock()
            {
                assert(initializer_.init_);
                initializer_.mtx_.unlock();
            }

        private:
            Lock(const Lock &);
            Lock &operator=(const Lock &);
        };

        typedef volatile Host VolatileType;

        /*typedef LOKI_THREADS_LONG IntType;

        LOKI_THREADS_ATOMIC_FUNCTIONS*/
    };

    template < class Host, class MutexPolicy >
    typename MutexLockerPolicy< Host, MutexPolicy >::Initializer
    MutexLockerPolicy< Host, MutexPolicy >::initializer_;
}

#endif