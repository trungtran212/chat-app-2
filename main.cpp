#include "user.h"
#include "server.h"
#include "client.h"
#include <iostream>

using namespace std;

int main() {
    int choice;
    cout << "1. Run as Server\n2. Run as Client\n3. Sign Up\n";
    cin >> choice;
    cin.ignore();  // Đọc ký tự newline còn sót lại

    if (choice == 1) {
        runServer();
    } else if (choice == 2) {
        if (signIn()) {
            runClient();
        } else {
            cout << "Invalid login.\n";
        }
    } else if (choice == 3) {
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        if (signUp(username, password)) {
            cout << "Sign up successful.\n";
        } else {
            cout << "Sign up failed.\n";
        }
    } 
    else {
        cout << "Invalid choice.\n";
    }

    return 0;
}
