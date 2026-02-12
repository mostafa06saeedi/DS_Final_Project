#include "User.h"

User::User(const std::string& name,
           const std::string& userName,
           const std::string& password,
           Status status)
    : name(name),
      userName(userName),
      hashedPass(hashPassword(password)),
      userStatus(status) {}

bool User::authenticate(const std::string& password) const {
    if (userStatus != Status::Active)
        return false;

    return hashedPass == hashPassword(password);
}

const std::string& User::getUserName() const {
    return userName;
}

const std::string& User::getName() const {
    return name;
}

User::Status User::getStatus() const {
    return userStatus;
}

void User::setStatus(Status status) {
    userStatus = status;
}

std::string User::hashPassword(const std::string& password) {
    size_t seed = 5381;
    for (char c : password) {
        seed = ((seed << 5) + seed) + static_cast<unsigned char>(c);
    }
    return std::to_string(seed);
}