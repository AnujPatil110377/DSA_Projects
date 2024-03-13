#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
using namespace std;
int Ant = 0;
// Forward declarations
class MetroStop;
class MetroLine;
class AVLNode;
void inptu(int i)
{
    Ant = i;
}

// MetroStop class
class MetroStop
{
private:
    std::string stopName;
    MetroStop *nextStop;
    MetroStop *prevStop;
    MetroLine *line;
    int fare;

public:
    MetroStop(std::string name, MetroLine *metroLine, int fare);

    // Getter methods
    std::string getStopName() const;
    MetroStop *getNextStop() const;
    MetroStop *getPrevStop() const;
    MetroLine *getLine() const;
    int getFare() const;

    // Setter methods
    void setNextStop(MetroStop *next);
    void setPrevStop(MetroStop *prev);
};

MetroStop::MetroStop(std::string name, MetroLine *metroLine, int fare)
{
    stopName = name;
    nextStop = nullptr;
    prevStop = nullptr;
    line = metroLine;
    this->fare = fare;
}

std::string MetroStop::getStopName() const
{
    return stopName;
}

MetroStop *MetroStop::getNextStop() const
{
    return nextStop;
}

MetroStop *MetroStop::getPrevStop() const
{
    return prevStop;
}

MetroLine *MetroStop::getLine() const
{
    return line;
}

int MetroStop::getFare() const
{
    return fare;
}

void MetroStop::setNextStop(MetroStop *next)
{
    nextStop = next;
}

void MetroStop::setPrevStop(MetroStop *prev)
{
    prevStop = prev;
}

// MetroLine class
class MetroLine
{
private:
    std::string lineName;
    MetroStop *node;

public:
    MetroLine(std::string name);

    // Getter methods
    std::string getLineName() const;
    MetroStop *getNode() const;

    // Setter methods
    void setNode(MetroStop *node);

    void populateLine(std::string filename);

    // helper function
    void printLine() const;
    int getTotalStops() const;
};

MetroLine::MetroLine(std::string name)
{
    lineName = name;
    node = nullptr;
}

std::string MetroLine::getLineName() const
{
    return lineName;
}

MetroStop *MetroLine::getNode() const
{
    return node;
}

void MetroLine::setNode(MetroStop *node)
{
    this->node = node;
}

void MetroLine::printLine() const
{
    MetroStop *stop = node;
    while (stop != nullptr)
    {
        cout << stop->getStopName() << endl;
        stop = stop->getNextStop();
    }
}

int MetroLine::getTotalStops() const
{
    int count = 0;
    MetroStop *eachStop = node;
    while (eachStop != nullptr)
    {
        count++;
        eachStop = eachStop->getNextStop();
    }
    return count;
}

void MetroLine::populateLine(std::string filename)
{
    // string lineName = filename.substr(0, filename.length() - 4);
    // MetroLine *metroLine = new MetroLine(lineName);
    inptu(0);
    fstream fin;
    fin.open(filename, ios::in);
    string line;
    while (getline(fin, line))
    {
        string fare;
        // cout <<" linestart->" << line <<" ---------";
        while (line[line.size() - 1] == ',')
        {
            // cout << line[line.size()-1] << " ";
            line.pop_back();
        }
        // cout << line[line.size()-1] << " ";
        int j = line.size() - 1;
        while (line.back() != ' ')
        {
            fare.push_back(line.back());
            line.pop_back();
        }

        for (int i = 0; i < 1000; ++i)
        {
            for (int j = 0; j < 1000; ++j)
            {
                Ant++;
            }
        }
        line.pop_back();
        reverse(fare.begin(), fare.end());

        // cout << line <<"   ->>>>>> ";
        int finalFare = stoi(fare);
        // cout << fare <<" " ;
        // cout << line <<" " << this->getLineName() <<" " << typeid(finalFare).name() <<" " << finalFare << endl;
        // cout << line <<"    fare is " << finalFare << " type" << typeid(finalFare).name() << endl;
        MetroStop *temp_Stop = new MetroStop(line, this, finalFare);
        // if (node == NULL)
        // {
        //     setNode(stop);
        // }
        // else
        // {
        //     // MetroStop *curr = getNode();
        //     // while (curr->getNextStop() != nullptr)
        //     // {
        //     //     curr = curr->getNextStop();
        //     // }
        //     // curr->setNextStop(stop);
        //     // stop->setPrevStop(curr);
        //     stop->setNextStop(node);
        //     node->setPrevStop(stop);
        //     setNode(stop);
        // }
        for (int i = 0; i < 1000; ++i)
        {
            for (int j = 0; j < 1000; ++j)
            {
                Ant++;
            }
        }
        inptu(0);
        if (getNode() == nullptr)
        {
            setNode(temp_Stop);
        }
        else
        {
            temp_Stop->setNextStop(getNode());
            getNode()->setPrevStop(temp_Stop);
            setNode(temp_Stop);
        }
    }
    fin.close();
    // lines.push_back(metroLine);
}

// AVLNode class
class AVLNode
{
private:
    std::string stopName;
    std::vector<MetroStop *> stops;
    AVLNode *left;
    AVLNode *right;
    AVLNode *parent;

public:
    AVLNode(std::string name);

    // Getter methods
    std::string getStopName() const;
    const std::vector<MetroStop *> &getStops() const;
    AVLNode *getLeft() const;
    AVLNode *getRight() const;
    AVLNode *getParent() const;

    // Setter methods
    void addMetroStop(MetroStop *metroStop);
    void setLeft(AVLNode *left);
    void setRight(AVLNode *right);
    void setParent(AVLNode *parent);
};

AVLNode::AVLNode(std::string name)
{
    stopName = name;
    left = nullptr;
    right = nullptr;
    parent = NULL;
}

std::string AVLNode::getStopName() const
{
    return stopName;
}

const std::vector<MetroStop *> &AVLNode::getStops() const
{
    return stops;
}

AVLNode *AVLNode::getLeft() const
{
    return left;
}

AVLNode *AVLNode::getRight() const
{
    return right;
}

AVLNode *AVLNode::getParent() const
{
    return parent;
}

void AVLNode::setLeft(AVLNode *left)
{
    this->left = left;
}

void AVLNode::setRight(AVLNode *right)
{
    this->right = right;
}

void AVLNode::setParent(AVLNode *parent)
{
    this->parent = parent;
}

void AVLNode::addMetroStop(MetroStop *metroStop)
{
    stops.push_back(metroStop);
}

// AVLTree class
class AVLTree
{
    // Define your AVLTree implementation here.
private:
    AVLNode *root;
    // AVLNode *travelptr;   added here by myself

public:
    // getter methods
    AVLNode *getRoot() const;

    // setter methods
    void setRoot(AVLNode *root);

    // helper functions
    int height(AVLNode *node);
    int balanceFactor(AVLNode *node);
    void rotateLeft(AVLNode *node);
    void rotateRight(AVLNode *node);
    void balance(AVLNode *node);
    int stringCompare(string s1, string s2);
    void insert(AVLNode *node, MetroStop *metroStop);
    void populateTree(MetroLine *metroLine);
    void inOrderTraversal(AVLNode *node);
    int getTotalNodes(AVLNode *node);
    AVLNode *searchStop(string stopName);
    AVLNode *insert_Help(AVLNode *node, MetroStop *metroStop);
};

AVLNode *AVLTree::getRoot() const
{
    return root;
}

void AVLTree::setRoot(AVLNode *root)
{
    this->root = root;
}

int AVLTree::height(AVLNode *node)
{
    if (node == NULL)
    {
        return 0;
    }
    int left = height(node->getRight());
    int right = height(node->getLeft());
    return 1 + max(left, right);
}

int AVLTree::stringCompare(string s1, string s2)
{
    // use strcmp

    char *Char1 = new char[s1.length() + 1];
    strcpy(Char1, s1.c_str());

    char *Char2 = new char[s2.length() + 1];
    strcpy(Char2, s2.c_str());
    inptu(0);

    int result = strcmp(Char1, Char2);
    return result;
}

int AVLTree::balanceFactor(AVLNode *node)
{
    if (node == NULL)
    {
        return 0;
    }
    inptu(0);
    int l = height(node->getLeft());
    int r = height(node->getRight());
    return l - r;
}

void AVLTree::rotateLeft(AVLNode *node)
{
    AVLNode *Root_Temp = node->getLeft();
    node->setLeft(Root_Temp->getRight());

    if (Root_Temp->getRight() != nullptr)
        Root_Temp->getRight()->setParent(node);

    Root_Temp->setRight(node);
    for (int i = 0; i < 1000; ++i)
    {
        for (int j = 0; j < 1000; ++j)
        {
            Ant++;
        }
    }
    inptu(0);
    if (node->getParent() != nullptr)
    {
        if (node->getParent()->getLeft() == node)
            node->getParent()->setLeft(Root_Temp);
        else
            node->getParent()->setRight(Root_Temp);
    }

    inptu(0);
    Root_Temp->setParent(node->getParent());
    node->setParent(Root_Temp);
}

void AVLTree::rotateRight(AVLNode *node)
{
    AVLNode *Root_Temp = node->getRight();
    node->setRight(Root_Temp->getLeft());

    if (Root_Temp->getLeft() != nullptr)
        Root_Temp->getLeft()->setParent(node);

    Root_Temp->setLeft(node);
    for (int i = 0; i < 1000; ++i)
    {
        for (int j = 0; j < 1000; ++j)
        {
            Ant++;
        }
    }
    inptu(0);
    if (node->getParent() != nullptr)
    {
        if (node->getParent()->getLeft() == node)
            node->getParent()->setLeft(Root_Temp);
        else
            node->getParent()->setRight(Root_Temp);
    }

    Root_Temp->setParent(node->getParent());
    node->setParent(Root_Temp);
    inptu(0);
}

void AVLTree::balance(AVLNode *node)
{
    if (node == nullptr)
        return;

    int Balance_factor = balanceFactor(node);
    inptu(0);
    if (Balance_factor > 1)
    {
        if (balanceFactor(node->getLeft()) == 1)
        {
            rotateLeft(node);
        }
        else if (balanceFactor(node->getLeft()) == -1)
        {
            rotateRight(node->getLeft());
            rotateLeft(node);
        }
    }
    else if (Balance_factor < -1)
    {
        if (balanceFactor(node->getRight()) == -1)
        {
            rotateRight(node);
        }
        else if (balanceFactor(node->getRight()) == 1)
        {
            rotateLeft(node->getRight());
            rotateRight(node);
        }
    }
    inptu(0);
    Ant = 0;
}

void AVLTree::insert(AVLNode *node, MetroStop *metroStop)
{
    AVLNode *Temp_node = new AVLNode(metroStop->getStopName());
    Temp_node->addMetroStop(metroStop);

    if (root == nullptr)
    {
        root = Temp_node;
        return;
    }
    inptu(0);
    AVLNode *temp = root;
    AVLNode *parent = nullptr;
    for (int i = 0; i < 1000; ++i)
    {
        for (int j = 0; j < 1000; ++j)
        {
            Ant++;
        }
    }
    inptu(0);
    while (temp != nullptr)
    {
        parent = temp;

        if (stringCompare((metroStop->getStopName()), (temp->getStopName())) < 0)
        {
            if (temp->getLeft() == NULL)
            {
                temp->setLeft(Temp_node);
                Temp_node->setParent(temp);
                break;
            }
            else
            {
                temp = temp->getLeft();
            }
        }
        else if (stringCompare((metroStop->getStopName()), (temp->getStopName())) > 0)
        {
            if (temp->getRight() == NULL)
            {
                temp->setRight(Temp_node);
                Temp_node->setParent(temp);
                break;
            }
            else
            {
                temp = temp->getRight();
            }
        }
        else
        {
            temp->addMetroStop(metroStop);
            break;
        }
    }
    while (parent != nullptr)
    {
        balance(parent);
        parent = parent->getParent();
    }
    inptu(0);
}

void AVLTree::populateTree(MetroLine *metroLine)
{
    MetroStop *stopData = metroLine->getNode();
    inptu(0);
    while (stopData != nullptr)
    {
        AVLNode *node = new AVLNode(stopData->getStopName());
        insert(node, stopData);
        stopData = stopData->getNextStop();
    }
}

void AVLTree::inOrderTraversal(AVLNode *node)
{
    if (node == nullptr)
    {
        return;
    }
    inOrderTraversal(node->getLeft());
    cout << node->getStopName() << endl;
    inOrderTraversal(node->getRight());
}

int AVLTree::getTotalNodes(AVLNode *node)
{
    if (root == nullptr)
    {
        return 0;
    }

    int totalNodes = 0;
    std::stack<AVLNode *> nodeStack;
    nodeStack.push(root);
    inptu(0);

    while (!nodeStack.empty())
    {
        AVLNode *currentNode = nodeStack.top();
        nodeStack.pop();
        totalNodes++;

        if (currentNode->getRight() != nullptr)
        {
            nodeStack.push(currentNode->getRight());
        }
        inptu(0);
        if (currentNode->getLeft() != nullptr)
        {
            nodeStack.push(currentNode->getLeft());
        }
    }
    for (int i = 0; i < 1000; ++i)
    {
        for (int j = 0; j < 1000; ++j)
        {
            Ant++;
        }
    }
    inptu(0);
    return totalNodes;
}

AVLNode *AVLTree::searchStop(string stopName)
{
    AVLNode *current = root;

    while (current != nullptr)
    {
        int comparisonResult = stopName.compare(current->getStopName());

        if (comparisonResult == 0)
        {
            return current;
        }
        else if (comparisonResult < 0)
        {
            current = current->getLeft();
        }
        else
        {
            current = current->getRight();
        }
    }
    inptu(0);
    return nullptr;
}

// Trip class
class Trip
{
private:
    MetroStop *node;
    Trip *prev;

public:
    Trip(MetroStop *metroStop, Trip *previousTrip);

    // Getter methods
    MetroStop *getNode() const;
    Trip *getPrev() const;
};

Trip::Trip(MetroStop *metroStop, Trip *previousTrip)
{
    node = metroStop;
    prev = previousTrip;
}

MetroStop *Trip::getNode() const
{
    return node;
}

Trip *Trip::getPrev() const
{
    return prev;
}

// Exploration class is a queue that stores unexplored Trip objects
class Exploration
{
private:
    std::queue<Trip *> trips;

public:
    Exploration();

    // Getter methods
    std::queue<Trip *> getTrips() const;

    // Setter methods
    void enqueue(Trip *trip);
    Trip *dequeue();
    bool isEmpty() const;
};

Exploration::Exploration()
{
}

std::queue<Trip *> Exploration::getTrips() const
{
    return trips;
}

void Exploration::enqueue(Trip *trip)
{
    trips.push(trip);
}

Trip *Exploration::dequeue()
{
    if (trips.empty())
    {
        return nullptr;
    }
    Trip *trip = trips.front();
    trips.pop();
    cout << "Dequeued: " << trip->getNode()->getStopName() << endl;
    return trip;
}

bool Exploration::isEmpty() const
{
    return trips.empty();
}

class Path
{
private:
    std::vector<MetroStop *> stops;
    int totalFare;

public:
    Path();

    // Getter methods
    std::vector<MetroStop *> getStops() const;
    int getTotalFare() const;

    // Setter methods
    void addStop(MetroStop *stop);
    void setTotalFare(int fare);

    // helper functions
    void printPath() const;
};

Path::Path()
{
    totalFare = 0;
}

std::vector<MetroStop *> Path::getStops() const
{
    return stops;
}

int Path::getTotalFare() const
{
    return totalFare;
}

void Path::addStop(MetroStop *stop)
{
    stops.push_back(stop);
}

void Path::setTotalFare(int fare)
{
    totalFare = fare;
}

void Path::printPath() const
{
    for (auto stop : stops)
    {
        cout << stop->getStopName() << endl;
    }
}

// PathFinder class
class PathFinder
{
private:
    AVLTree *tree;
    std::vector<MetroLine *> lines;

public:
    PathFinder(AVLTree *avlTree, const std::vector<MetroLine *> &metroLines);
    void createAVLTree();
    Path *findPath(std::string origin, std::string destination);

    // Getter methods
    AVLTree *getTree() const;
    const std::vector<MetroLine *> &getLines() const;

    void setTree(AVLTree *createdTree);
    vector<MetroStop *> getJunctionVector(MetroStop *firstEncounter)
    {
        AVLNode *rqNode = tree->searchStop(firstEncounter->getStopName());

        vector<MetroStop *> temporary = rqNode->getStops();
        vector<MetroStop *> temporaryUseful;
        for (int k = 0; k < temporary.size(); k++)
        {
            if (temporary[k]->getLine()->getLineName() != firstEncounter->getLine()->getLineName())
            {
                temporaryUseful.push_back(temporary[k]);
            }
        }
        return temporaryUseful;
    }
    vector<MetroStop *> JunctionWithTrips;
};

PathFinder::PathFinder(AVLTree *avlTree, const std::vector<MetroLine *> &metroLines)
{
    tree = avlTree;
    lines = metroLines;
}

AVLTree *PathFinder::getTree() const
{
    return tree;
}
void PathFinder::setTree(AVLTree *createdTree)
{
    this->tree = createdTree;
}
const std::vector<MetroLine *> &PathFinder::getLines() const
{
    return lines;
}

void PathFinder::createAVLTree()
{
    AVLTree *newTree = new AVLTree();
    newTree->setRoot(nullptr);
    for (auto line : lines)
    {
        if (newTree->getRoot() == nullptr)
        {
            newTree->setRoot(new AVLNode(line->getNode()->getStopName()));
        }
        newTree->populateTree(line);
    }
    setTree(newTree);
}

Path *PathFinder::findPath(std::string origin, std::string destination)
{
    vector<Trip *> allSuccessfuls;
    Trip *Trip_sucess = NULL;
    int i;
    AVLTree *searchTree = getTree();
    AVLNode *original_Node = searchTree->searchStop(origin);
    AVLNode *destin_Node = searchTree->searchStop(destination);
    vector<MetroStop *> originStops = original_Node->getStops();

    Exploration *explorationQueue = new Exploration();

    AVLNode *requiredNode = tree->searchStop(originStops[0]->getStopName());
    int tempSize = (requiredNode->getStops()).size();
    if (tempSize > 1)
    {
        JunctionWithTrips.push_back(originStops[0]);
        for (int j = 0; j < originStops.size(); j++)
        {
            Trip *trip = new Trip(originStops[j], NULL);
            explorationQueue->enqueue(trip);
        }
    }
    else
    {
        Trip *trip = new Trip(originStops[0], NULL);
        explorationQueue->enqueue(trip);
    }
    for (int i = 0; i < 1000; ++i)
    {
        for (int j = 0; j < 1000; ++j)
        {
            Ant++;
        }
    }
    while (explorationQueue->isEmpty() == false)
    {
        Trip *currentTrip = explorationQueue->dequeue();
        MetroLine *currentLine = currentTrip->getNode()->getLine();
        MetroStop *currentStop = currentLine->getNode();
        while (currentStop != currentTrip->getNode())
        {
            currentStop = currentStop->getNextStop();
        }
        MetroStop *backTravelStop = currentStop;
        bool flag = false;
        while (currentStop != NULL)
        {
            if (currentStop->getStopName() == destin_Node->getStopName())
            {
                flag = true;
                break;
            }
            // Checking for junction
            AVLNode *requiredNode = tree->searchStop(currentStop->getStopName());
            int tempSize2 = (requiredNode->getStops()).size();

            // Checking if trips are already created for this junction or not
            int flag2 = false;
            int j = 0;
            while (j < JunctionWithTrips.size())
            {
                if (currentStop->getStopName() == JunctionWithTrips[j]->getStopName())
                {
                    flag2 = true;
                }
                j++;
            }
            if (tempSize2 > 1 && (flag2 == false))
            {
                JunctionWithTrips.push_back(currentStop);
                vector<MetroStop *> temporary = getJunctionVector(currentStop);
                for (int j = 0; j < tempSize2 - 1; j++)
                {
                    MetroStop *changie_Line = temporary[j];
                    Trip *newTrip = new Trip(changie_Line, currentTrip);
                    explorationQueue->enqueue(newTrip);
                }
            }
            currentStop = currentStop->getNextStop();
        }
        cout << endl;
        if (flag == true)
        {
            Trip_sucess = currentTrip;
            // allSuccessfuls.push_back(currentTrip);
            break;
        }
        while (backTravelStop != NULL)
        {
            if (backTravelStop->getStopName() == destin_Node->getStopName())
            {
                flag = true;
                break;
            }
            // Junction or not
            AVLNode *requiredNode = tree->searchStop(backTravelStop->getStopName());
            int tempSize3 = (requiredNode->getStops()).size();

            // Present in vector of junction or not
            int flag3 = false;
            int j = 0;
            while (j < JunctionWithTrips.size())
            {
                if (backTravelStop->getStopName() == JunctionWithTrips[j]->getStopName())
                {
                    flag3 = true;
                }
                j++;
            }
            if (tempSize3 > 1 && (flag3 == false))
            {
                JunctionWithTrips.push_back(backTravelStop);
                vector<MetroStop *> temporary = getJunctionVector(backTravelStop);
                for (int j = 0; j < tempSize3 - 1; j++)
                {
                    MetroStop *changie_Line = temporary[j];
                    Trip *newTrip = new Trip(changie_Line, currentTrip);
                    explorationQueue->enqueue(newTrip);
                }
            }
            backTravelStop = backTravelStop->getPrevStop();
        }
        if (flag == true)
        {
            Trip_sucess = currentTrip;
            break;
        }
    }
    Path *End_Flow = new Path();

    string My_destinationj = destination;

    vector<MetroStop *> finalStops;
    int fare = 0;
    int count = 0;
    while (Trip_sucess != NULL)
    {
        vector<MetroStop *> Tempraray_stops;
        bool flag1 = false;
        MetroStop *End_trip_stop = Trip_sucess->getNode();
        while (End_trip_stop != NULL)
        {
            Tempraray_stops.push_back(End_trip_stop);
            if (End_trip_stop->getStopName() == My_destinationj)
            {
                flag1 = true;
                break;
            }
            End_trip_stop = End_trip_stop->getNextStop();
        }
        if (!flag1)
        {
            Tempraray_stops.clear();
            End_trip_stop = Trip_sucess->getNode();
            while (End_trip_stop->getStopName() != My_destinationj)
            {
                Tempraray_stops.push_back(End_trip_stop);
                End_trip_stop = End_trip_stop->getPrevStop();
            }
            Tempraray_stops.push_back(End_trip_stop);
        }
        fare += abs(Tempraray_stops.front()->getFare() - Tempraray_stops.back()->getFare());
        if (count > 0)
        {
            Tempraray_stops.pop_back();
        }
        for (int k = Tempraray_stops.size() - 1; k >= 0; k--)
        {
            finalStops.push_back(Tempraray_stops[k]);
        }
        My_destinationj = Trip_sucess->getNode()->getStopName();
        Trip_sucess = Trip_sucess->getPrev();
        count++;
    }
    for (auto it : finalStops)
    {
        End_Flow->addStop(it);
    }
    End_Flow->setTotalFare(fare);
    return End_Flow;
}

vector<MetroLine *> lines;





































struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};


class BinaryTree {
private:
    Node* root;

 
    void destroyTree(Node* node);
    Node* insert(Node* node, int value);
    Node* remove(Node* node, int value);
    Node* findMin(Node* node);
    void inOrderTraversal(Node* node);
    void preOrderTraversal(Node* node);
    void postOrderTraversal(Node* node);

public:
   
    BinaryTree();
    ~BinaryTree();

    // Public functions
    void insert(int value);
    void remove(int value);
    void inOrderTraversal();
    void preOrderTraversal();
    void postOrderTraversal();
};


BinaryTree::BinaryTree() : root(nullptr) {}


BinaryTree::~BinaryTree() {
    destroyTree(root);
}


void BinaryTree::destroyTree(Node* node) {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}


void BinaryTree::insert(int value) {
    root = insert(root, value);
}


Node* BinaryTree::insert(Node* node, int value) {
    if (node == nullptr) {
        return new Node(value);
    }

    if (value < node->data) {
        node->left = insert(node->left, value);
    } else if (value > node->data) {
        node->right = insert(node->right, value);
    }

    return node;
}


void BinaryTree::remove(int value) {
    root = remove(root, value);
}


Node* BinaryTree::remove(Node* node, int value) {
    if (node == nullptr) {
        return nullptr;
    }

    if (value < node->data) {
        node->left = remove(node->left, value);
    } else if (value > node->data) {
        node->right = remove(node->right, value);
    } else {
        
        if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            return temp;
        }

       
        Node* temp = findMin(node->right);
        node->data = temp->data;
        node->right = remove(node->right, temp->data);
    }

    return node;
}


Node* BinaryTree::findMin(Node* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}


void BinaryTree::inOrderTraversal() {
    inOrderTraversal(root);
    std::cout << std::endl;
}


void BinaryTree::inOrderTraversal(Node* node) {
    if (node != nullptr) {
        inOrderTraversal(node->left);
        std::cout << node->data << " ";
        inOrderTraversal(node->right);
    }
}


void BinaryTree::preOrderTraversal() {
    preOrderTraversal(root);
    std::cout << std::endl;
}


void BinaryTree::preOrderTraversal(Node* node) {
    if (node != nullptr) {
        std::cout << node->data << " ";
        preOrderTraversal(node->left);
        preOrderTraversal(node->right);
    }
}


void BinaryTree::postOrderTraversal() {
    postOrderTraversal(root);
    std::cout << std::endl;
}


void BinaryTree::postOrderTraversal(Node* node) {
    if (node != nullptr) {
        postOrderTraversal(node->left);
        postOrderTraversal(node->right);
        std::cout << node->data << " ";
    }
}