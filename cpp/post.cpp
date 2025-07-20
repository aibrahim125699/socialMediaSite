
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
using namespace std;
class post{
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
    post(const string& content, const string& author) {
        postId = ++globalPostId;  
        textcontent = content;  
        authorUsername = author;
        time_t now = time(0); 
        dateTime = *localtime(&now);   
        likes = 0;
        dislikes = 0;
        comments_num = 0;
    }
    void print() const {  
        cout << "Author: " << authorUsername << endl;
        printDatetime();  
        cout << textcontent << endl;  
        cout << "Likes: " << likes << " | Dislikes: " << dislikes << endl;
        cout << "Comments: " << comments_num << endl;
    }


    void printDatetime() const {  
        cout << "Date: " << 1900 + dateTime.tm_year << "/"
             << 1 + dateTime.tm_mon << "/"
             << dateTime.tm_mday << endl;

        cout << "Time: " << (dateTime.tm_hour < 10 ? "0" : "") << dateTime.tm_hour << ":"
             << (dateTime.tm_min < 10 ? "0" : "") << dateTime.tm_min << ":";
    }
     
    void likePost(const string& username) {
        likedByUsers.push_back(username);
        likes++;
    }

    void dislikePost() {
        dislikes++;
    }
    void entertext(){
        getline(cin, textcontent);  
    }
      bool editContent(const string& newContent, const string& editorUsername) {
        if (editorUsername != authorUsername) {
            cout << "Only the author can edit this post!" << endl;
            return false;
        }
        textcontent = newContent; 
        return true;
    }
};

void writePost(string username){
    string content;
    cout << "Enter post content: ";
    getline(cin, content);
    post Newpost(content, username);  
    //press post
   
    cout << "Posted by: " << username << endl;
    Newpost.print();

}


int post::globalPostId = 0;

