#ifndef USER_H
#define USER_H

#include <string>

class Manager;

class User
{
public:
    enum class Status
    {
        Active,
        Deactive
    };

protected:
    std::string name;
    std::string userName;
    std::string hashedPass;
    Status userStatus;

public:
    User(const std::string &name,
         const std::string &userName,
         const std::string &password,
         Status status = Status::Active);

    virtual ~User() = default;

    bool authenticate(const std::string &password) const;

    virtual void commands() = 0;

    const std::string &getUserName() const;
    const std::string &getName() const;
    Status getStatus() const;

    void setStatus(Status status);

    friend class Manager;

private:
    static std::string hashPassword(const std::string &password);
};

#endif
