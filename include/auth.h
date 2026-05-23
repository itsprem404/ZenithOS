#ifndef AUTH_H
#define AUTH_H

#include <string>

class Auth
{
private:
    std::string currentUser; // ✅ NEW

    std::string hashPassword(const std::string &password);
    void ensureDefaultUser();
    bool userExists(const std::string &username);

public:
    bool login();
    void registerUser();

    std::string getCurrentUser() const; // ✅ NEW
};

#endif