#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;
class StudentRecord
{
private:
    string studentName;
    
    string rollNumber;

public:
    string get_studentName()
    {
        return studentName;
    }
    void set_studentName(string Name)
    {
        studentName = Name;
    }
    string get_rollNumber()
    {
        return rollNumber;
    }
    void set_rollNumber(string rollnum)
    {
        rollNumber = rollnum;
    }
};

class Node
{
private:
    Node *next;
    StudentRecord *element;

public:
    Node *get_next()
    {
        return next;
    }
    StudentRecord *get_element()
    {
        return element;
    }

    void set_next(Node *value)
    {
        next = value;
    }
    void set_element(StudentRecord *student)
    {
        element = student;
    }
};

class Entity
{
private:
    string name;
    Node *iterator;

public:
    string get_name()
    {
        return name;
    }
    void set_name(string Name)
    {
        name = Name;
    }
    Node *get_iterator()
    {
        return iterator;
    }
    void set_iterator(Node *iter)
    {
        iterator = iter;
    }
};
vector<StudentRecord> students;

class LinkedList : public Entity
{

public:
    void add_student(StudentRecord student)
    {
        Node *head = get_iterator();
        bool check = false;

        while (head != NULL)
        {
            if (head->get_element()->get_rollNumber() == student.get_rollNumber())
            {
                check = true;
                break;
            }
            head = head->get_next();
        }

        if (!check)
        {
            Node *New_Node = new Node;
             StudentRecord *COpy = new StudentRecord;
            *COpy = student;

            New_Node->set_element(COpy);
             New_Node->set_next(NULL);

            if (get_iterator() != NULL)
            {
                 New_Node->set_next(get_iterator());
                 set_iterator(New_Node);
            }
            else
            {
            set_iterator(New_Node);
            }
        }
    }

void delete_student(string studentName)
    {
        int n = 1;
        Node *Current_Node = get_iterator();
        bool found = false;

        while (Current_Node != NULL)
        {
            if (Current_Node->get_element()->get_studentName() == studentName)
            {
                found = true;
                break;
            }
            Current_Node = Current_Node->get_next();
            n++;
        }

        if (found)
        {
            if (n == 1)
            {
                set_iterator(Current_Node->get_next());
                return;
            }
            Current_Node = Current_Node->get_next();
            Node *previousNode = get_iterator();
            for (int i = 0; i < n - 2; i++)
            {
                previousNode = previousNode->get_next();
            }
            previousNode->set_next(Current_Node);
        }
    }

};
vector<LinkedList> EntityArray;
void read_input_file(string file_path)
{
    string line;
    ifstream inputFile(file_path);

    if (!inputFile.is_open())
    {
        cerr << "Error opening file." << std::endl;
        return;
    }

    while (getline(inputFile, line))
    {
        
        istringstream W_o_rd(line);
        string studentName, rollNumber, entityData;

        if (getline(W_o_rd, studentName, ','))
        {
            studentName.erase(0, studentName.find_first_not_of(" \t\r\n"));
            studentName.erase(studentName.find_last_not_of(" \t\r\n") + 1);
        }

        if (getline(W_o_rd, rollNumber, ','))
        {
            rollNumber.erase(0, rollNumber.find_first_not_of(" \t\r\n"));
            rollNumber.erase(rollNumber.find_last_not_of(" \t\r\n") + 1);
        }
        StudentRecord student;
        student.set_studentName(studentName);
        student.set_rollNumber(rollNumber);
        students.push_back(student);

        if (getline(W_o_rd, entityData))
        {
            entityData.erase(0, entityData.find_first_not_of(" \t\r\n"));
            entityData.erase(entityData.find_last_not_of(" \t\r\n") + 1);

            
            std::string delimiter = ",[]";
            size_t pos = 0;
            while ((pos = entityData.find_first_of(delimiter)) != std::string::npos)
            {
                std::string entity = entityData.substr(0, pos);
                // Trim whitespace from the entity
                entity.erase(0, entity.find_first_not_of(" \t\r\n"));
                entity.erase(entity.find_last_not_of(" \t\r\n") + 1);

                
                if (!entity.empty())
                {
                    int i;
                    bool found = false;
                    for (i = 0; i < EntityArray.size(); i++)
                    {
                        if (EntityArray[i].get_name() == entity)
                        {
                            found = true;
                            break;
                        }
                    }

                    if (!found)
                    {
                        LinkedList Entity1;
                        Entity1.set_name(entity);
                        Entity1.set_iterator(NULL);
                        EntityArray.push_back(Entity1);
                        EntityArray[EntityArray.size() - 1].add_student(student);

                      
                    }
                    else
                    {
                        EntityArray[i].add_student(student);
                    }
                }

                entityData.erase(0, pos + 1);
            }
        }
    }

    inputFile.close();
}


int Search(string key)
{
    int count = 0;

    int size = EntityArray.size();
    for (int i = 0; i < size; i++)
    {

        if (key == EntityArray[i].get_name())
        {
            count++;
        }
    }
    if (count == size)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}