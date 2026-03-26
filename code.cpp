/*
Library Management System
--------------------------
Description:
Develop a system to manage books in a library using basic feature of C++ in the main class
----------------------------
ID:
1.Add new books
2.Issue book
3.Return book
4.Search book
5.Display available books
------------------------------
Example Books:
1	No Shadow Without Light	Luke Gracias
2	One Arranged Murder	Chetan Bhagat
3	Twisted Love	Ana Huang
4	Twisted Games	Ana Huang
5	Twisted Hate	Ana Huang
6	Twisted Lies	Ana Huang
7	It Ends With Us	Collen Hover
8	It Starts With Us	Collen Hover
9	The Spanish Love Deception	Elena Armas
10  Too Good Too Be True Prajakta Kohli
*/

#include<bits/stdc++.h>
using namespace std;

int main(){

    string title[50];
    string author[50];
    int issued[50]; 

    // Waiting list
    string waitName[100];
    int waitBookID[100];
    int waitCount = 0;

    // Sample Books
    title[0] = "No Shadow Without Light";    author[0] = "Luke Gracias";    issued[0] = 0;
    title[1] = "One Arranged Murder";        author[1] = "Chetan Bhagat";   issued[1] = 0;
    title[2] = "Twisted Love";               author[2] = "Ana Huang";       issued[2] = 0;
    title[3] = "Twisted Games";              author[3] = "Ana Huang";       issued[3] = 0;
    title[4] = "Twisted Hate";               author[4] = "Ana Huang";       issued[4] = 0;
    title[5] = "Twisted Lies";               author[5] = "Ana Huang";       issued[5] = 0;
    title[6] = "It Ends With Us";            author[6] = "Colleen Hoover";  issued[6] = 0;
    title[7] = "It Starts With Us";          author[7] = "Colleen Hoover";  issued[7] = 0;
    title[8] = "The Spanish Love Deception"; author[8] = "Elena Armas";     issued[8] = 0;
    title[9] = "Too Good To Be True";        author[9] = "Prajakta Kohli";  issued[9] = 0;

    int totalBooks = 10;
    int choice, id;

    cout << "\n--- Welcome to Library Management System ---\n";

    do{

        cout << "\n1. Add Book";
        cout << "\n2. Issue Book";
        cout << "\n3. Return Book";
        cout << "\n4. Search Book";
        cout << "\n5. Display All Books";
        cout << "\n6. View Waiting List";
        cout << "\n0. Exit";
        cout << "\n\nEnter choice: ";
        cin >> choice;

        // If user types a letter or bad input, cin fails -> clear it
        if(cin.fail()){
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input! Enter a number.\n";
            continue;
        }

        cin.ignore(1000, '\n');

        switch(choice){

            // Add Book
            case 1:
                if(totalBooks >= 50){
                    cout << "Library is full!\n";
                    break;
                }
                cout << "\nEnter Title  : ";
                getline(cin, title[totalBooks]);
                cout << "Enter Author : ";
                getline(cin, author[totalBooks]);
                issued[totalBooks] = 0;
                totalBooks++;
                cout << "Book added successfully!\n";
                break;

            // Issue Book
            case 2:
                cout << "\nEnter Book ID to issue (1 to " << totalBooks << "): ";
                cin >> id;
                cin.ignore(1000, '\n');
                id = id - 1;

                if(id < 0 || id >= totalBooks){
                    cout << "Invalid ID!\n";
                }
                else if(issued[id] == 1){
                    cout << "Book is already issued!\n";
                    cout << "Do you want to join the waiting list? (1=Yes / 0=No): ";
                    int joinWait;
                    cin >> joinWait;
                    cin.ignore(1000, '\n');
                    if(joinWait == 1){
                        cout << "Enter your name: ";
                        getline(cin, waitName[waitCount]);
                        waitBookID[waitCount] = id + 1;
                        waitCount++;
                        cout << "You have been added to the waiting list!\n";
                    }
                }
                else{
                    issued[id] = 1;
                    cout << "Book issued successfully!\n";
                }
                break;

            // Return Book
            case 3:
                cout << "\nEnter Book ID to return (1 to " << totalBooks << "): ";
                cin >> id;
                cin.ignore(1000, '\n');
                id = id - 1;

                if(id < 0 || id >= totalBooks){
                    cout << "Invalid ID!\n";
                }
                else if(issued[id] == 0){
                    cout << "Book was not issued!\n";
                }
                else{
                    issued[id] = 0;
                    cout << "Book returned successfully!\n";

                    // Check if anyone is waiting for this book
                    for(int i = 0; i < waitCount; i++){
                        if(waitBookID[i] == id + 1){
                            cout << "** Notice: " << waitName[i]
                                 << " is waiting for this book! **\n";
                        }
                    }
                }
                break;

            // Search Book
            case 4:
                cout << "\nEnter Book ID to search (1 to " << totalBooks << "): ";
                cin >> id;
                cin.ignore(1000, '\n');
                id = id - 1;

                if(id < 0 || id >= totalBooks){
                    cout << "Invalid ID!\n";
                }
                else{
                    cout << "\n";
                    cout << left << setw(5)  << "ID"
                                 << setw(35) << "Title"
                                 << setw(20) << "Author"
                                 << "Status" << "\n";
                    cout << string(70, '-') << "\n";
                    cout << left << setw(5)  << id+1
                                 << setw(35) << title[id]
                                 << setw(20) << author[id]
                                 << (issued[id] == 0 ? "Available" : "Issued") << "\n";
                }
                break;

            // Display All Books
            case 5:
                cout << "\n";
                cout << left << setw(5)  << "ID"
                             << setw(35) << "Title"
                             << setw(20) << "Author"
                             << "Status" << "\n";
                cout << string(70, '-') << "\n";

                for(int i = 0; i < totalBooks; i++){
                    cout << left << setw(5)  << i+1
                                 << setw(35) << title[i]
                                 << setw(20) << author[i]
                                 << (issued[i] == 0 ? "Available" : "Issued") << "\n";
                }
                cout << string(70, '-') << "\n";
                cout << "Total Books: " << totalBooks << "\n";
                break;

            // View Waiting List
            case 6:
                cout << "\n";
                if(waitCount == 0){
                    cout << "No one is on the waiting list!\n";
                }
                else{
                    cout << left << setw(5)  << "No."
                                 << setw(25) << "Name"
                                 << setw(5)  << "Book ID"
                                 << "Book Title" << "\n";
                    cout << string(70, '-') << "\n";

                    for(int i = 0; i < waitCount; i++){
                        cout << left << setw(5)  << i+1
                                     << setw(25) << waitName[i]
                                     << setw(8)  << waitBookID[i]
                                     << title[waitBookID[i]-1] << "\n";
                    }
                    cout << string(70, '-') << "\n";
                    cout << "Total Waiting: " << waitCount << "\n";
                }
                break;

            // Exit
            case 0:
                cout << "\nGoodbye!\n";
                break;

            default:
                cout << "Invalid choice! Enter 0 to 6.\n";
        }

    }while(choice != 0);

    return 0;
}