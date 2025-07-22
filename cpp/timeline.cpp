#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>

using namespace std;


class post;


class timelineManager {
private:
    vector<post*> allPosts;

public:
    timelineManager();
    ~timelineManager();
    void addPost(post* newPost);
    vector<post*> getUserPosts(int userId);
    vector<post*> generateTimeline(int userId, const vector<int>& friendIds);
    void displayTimeline(const vector<post*>& timeline, int maxPosts = 10);
    vector<post*> searchPosts(const string& keyword);
    vector<post*> getRecentPosts(int count = 5);
};




timelineManager::timelineManager() {}

timelineManager::~timelineManager() {
    
}

void timelineManager::addPost(post* newPost) {
    if (newPost != nullptr) {
        allPosts.push_back(newPost);
    }
}

vector<post*> timelineManager::getUserPosts(int userId) {
    vector<post*> userPosts;
    for (int i = 0; i < allPosts.size(); i++) {
        if (allPosts[i] != nullptr && allPosts[i]->getUserId() == userId) {
            userPosts.push_back(allPosts[i]);
        }
    }
    return userPosts;
}

vector<post*> timelineManager::generateTimeline(int userId, const vector<int>& friendIds) {
    vector<post*> timeline;
    
  
    vector<post*> ownPosts = getUserPosts(userId);
    for (int i = 0; i < ownPosts.size(); i++) {
        timeline.push_back(ownPosts[i]);
    }
    
   
    for (int i = 0; i < friendIds.size(); i++) {
        vector<post*> friendPosts = getUserPosts(friendIds[i]);
        for (int j = 0; j < friendPosts.size(); j++) {
            timeline.push_back(friendPosts[j]);
        }
    }
    
    
    for (int i = 0; i < timeline.size() - 1; i++) {
        for (int j = i + 1; j < timeline.size(); j++) {
            if (timeline[i]->getTimestamp() < timeline[j]->getTimestamp()) {
                post* temp = timeline[i];
                timeline[i] = timeline[j];
                timeline[j] = temp;
            }
        }
    }
    
    return timeline;
}

void timelineManager::displayTimeline(const vector<post*>& timeline, int maxPosts) {
    cout << "\n=== TIMELINE ===" << endl;
    if (timeline.empty()) {
        cout << "No posts to display." << endl;
        return;
    }

    int count = 0;
    for (int i = 0; i < timeline.size() && count < maxPosts; i++) {
        if (timeline[i] != nullptr) {
            timeline[i]->displayPost();
            count++;
        }
    }
}


