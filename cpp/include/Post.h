#pragma once

#include <string>
#include <ctime>

class Post {
public:
    int postId;
    std::string authorUsername;
    std::string content;
    std::time_t timestamp;

    Post(int pId, std::string aUsername, std::string c)
        : postId(pId), authorUsername(aUsername), content(c) {
        timestamp = std::time(nullptr);
    }
};
