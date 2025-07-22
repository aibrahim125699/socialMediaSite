#include <iostream>
#include <string>
#include <ctime>
#include <vector>

using namespace std;

// Post class declaration
class post {
private:
    static int globalPostId;
    int postId;
    string textcontent;
    string authorUsername;
    struct tm dateTime;
    int likes;
    int dislikes;
    string comment;
    int comments_num;
    vector<string> likedByUsers;

public:
    post(const string& content, const string& author);
    void print() const;
    void printDatetime() const;
    void likePost(const string& username);
    void dislikePost();
    void entertext();
    bool editContent(const string& newContent, const string& editorUsername);
    
    // Added methods for timeline and notifications compatibility
    int getUserId() const;
    time_t getTimestamp() const;
    string getContent() const;
    void displayPost() const;
    int getPostId() const;
    string getAuthor() const;
};

// Function declaration
void writePost(string username);

#endif // POST_H

// Static member initialization
int post::globalPostId = 0;

// Post class implementation
post::post(const string& content, const string& author) {
    postId = ++globalPostId;
    textcontent = content;
    authorUsername = author;
    time_t now = time(0);
    dateTime = *localtime(&now);
    likes = 0;
    dislikes = 0;
    comments_num = 0;
}

void post::print() const {
    cout << "Author: " << authorUsername << endl;
    printDatetime();
    cout << textcontent << endl;
    cout << "Likes: " << likes << " | Dislikes: " << dislikes << endl;
    cout << "Comments: " << comments_num << endl;
}

void post::printDatetime() const {
    cout << "Date: " << 1900 + dateTime.tm_year << "/"
         << 1 + dateTime.tm_mon << "/"
         << dateTime.tm_mday << endl;
    cout << "Time: " << (dateTime.tm_hour < 10 ? "0" : "") << dateTime.tm_hour << ":"
         << (dateTime.tm_min < 10 ? "0" : "") << dateTime.tm_min << ":";
}

void post::likePost(const string& username) {
    likedByUsers.push_back(username);
    likes++;
}

void post::dislikePost() {
    dislikes++;
}

void post::entertext() {
    getline(cin, textcontent);
}

bool post::editContent(const string& newContent, const string& editorUsername) {
    if (editorUsername != authorUsername) {
        cout << "Only the author can edit this post!" << endl;
        return false;
    }
    textcontent = newContent;
    return true;
}

// Added methods for timeline and notifications compatibility
int post::getUserId() const {
    int id = 0;
    for (char c : authorUsername) {
        id += c;
    }
    return id;
}

time_t post::getTimestamp() const {
    return mktime(const_cast<struct tm*>(&dateTime));
}

string post::getContent() const {
    return textcontent;
}

void post::displayPost() const {
    print();
}

int post::getPostId() const {
    return postId;
}

string post::getAuthor() const {
    return authorUsername;
}

void writePost(string username) {
    string content;
    cout << "Enter post content: ";
    getline(cin, content);
    post Newpost(content, username);
    
    cout << "Posted by: " << username << endl;
    Newpost.print();
}
