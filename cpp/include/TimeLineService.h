#include "UserManager.h"
#include "Post.h"
#include <vector>
#include <algorithm>

class TimelineService {
private:
    static std::atomic<int> nextPostId;

public:
    static Post* createPost(string username, const std::string& content) {
        User* author = UserManager::getUser(username);
        if (!author) {
		return nullptr;
	}

	int postId = nextPostId++;
        Post* newPost = new Post(postId, username, content);

        author->posts.push_back(newPost);

        return newPost;
    }


static std::vector<Post*> generateTimeline(string username) {
    User* user = UserManager::getUser(username);
    if (!user) {
        return {};
    }

    std::vector<Post*> allPosts;

    allPosts.insert(allPosts.end(), user->posts.begin(), user->posts.end());

    std::vector<string> friends = user->friends.inorderTraversal();

    for (string friendUser : friends) {
	User* currentObject = UserManager::getUser(friendUser);
        allPosts.insert(allPosts.end(), currentObject->posts.begin(), currentObject->posts.end());
    }

    std::sort(allPosts.begin(), allPosts.end(), [](const Post* a, const Post* b) {
        return a->timestamp > b->timestamp;
    });


    return allPosts;
}
};


std::atomic<int> TimelineService::nextPostId(1);
