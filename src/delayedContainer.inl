template <typename T>
std::shared_ptr<T> DelayedContainer<T>::add(T* object) {
    std::shared_ptr<T> ptr(object);
    add(ptr);
    return ptr;
}

template <typename T>
void DelayedContainer<T>::add(std::shared_ptr<T> object) {
    pending_changes.push_back({Add, object});
}

template <typename T>
void DelayedContainer<T>::remove(T *object) {
    pending_changes.push_back({Remove, object});
}

template <typename T>
void DelayedContainer<T>::applyPendingChanges() {
    for (auto& change : pending_changes)
        switch (change.action) {
            case Add:
                this->push_back(change.shared_object);
                break;

            case Remove:
                for (auto it = this->begin(); it != this->end(); it++)
                    if ((*it).get() == change.object) {
                        (*it).get()->setWorld(nullptr);
                        this->erase(it);
                        break;
                    }
        }

    pending_changes.clear();
}