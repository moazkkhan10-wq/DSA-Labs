#include <iostream>
#include <string>
using namespace std;

// Node structure representing a song
struct Song {
    int id;
    string name;
    string duration; // Format MM:SS
    Song* prev;
    Song* next;

    Song(int i, string n, string d) {
        id = i;
        name = n;
        duration = d;
        prev = nullptr;
        next = nullptr;
    }
};

class Playlist {
private:
    Song* head;
    Song* tail;
    Song* current;

public:
    Playlist() {
        head = nullptr;
        tail = nullptr;
        current = nullptr;
    }

    // 1. Add Song – Insert at the end of the playlist
    void addSong(int id, string name, string duration) {
        Song* newSong = new Song(id, name, duration);
        if (head == nullptr) {
            head = tail = current = newSong;
        } else {
            tail->next = newSong;
            newSong->prev = tail;
            tail = newSong;
        }
        cout << "Added: \"" << name << "\" (" << duration << ")" << endl;
    }

    // 2. Delete Song – Remove by ID
    void deleteSong(int id) {
        if (head == nullptr) {
            cout << "Playlist is empty." << endl;
            return;
        }

        Song* temp = head;
        while (temp != nullptr && temp->id != id) {
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Song with ID " << id << " not found." << endl;
            return;
        }

        // Adjust current pointer if deleting active song
        if (temp == current) {
            current = (current->next != nullptr) ? current->next : current->prev;
        }

        if (temp == head && temp == tail) {
            head = tail = current = nullptr;
        } else if (temp == head) {
            head = head->next;
            head->prev = nullptr;
        } else if (temp == tail) {
            tail = tail->prev;
            tail->next = nullptr;
        } else {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
        }

        cout << "Deleted song: \"" << temp->name << "\"" << endl;
        delete temp;
    }

    // 3. Display Playlist Forward (First to Last)
    void displayForward() {
        if (head == nullptr) {
            cout << "Playlist is empty." << endl;
            return;
        }

        cout << "\n--- Playlist (First to Last) ---" << endl;
        Song* temp = head;
        while (temp != nullptr) {
            if (temp == current) cout << "-> ";
            else cout << "   ";
            cout << "ID: " << temp->id << " | Name: " << temp->name 
                 << " | Duration: " << temp->duration << endl;
            temp = temp->next;
        }
        cout << "---------------------------------\n";
    }

    // 4. Display Playlist Backward (Last to First)
    void displayBackward() {
        if (tail == nullptr) {
            cout << "Playlist is empty." << endl;
            return;
        }

        cout << "\n--- Playlist (Last to First) ---" << endl;
        Song* temp = tail;
        while (temp != nullptr) {
            if (temp == current) cout << "-> ";
            else cout << "   ";
            cout << "ID: " << temp->id << " | Name: " << temp->name 
                 << " | Duration: " << temp->duration << endl;
            temp = temp->prev;
        }
        cout << "---------------------------------\n";
    }

    // 5. Search Song – Search by ID and display details
    void searchSong(int id) {
        Song* temp = head;
        while (temp != nullptr) {
            if (temp->id == id) {
                cout << "\n[Song Found] ID: " << temp->id 
                     << " | Name: " << temp->name 
                     << " | Duration: " << temp->duration << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Song with ID " << id << " not found." << endl;
    }

    // 6. Play Next Song
    void playNext() {
        if (current == nullptr) {
            cout << "No active song playing." << endl;
            return;
        }
        if (current->next != nullptr) {
            current = current->next;
            cout << "Now Playing: " << current->name << " (" << current->duration << ")" << endl;
        } else {
            cout << "Already at the end of the playlist." << endl;
        }
    }

    // 6. Play Previous Song
    void playPrev() {
        if (current == nullptr) {
            cout << "No active song playing." << endl;
            return;
        }
        if (current->prev != nullptr) {
            current = current->prev;
            cout << "Now Playing: " << current->name << " (" << current->duration << ")" << endl;
        } else {
            cout << "Already at the beginning of the playlist." << endl;
        }
    }

    // 7. Reverse Playlist – In-place pointer manipulation
    void reversePlaylist() {
        if (head == nullptr || head->next == nullptr) {
            return;
        }

        Song* currentPtr = head;
        Song* temp = nullptr;

        // Swap next and prev pointers for all nodes
        while (currentPtr != nullptr) {
            temp = currentPtr->prev;
            currentPtr->prev = currentPtr->next;
            currentPtr->next = temp;
            currentPtr = currentPtr->prev; // moves to next original node
        }

        if (temp != nullptr) {
            tail = head;
            head = temp->prev;
        }

        cout << "\n[Playlist Reversed In-Place!]" << endl;
    }
};

int main() {
    Playlist myPlaylist;

    // 1. Add Songs
    myPlaylist.addSong(101, "Shape of You", "3:53");
    myPlaylist.addSong(102, "Blinding Lights", "3:20");
    myPlaylist.addSong(103, "Starboy", "3:50");

    // 3. Display Forward
    myPlaylist.displayForward();

    // 4. Display Backward
    myPlaylist.displayBackward();

    // 5. Search Song
    myPlaylist.searchSong(102);

    // 6. Play Next / Previous
    myPlaylist.playNext();
    myPlaylist.playNext();
    myPlaylist.playPrev();

    // 7. Reverse Playlist
    myPlaylist.reversePlaylist();
    myPlaylist.displayForward();

    // 2. Delete Song
    myPlaylist.deleteSong(102);
    myPlaylist.displayForward();

    return 0;
}
