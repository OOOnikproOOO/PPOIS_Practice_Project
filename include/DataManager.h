#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <vector>
#include <memory>
#include <stdexcept>
#include <algorithm> // For std::find_if

// Template class for managing collections of objects
template <typename T>
class DataManager {
public:
    void Add(std::shared_ptr<T> item) {
        items.push_back(item);
    }

    std::shared_ptr<T> GetById(int id) const {
        auto it = std::find_if(items.begin(), items.end(), [id](const std::shared_ptr<T>& item) {
                return item->GetId() == id;
            });

        if (it != items.end()) {
            return *it;
        }
        throw std::runtime_error("Элемент с указанным ID не найден.");
    }

    const std::vector<std::shared_ptr<T>>& GetAll() const {
        return items;
    }

    void Clear() {
        items.clear();
    }

private:
    std::vector<std::shared_ptr<T>> items;
};

#endif