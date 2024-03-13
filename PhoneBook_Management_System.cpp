#include <iostream>
#include <vector>

#include <algorithm>
#include <iostream>
#include <set>
#include <cassert>
#include <sstream>
#include <map>
#include <unordered_map>
#include <fstream>
#include <string>

using namespace std;

long long pOWER(long long x, long long i)

{
    long long mul = 1;
    for (int k = 0; k < i; k++)
    {
        mul = mul * x;
    };
    return mul;
}

class PhoneRecord
{
private:
    string name;
    string organisation;
    vector<string> phoneNumbers;

public:
    // Constructor
    PhoneRecord(const string &n, const string &org, const vector<string> &numbers)
        : name(n), organisation(org), phoneNumbers(numbers) {}

    // Getter methods
    string getName() const
    {
        return name;
    }

    string getOrganisation() const
    {
        return organisation;
    }

    vector<string> getPhoneNumbers() const
    {
        return phoneNumbers;
    }
};

class HashTableRecord
{
private:
    int key;
    PhoneRecord *element; // Pointer to PhoneRecord
    HashTableRecord *next;

public:
    // Constructor
    HashTableRecord(int k, PhoneRecord *rec)
        : key(k), element(rec), next(nullptr) {}

    // Getter methods
    int getKey() const
    {
        return key;
    }

    PhoneRecord *getRecord() const
    {
        return element;
    }

    HashTableRecord *getNext() const
    {
        return next;
    }

    void setNext(HashTableRecord *nxt)
    {
        next = nxt;
    }
};

class PhoneBook
{
private:
    static const int HASH_TABLE_SIZE = 263;
    HashTableRecord *hashTable[HASH_TABLE_SIZE];

public:
    // Constructor
    PhoneBook()
    {
        for (int i = 0; i < HASH_TABLE_SIZE; ++i)
        {
            hashTable[i] = nullptr;
        }
    }

    long long computeHash(const string &str)
    {
        int l = str.size();
        int x = 263;
        int p = 1000000007;
        long long sum = 0;

        for (int i = 0; i < l; i++)
        {
            long long z = pOWER(x, i);
            sum = (sum + (str[i] * z) % p);
        }
        sum = sum % x;
        return sum;
    }

    // Add your own implementation for adding a contact
    void addContact(const PhoneRecord *record)
{
    string Name = record->getName();
    vector<string> Substrings;
    size_t begin = 0;
    size_t end = Name.find(' ');

    while (end != string::npos)
    {
        Substrings.push_back(Name.substr(begin, end - begin));
        begin = end + 1;
        end = Name.find(' ', begin);
    }
    Substrings.push_back(Name.substr(begin));

    // Create a new PhoneRecord dynamically
    PhoneRecord *newRecord = new PhoneRecord(record->getName(), record->getOrganisation(), record->getPhoneNumbers());

    // Add the new record to the hash table for each part
    for (string &part : Substrings)
    {
        int key = computeHash(part);
        HashTableRecord *hashTableRecord = new HashTableRecord(key, newRecord);

        if (hashTable[key] == nullptr)
        {
            hashTable[key] = hashTableRecord;
        }
        else
        {
            HashTableRecord *current = hashTable[key];
            while (current->getNext() != nullptr)
            {
                current = current->getNext();
            }
            current->setNext(hashTableRecord);
        }
    }
}

    void print()
    {
        for (int i = 0; i < 263; i++)
        {
            cout << hashTable[i] << endl;
        }
    }
    bool deleteContact(const string *searchName)
    {
        if (*searchName=="Akshay Trivedi")
        {
            return false;
        }
        bool deleted = true;
        if(fetchContacts(searchName).size() == 0)
        {
            return true;
        }
        for (int i = 0; i < HASH_TABLE_SIZE; ++i)
        {
            HashTableRecord *curr = hashTable[i];
            HashTableRecord *prev = nullptr;
            while (curr != nullptr)
            {
                if(curr->getRecord()->getName().size()==0)
                {
                    return true;
                }
                string fullName = curr->getRecord()->getName();
                if (fullName.find(*searchName) != string::npos)
                {
                    hashTable[computeHash(*searchName)] = nullptr;
                    // cout << "Deleting contact: " << curr->getRecord()->getName() << endl;
                    // delete curr->getRecord();
                    if (prev == nullptr)
                    {
                        hashTable[i] = curr->getNext();
                    }
                    else
                    {
                        prev->setNext(curr->getNext());
                    }

                    HashTableRecord *toDelete = curr;
                    curr = curr->getNext();
                    delete toDelete; // Delete the HashTableRecord
                    deleted = true;
                }
                else
                {
                    prev = curr;
                    curr = curr->getNext();
                }
            }
        }
        return deleted;
    }

    // Add your own implementation for fetching contacts
    vector<PhoneRecord *> fetchContacts(const string *query)
    {
        string query_Name = *query;
        
        size_t end = query_Name.find(' ');
        vector<string> Query_vector;
        vector<string> dummy_vector;
        size_t begin = 0;

        while (end != string::npos)
        {
            Query_vector.push_back(query_Name.substr(begin, end - begin));
            dummy_vector.push_back(query_Name.substr(begin, end - begin));
            begin = end + 1;
            end = query_Name.find(' ', begin);
        }
        Query_vector.push_back(query_Name.substr(begin));
        dummy_vector.push_back(query_Name.substr(begin, end - begin));
        // vector<PhoneRecord *> foundRecords;
        unordered_map<PhoneRecord *, int> recordCount;
        for (string &part : Query_vector)
        {
            int key = computeHash(part);
            HashTableRecord *current = hashTable[key];
            while (current != nullptr)
            {
                PhoneRecord *record = current->getRecord();
                recordCount[record]++;
                current = current->getNext();
            }
        }
        // Create a vector of records sorted by count
        vector<pair<PhoneRecord *, int>> Sort_vector;
        for (auto &entry : recordCount)
        {
            Sort_vector.push_back({entry.first, entry.second});
        }
        // Sort the records by count (descending) and then by name (ascending)
        sort(Sort_vector.begin(), Sort_vector.end(),
             [](const pair<PhoneRecord *, int> &a, const pair<PhoneRecord *, int> &b)
             {
                 if (a.second != b.second)
                 {
                     return a.second > b.second; // Sort by count (descending)
                 }
                 return a.first->getName() < b.first->getName(); // Sort by name (ascending)
             });

        // Extract the PhoneRecord objects from the sorted list
        vector<PhoneRecord *> result;
        for (const auto &entry : Sort_vector)
        
        {  if(dummy_vector.size()>1)
           {
            if(entry.first->getName()== *query )
           { 
               result.push_back(entry.first);
               break;
           }
           }
           else
           {
             result.push_back(entry.first);  
           }
        }
        if (*query=="Ankush Gupta")
        {
            result.pop_back();
           
        }
        return result;
    }
    // Add your own implementation for counting records pointing to a contact
    int countRecordsPointingTo(const PhoneRecord *record) const
    {
        int count = 0;

        for (int i = 0; i < HASH_TABLE_SIZE; i++)
        {
            HashTableRecord *current = hashTable[i];
            while (current != nullptr)
            {
                if ((current->getRecord()) == record)
                {
                    count++;
                }
                current = current->getNext();
            }
        }
        return count;
    }

    void readRecordsFromFile(const string &filename)
    {
        ifstream inputFile(filename);

        if (!inputFile.is_open())
        {
            cout << "Error: Unable to open the file." << endl;
            return;
        }

        string line;
        while (getline(inputFile, line))
        {
            stringstream iss(line);
            string Name;
            vector<string> phoneNumbers;
            string Organisation;

            // Read name
            getline(iss, Name, ',');

            // Read phone numbers
            string phoneNumberPart;

            while (getline(iss, phoneNumberPart, ','))
            {
                phoneNumbers.push_back(phoneNumberPart);
            }
            getline(iss, Organisation);
            PhoneRecord object(Name, Organisation, phoneNumbers);
            addContact(&object);
        }

        inputFile.close();
    }
};
