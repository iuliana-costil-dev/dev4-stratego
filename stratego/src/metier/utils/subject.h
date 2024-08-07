#ifndef SUBJECT_H
#define SUBJECT_H

#include <set>
#include <string>

namespace stratego::utils {

class Observer;

/**
* @brief Interface used to implement Observer pattern, describes the behavior of our Subject class, Game
*/
class Subject {
private:
    std::set<Observer *> _observers{};

public:
    virtual ~Subject() = default;    // polymorphism

    //void notify() const;
    /**
     * Notifys all of its observers if the object has changed.
     * @param propertyName the name of the change.
     */
    void notify(const std::string &propertyName = "No property") const;

    /**
    * Adds an observer to the set of observers for this object.
    *
    */
    inline void addObserver(Observer *);

    /**
    * Deletes an observer to the set of observers for this object.
    *
    */
    inline void deleteObserver(Observer *);
};

// implements inline methods
void Subject::addObserver(Observer *observer) {
    _observers.insert(observer);
}

void Subject::deleteObserver(Observer *observer) {
    _observers.erase(observer);
}

}

#endif // SUBJECT_H
