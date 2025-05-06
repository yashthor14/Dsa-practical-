#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Record {
    int id;
    char name[30];  // Use fixed-size char array for binary write
    int age;
};

void insertRecord(fstream &file, int pos, const Record &record) {
    file.seekp(pos * sizeof(Record), ios::beg);
    file.write(reinterpret_cast<const char*>(&record), sizeof(Record));
    cout << "Record inserted successfully at position " << pos << endl;
}

void deleteRecord(fstream &file, int pos) {
    Record blankRecord = {0, "", 0};
    file.seekp(pos * sizeof(Record), ios::beg);
    file.write(reinterpret_cast<const char*>(&blankRecord), sizeof(Record));
    cout << "Record deleted successfully from position " << pos << endl;
}

void displayFileContents(fstream &file) {
    file.seekg(0, ios::beg);
    Record record;
    int position = 0;
    while (file.read(reinterpret_cast<char*>(&record), sizeof(Record))) {
        if (record.id != 0) {
            cout << "Position " << position
                 << ": ID = " << record.id
                 << ", Name = " << record.name
                 << ", Age = " << record.age << endl;
        }
        position++;
    }
}

int main() {
    fstream file("records.dat", ios::in | ios::out | ios::binary | ios::trunc);
    if (!file) {
        cout << "File could not be created!" << endl;
        return 1;
    }

    // Create records with fixed-size name fields
    Record r1 = {1, "", 25};
    Record r2 = {2, "", 30};
    Record r3 = {3, "", 22};
    strncpy(r1.name, "Rutja", sizeof(r1.name));
    strncpy(r2.name, "Saisha", sizeof(r2.name));
    strncpy(r3.name, "Shrinidhi", sizeof(r3.name));

    insertRecord(file, 0, r1);
    insertRecord(file, 1, r2);
    insertRecord(file, 2, r3);

    cout << "\nFile contents after insertion:\n";
    displayFileContents(file);

    deleteRecord(file, 1);

    cout << "\nFile contents after deletion:\n";
    file.clear(); // Clear EOF flag for reuse
    displayFileContents(file);

    file.close();
    return 0;
}
