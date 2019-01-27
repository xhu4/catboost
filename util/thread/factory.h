#pragma once

#include <util/generic/ptr.h>
#include <functional>

class IThreadFactory {
public:
    class IThreadAble {
    public:
        inline IThreadAble() noexcept = default;

        virtual ~IThreadAble() = default;

        inline void Execute() {
            DoExecute();
        }

    private:
        virtual void DoExecute() = 0;
    };

    class IThread {
        friend class IThreadFactory;

    public:
        inline IThread() noexcept = default;

        virtual ~IThread() = default;

        inline void Join() noexcept {
            DoJoin();
        }

    private:
        inline void Run(IThreadAble* func) {
            DoRun(func);
        }

    private:
        // it's actually DoStart
        virtual void DoRun(IThreadAble* func) = 0;
        virtual void DoJoin() noexcept = 0;
    };

    inline IThreadFactory() noexcept = default;

    virtual ~IThreadFactory() = default;

    // XXX: rename to Start
    inline TAutoPtr<IThread> Run(IThreadAble* func) {
        TAutoPtr<IThread> ret(DoCreate());

        ret->Run(func);

        return ret;
    }

    TAutoPtr<IThread> Run(std::function<void()> func);

private:
    virtual IThread* DoCreate() = 0;
};

IThreadFactory* SystemThreadPool();
void SetSystemThreadPool(IThreadFactory* pool);