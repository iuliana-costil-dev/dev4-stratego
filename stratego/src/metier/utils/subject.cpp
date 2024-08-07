#include "subject.h"
#include "observer.h"
#include <string>

namespace stratego::utils {

void Subject::notify(const std::string &message) const {
    for (auto *observer : _observers) {
        observer->update(message);
    }
}

}
