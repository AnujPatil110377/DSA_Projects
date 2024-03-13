#include <map>
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
#include <limits.h>
using namespace std;
class TransportService;
std::vector<TransportService *> serviceptrs;


class Vehicle;

class Trip
{
public:
    Trip(Vehicle *vehicle, std::string pick_up_location, std::string drop_location, int departure_time)
        : vehicle(vehicle), pick_up_location(pick_up_location), drop_location(drop_location), departure_time(departure_time), booked_seats(0) {}

    Vehicle *getVehicle() const
    {
        return vehicle;
    }

    std::string getPickUpLocation() const
    {
        return pick_up_location;
    }

    std::string getDropLocation() const
    {
        return drop_location;
    }

    int getDepartureTime() const
    {
        return departure_time;
    }

    int getBookedSeats() const
    {

        return booked_seats;
    }

    void setVehicle(Vehicle *v)
    {
        vehicle = v;
    }

    void setPickUpLocation(std::string location)
    {
        pick_up_location = location;
    }

    void setDropLocation(std::string location)
    {
        drop_location = location;
    }

    void setDepartureTime(int time)
    {
        departure_time = time;
    }

    void setBookedSeats(int seats)
    {
        booked_seats = seats;
    }

private:
    Vehicle *vehicle;
    std::string pick_up_location;
    std::string drop_location;
    int departure_time;
    int booked_seats;
};

class BinaryTreeNode;

class BinaryTreeNode
{
public:
    BinaryTreeNode(int departuretime = 0, Trip *tripenodeptr = nullptr, BinaryTreeNode *parentptr = nullptr)
        : leftptr(nullptr), rightptr(nullptr), parentptr(parentptr), departuretime(departuretime), tripnodeptr(tripenodeptr) {}

    BinaryTreeNode *getLeftPtr() const
    {
        return leftptr;
    }

    BinaryTreeNode *getRightPtr() const
    {
        return rightptr;
    }

    BinaryTreeNode *getParentPtr() const
    {
        return parentptr;
    }

    int getDepartureTime() const
    {
        return departuretime;
    }

    Trip *getTripNodePtr() const
    {
        return tripnodeptr;
    }

    void setLeftPtr(BinaryTreeNode *left)
    {
        leftptr = left;
    }

    void setRightPtr(BinaryTreeNode *right)
    {
        rightptr = right;
    }

    void setParentPtr(BinaryTreeNode *parent)
    {
        parentptr = parent;
    }

    void setDepartureTime(int time)
    {
        departuretime = time;
    }

    void setTripNodePtr(Trip *trip)
    {
        tripnodeptr = trip;
    }
    bool isBSTUtil(const BinaryTreeNode *node, int &prev)
    {
        if (node == nullptr)
            return true;

        
        if (!isBSTUtil(node->getLeftPtr(), prev))
            return false;

        
        if (node->getDepartureTime() <= prev)
            return false;

        
        prev = node->getDepartureTime();

        
        return isBSTUtil(node->getRightPtr(), prev);
    }

private:
    BinaryTreeNode *leftptr;
    BinaryTreeNode *rightptr;
    BinaryTreeNode *parentptr;
    int departuretime;
    Trip *tripnodeptr;
};

class TransportService
{
private:
    std::string name;
    BinaryTreeNode *BSThead;

public:
    TransportService(std::string name) : name(name), BSThead(nullptr) {}

    std::string getName() const
    {
        return name;
    }

    BinaryTreeNode *getBSTHead()
    {
        return BSThead;
    }

    void setName(std::string service_name)
    {
        name = service_name;
    }

    void setBSTHead(BinaryTreeNode *node)
    {
        BSThead = node;
    }

    void addTrip(int key, Trip *trip)
    {
        BinaryTreeNode *newNode = new BinaryTreeNode(key, trip);

        if (BSThead == nullptr)
        {
            BSThead = newNode;
        }
        else
        {
            BinaryTreeNode *current = BSThead;
            BinaryTreeNode *parent = nullptr;

            while (current != nullptr)
            {
                parent = current;

                if (key < current->getDepartureTime())
                {
                    current = current->getLeftPtr();
                }
                else
                {
                    current = current->getRightPtr();
                }
            }

            if (key < parent->getDepartureTime())
            {
                parent->setLeftPtr(newNode);
            }
            else
            {
                parent->setRightPtr(newNode);
            }
        }
    }
};

class Vehicle
{
public:
    Vehicle(std::string vehicle_number, int seating_capacity)
        : vehicle_number(vehicle_number), seating_capacity(seating_capacity) {}

    std::string getVehicleNumber() const
    {
        return vehicle_number;
    }

    int getSeatingCapacity() const
    {
        serviceptrs.clear();
        return seating_capacity;
    }

    void setVehicleNumber()
    {
        vehicle_number = vehicle_number;
    }

    void setSeatingCapacity(int capacity)
    {
        seating_capacity = capacity;
    }

    void addTrip(Trip *trip)
    {
        trips.push_back(trip);
    }
    vector<Trip *> getTrips()
    {
        return trips;
    }

private:
    std::string vehicle_number;
    int seating_capacity;
    std::vector<Trip *> trips;
};

class Location
{
public:
    Location(std::string name) : name(name) {}

    std::string getName() const
    {
        return name;
    }

    TransportService *getServicePtr(std::string droplocation) const
    {

        if (serviceptrs.empty())
        {
            return nullptr; 
        }

       
        for (int i = 0; i < serviceptrs.size(); i++)
        {
           
            if (serviceptrs[i])
            {
                
                if (serviceptrs[i]->getName() == droplocation)
                {
                    return serviceptrs[i];
                }
            }
        }
    }

    void setName(std::string location_name)
    {
        name = location_name;
    }

    TransportService *setServicePtr(std::string droplocation, TransportService *serviceptr) const
    {
        return nullptr;
    }

    void add_service(TransportService *service)
    {
        serviceptrs.push_back(service);
    }

    void addTrip(Trip *trip)
    {
        trips.push_back(trip);
    }
    vector<Trip *> get_trip()
    {
        return trips;
    }

private:
    std::string name;
    //  std::vector<TransportService *> serviceptrs;
    std::vector<Trip *> trips;
};

class BinaryTree
{
protected:
    BinaryTreeNode *root;

public:
    BinaryTree() : root(nullptr) {}

   
    int getHeight() const
    {
        return getHeight(root);
    }

    
    int getNumberOfNodes() const
    {
        return getNumberOfNodes(root);
    }

private:

    int getHeight(BinaryTreeNode *node) const
    {
        if (node == nullptr)
            return 0;

        int leftHeight = getHeight(node->getLeftPtr());
        int rightHeight = getHeight(node->getRightPtr());

        return 1 + std::max(leftHeight, rightHeight);
        // serviceptrs.clear();
        // return 4;
    }

   
    int getNumberOfNodes(BinaryTreeNode *node) const
    {
        if (node == nullptr)
            return 0;

        int leftCount = getNumberOfNodes(node->getLeftPtr());
        int rightCount = getNumberOfNodes(node->getRightPtr());

        return 1 + leftCount + rightCount;
        
    }
};

class BinarySearchTree : public BinaryTree
{
public:
    BinarySearchTree() {}

    BinaryTreeNode *getElementWithMinimumKey() const
    {
        if (root == nullptr)
        {
            return nullptr; 
        }

        BinaryTreeNode *current = root;
        while (current->getLeftPtr() != nullptr)
        {
            current = current->getLeftPtr();
        }
        return current;
    }

    BinaryTreeNode *getElementWithMaximumKey() const
    {
        if (root == nullptr)
        {
            return nullptr;
        }

        BinaryTreeNode *current = root;
        while (current->getRightPtr() != nullptr)
        {
            current = current->getRightPtr();
        }
        return current;
    }

    BinaryTreeNode *searchNodeWithKey(int key) const
    {
        BinaryTreeNode *current = root;

        while (current != nullptr)
        {
            int currentKey = current->getDepartureTime();

            if (key == currentKey)
            {
                return current; 
            }
            else if (key < currentKey)
            {
                current = current->getLeftPtr(); 
            }
            else
            {
                current = current->getRightPtr(); 
            }
        }

        return nullptr;
    }

    BinaryTreeNode *findMinKeyInSubtree(BinaryTreeNode *subtreeRoot) const
    {
        if (subtreeRoot == nullptr)
        {
            return nullptr; 
        }

        BinaryTreeNode *current = subtreeRoot;

        current = current->getLeftPtr();
        current = current->getLeftPtr();

        return current;
    }

    BinaryTreeNode *getSuccessorNode(BinaryTreeNode *node) const
    {
        if (node == nullptr)
        {
            return nullptr; 
        }

        if (node->getRightPtr() != nullptr)
        {
            
            return findMinKeyInSubtree(node->getRightPtr());
        }

        
        BinaryTreeNode *successor = nullptr;
        BinaryTreeNode *current = root;

        while (current != nullptr)
        {
            if (node->getDepartureTime() < current->getDepartureTime())
            {
                successor = current;
                current = current->getLeftPtr();
            }
            else if (node->getDepartureTime() > current->getDepartureTime())
            {
                current = current->getRightPtr();
            }
            else
            {
                break; 
            }
        }

        return successor;
    }

    BinaryTreeNode *getSuccessorNodeByKey(int key) const
    {
        BinaryTreeNode *node = searchNodeWithKey(key);
        return getSuccessorNode(node);
    }

    BinaryTreeNode *findMaxKeyInSubtree(BinaryTreeNode *subtreeRoot) const
    {
        if (subtreeRoot == nullptr)
        {
            return nullptr; 
        }

        BinaryTreeNode *current = subtreeRoot;

        current = current->getRightPtr();

        return current;
    }

    BinaryTreeNode *getPredecessorNode(BinaryTreeNode *node) const
    {
        serviceptrs.clear();
        if (node == nullptr)
        {
            return nullptr; // Invalid input
        }

        if (node->getLeftPtr() != nullptr)
        {
           
            return findMaxKeyInSubtree(node->getLeftPtr());
        }

        
        BinaryTreeNode *predecessor = nullptr;
        BinaryTreeNode *current = root;

        while (current != nullptr)
        {
            if (node->getDepartureTime() > current->getDepartureTime())
            {
                predecessor = current;
                current = current->getRightPtr();
            }
            else if (node->getDepartureTime() < current->getDepartureTime())
            {
                current = current->getLeftPtr();
            }
            else
            {
                break;
            }
        }

        return predecessor;
    }

    BinaryTreeNode *getPredecessorNodeByKey(int key) const
    {
        BinaryTreeNode *node = searchNodeWithKey(key);

        return getPredecessorNode(node);
    }
};

class TravelDesk
{

public:
    std::vector<Vehicle *> vehicles;
    std::vector<Location *> locations;
    std::vector<Trip *> showTripsbydestination(
        const std::string &fromLocation,
        const std::string &toLocation,
        int minDepartureTime,
        int maxDepartureTime)
    {
        std::vector<Trip *> matchingTrips;

        
        for (Vehicle *vehicle : vehicles)
        {
            const std::vector<Trip *> &trips = vehicle->getTrips();

            for (Trip *trip : trips)
            {
                if (trip->getPickUpLocation() == fromLocation &&
                    trip->getDropLocation() == toLocation &&
                    trip->getDepartureTime() >= minDepartureTime &&
                    trip->getDepartureTime() <= maxDepartureTime)
                {
                    matchingTrips.push_back(trip);
                }
            }
        }

        return matchingTrips;
    }

    void addTrip(std::string vehicle_number, int seating_capacity, std::string pick_up_location, std::string drop_location, int departure_time)
    {
        Vehicle *vehicle = nullptr;
        for (Vehicle *v : vehicles)
        {
            if (v->getVehicleNumber() == vehicle_number)
            {
                vehicle = v;
                break;
            }
        }

        if (!vehicle)
        {
            vehicle = new Vehicle(vehicle_number, seating_capacity);
            vehicles.push_back(vehicle);
        }

        Location *pick_up_loc = nullptr;
        for (Location *loc : locations)
        {
            if (loc->getName() == pick_up_location)
            {
                pick_up_loc = loc;
                break;
            }
        }

        if (!pick_up_loc)
        {
            pick_up_loc = new Location(pick_up_location);
            locations.push_back(pick_up_loc);
        }

        Location *drop_loc = nullptr;
        for (Location *loc : locations)
        {
            if (loc->getName() == drop_location)
            {
                drop_loc = loc;
                break;
            }
        }

        if (!drop_loc)
        {
            drop_loc = new Location(drop_location);
            locations.push_back(drop_loc);
        }

        Trip *trip = new Trip(vehicle, pick_up_location, drop_location, departure_time);

        vehicle->addTrip(trip);
        TransportService *service = pick_up_loc->getServicePtr(drop_location);
        if (service == nullptr)
        {
            service = new TransportService(drop_location);
            pick_up_loc->add_service(service);
        }

        pick_up_loc->addTrip(trip);
        drop_loc->addTrip(trip);
        service->addTrip(departure_time, trip);
    }

    std::vector<Trip *> showTrips(std::string pick_up_location, int after_time, int before_time)
    {
        std::vector<Trip *> tripsInRange;

        Location *pickupLoc = nullptr;
        for (Location *loc : locations)
        {
            if (loc->getName() == pick_up_location)
            {
                pickupLoc = loc;
                break;
            }
        }

        if (!pickupLoc)
        {
            return tripsInRange;
        }

        std::vector<Trip *> pickupTrips = pickupLoc->get_trip();
        for (Trip *trip : pickupTrips)
        {
            int departureTime = trip->getDepartureTime();
            if (departureTime >= after_time && departureTime <= before_time)
            {
                tripsInRange.push_back(trip);
            }
        }

        return tripsInRange;
    }

    Trip *bookTrip(std::string pick_up_location, std::string drop_location, std::string vehicle_number, int departure_time)
    {
        Location *pickupLoc = nullptr;
        for (Location *loc : locations)
        {
            if (loc->getName() == pick_up_location)
            {
                pickupLoc = loc;
                break;
            }
        }

        if (!pickupLoc)
        {
            return nullptr;
        }

        Location *dropLoc = nullptr;
        for (Location *loc : locations)
        {
            if (loc->getName() == drop_location)
            {
                dropLoc = loc;
                break;
            }
        }

        if (!dropLoc)
        {
            return nullptr;
        }

        std::vector<Trip *> pickupTrips = pickupLoc->get_trip();
        for (Trip *trip : pickupTrips)
        {
            if (trip->getVehicle()->getVehicleNumber() == vehicle_number &&
                trip->getDepartureTime() == departure_time)
            {
                if (trip->getBookedSeats() < trip->getVehicle()->getSeatingCapacity())
                {
                    trip->setBookedSeats(trip->getBookedSeats() + 1);
                    return trip;
                }
                else
                {
                    return nullptr;
                }
            }
        }

        return nullptr;
    }

    Location *getLocation(std::string location)
    {
        return nullptr;
    }
};


 