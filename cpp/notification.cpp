#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

class notification {
private:
    static int globalId;
    int id;
    int userId;
    string message;
    time_t timestamp;
    bool isRead;

public:
    notification(int user_id, const string& msg);
    void print() const;
    void markRead();
    int getId() const { return id; }
    int getUserId() const { return userId; }
    bool getReadStatus() const { return isRead; }
    time_t getTimestamp() const { return timestamp; }
};

class notificationManager {
private:
    vector<notification> notifications;

public:
    void addNotification(int userId, const string& message);
    vector<notification> getUserNotifications(int userId);
    void markAsRead(int notificationId);
    void displayNotifications(int userId);
    int getUnreadCount(int userId);
};

int notification::globalId = 0;

notification::notification(int user_id, const string& msg) {
    id = ++globalId;
    userId = user_id;
    message = msg;
    timestamp = time(0);
    isRead = false;
}

void notification::print() const {
    cout << "[" << (isRead ? "READ" : "UNREAD") << "] " << message;
    struct tm* t = localtime(&timestamp);
    cout << " (" << 1900 + t->tm_year << "/" << 1 + t->tm_mon << "/" << t->tm_mday << ")" << endl;
}

void notification::markRead() {
    isRead = true;
}

void notificationManager::addNotification(int userId, const string& message) {
    notifications.push_back(notification(userId, message));
}

vector<notification> notificationManager::getUserNotifications(int userId) {
    vector<notification> result;
    for (int i = 0; i < notifications.size(); i++) {
        if (notifications[i].getUserId() == userId) {
            result.push_back(notifications[i]);
        }
    }
    return result;
}

void notificationManager::markAsRead(int notificationId) {
    for (int i = 0; i < notifications.size(); i++) {
        if (notifications[i].getId() == notificationId) {
            notifications[i].markRead();
            break;
        }
    }
}

void notificationManager::displayNotifications(int userId) {
    cout << "\n=== NOTIFICATIONS ===" << endl;
    vector<notification> userNotifs = getUserNotifications(userId);
    
    if (userNotifs.empty()) {
        cout << "No notifications." << endl;
        return;
    }

    for (int i = 0; i < userNotifs.size(); i++) {
        userNotifs[i].print();
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
