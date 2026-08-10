#ifndef TOOLBOX_H
#define TOOLBOX_H

template <typename T>
class Singleton {
public:
    static T& getInstance(void) {
        static T instance;
        return instance;
    }

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    Singleton(Singleton&&) = delete;
    Singleton& operator=(Singleton&&) = delete;

protected:
    Singleton(void) = default;
    virtual ~Singleton(void) = default;
};

#endif
