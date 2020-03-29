#ifndef DELAYEDCONTAINER_H
#define DELAYEDCONTAINER_H

#include <vector>
#include <memory>

template <typename T>
class DelayedContainer : public std::vector<std::shared_ptr<T>> {
public:
    std::shared_ptr<T> add(T* object);
    void add(std::shared_ptr<T> object);
    void remove(T *object);
    void applyPendingChanges();
private:
    enum Action {
        Add,
        Remove
    };

    struct Change {
        Action action;
        std::shared_ptr<T> object;
    };

    std::vector<Change> pending_changes;
};

#include "../src/delayedContainer.inl"
#endif