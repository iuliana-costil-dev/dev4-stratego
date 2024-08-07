#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>

namespace stratego::utils {
/**
* @brief Interface used to implement Observer pattern, describes the behavior of our Observer classes
*/
class Observer {

public:
    //destructor
    virtual ~Observer() = default;
    /**
     * Called when an observer is notified of a change.
     * @param The name of the change
     */
    virtual void update(const std::string &message) = 0;
};

}

#endif // OBSERVER_H
