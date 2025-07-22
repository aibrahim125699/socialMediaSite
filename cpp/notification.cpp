#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;


class notification {
private:
    static int globalNotificationId;
    int notificationId;
    int userId;
    string type;
    string message;
    string fromUser;
    time_t timestamp;
    bool isRead;

public:
    notification(int user_id, const string& notification_type, const string& msg, const string& from_user);
    void print() const;
    void markRead();
    int getId() const;
    int getUserId() const;
    string getType() const;
    bool getReadStatus() const;
    time_t getTimestamp() const;
};


class notificationManager {
private:
    vector<notification> notifications;

public:
    notificationManager();
    void createFriendRequestNotification(int userId, const string& fromUser);
    void createFriendAcceptedNotification(int userId, const string& fromUser);
    void createNewPostNotification(int userId, const string& fromUser);
    vector<notification> getUserNotifications(int userId);
    vector<notification> getUnreadNotifications(int userId);
    void markAsRead(int notificationId);
    void markAllAsRead(int userId);
    void displayNotifications(int userId, bool unreadOnly = false);
    int getUnreadCount(int userId);
    void clearOldNotifications(int daysOld = 30);
};



int notification::globalNotificationId = 0;

notification::notification(int user_id, const string& notification_type, const string& msg, const string& from_user) {
    notificationId = ++globalNotificationId;
    userId = user_id;
    type = notification_type;
    message = msg;
    fromUser = from_user;
    timestamp = time(0);
    isRead = false;
}

void notification::print() const {
    cout << "[" << (isRead ? "READ" : "UNREAD") << "] ";
    cout << message << " - from " << fromUser;
    struct tm* timeinfo = localtime(&timestamp);
    cout << " (" << 1900 + timeinfo->tm_year << "/" << 1 + timeinfo->tm_mon << "/" << timeinfo->tm_mday << ")";
    cout << endl;
}

void notification::markRead() {
    isRead = true;
}

int notification::getId() const {
    return notificationId;
}

int notification::getUserId() const {
    return userId;
}

string notification::getType() const {
    return type;
}

bool notification::getReadStatus() const {
    return isRead;
}

time_t notification::getTimestamp() const {
    return timestamp;
}

// Notification Manager implementation
notificationManager::notificationManager() {}

void notificationManager::createFriendRequestNotification(int userId, const string& fromUser) {
    string message = "New friend request";
    notification notif(userId, "friend_request", message, fromUser);
    notifications.push_back(notif);
}

void notificationManager::createFriendAcceptedNotification(int userId, const string& fromUser) {
    string message = "Friend request accepted";
    notification notif(userId, "friend_accepted", message, fromUser);
    notifications.push_back(notif);
}

void notificationManager::createNewPostNotification(int userId, const string& fromUser) {
    string message = "Posted a new update";
    notification notif(userId, "post", message, fromUser);
    notifications.push_back(notif);
}

vector<notification> notificationManager::getUserNotifications(int userId) {
    vector<notification> userNotifs;
    for (int i = 0; i < notifications.size(); i++) {
        if (notifications[i].getUserId() == userId) {
            userNotifs.push_back(notifications[i]);
        }
    }
    
    // Sort by timestamp (newest first) - bubble sort
    for (int i = 0; i < userNotifs.size() - 1; i++) {
        for (int j = i + 1; j < userNotifs.size(); j++) {
            if (userNotifs[i].getTimestamp() < userNotifs[j].getTimestamp()) {
                notification temp = userNotifs[i];
                userNotifs[i] = userNotifs[j];
                userNotifs[j] = temp;
            }
        }
    }
    
    return userNotifs;
}

vector<notification> notificationManager::getUnreadNotifications(int userId) {
    vector<notification> unread;
    for (int i = 0; i < notifications.size(); i++) {
        if (notifications[i].getUserId() == userId && !notifications[i].getReadStatus()) {
            unread.push_back(notifications[i]);
        }
    }
    return unread;
}

void notificationManager::markAsRead(int notificationId) {
    for (int i = 0; i < notifications.size(); i++) {
        if (notifications[i].getId() == notificationId) {
            notifications[i].markRead();
            break;
        }
    }
}

void notificationManager::markAllAsRead(int userId) {
    for (int i = 0; i < notifications.size(); i++) {
        if (notifications[i].getUserId() == userId) {
            notifications[i].markRead();
        }
    }
}

void notificationManager::displayNotifications(int userId, bool unreadOnly) {
    cout << "\n=== NOTIFICATIONS ===" << endl;
    vector<notification> userNotifs = getUserNotifications(userId);
    
    if (userNotifs.empty()) {
        cout << "No notifications." << endl;
        return;
    }

    for (int i = 0; i < userNotifs.size(); i++) {
        if (!unreadOnly || !userNotifs[i].getReadStatus()) {
            userNotifs[i].print();
        }
    }
}

int notificationManager::getUnreadCount(int userId) {
    int count = 0;
    for (int i = 0; i < notifications.size(); i++) {
        if (notifications[i].getUserId() == userId && !notifications[i].getReadStatus()) {
            count++;
        }
    }
    return count;
}

void notificationManager::clearOldNotifications(int daysOld) {
    time_t currentTime = time(0);
    time_t cutoffTime = currentTime - (daysOld * 24 * 60 * 60);
    
    vector<notification> newNotifications;
    for (int i = 0; i < notifications.size(); i++) {
        if (notifications[i].getTimestamp() >= cutoffTime) {
            newNotifications.push_back(notifications[i]);
        }
    }
    notifications = newNotifications;
}