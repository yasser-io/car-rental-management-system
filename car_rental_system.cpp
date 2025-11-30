#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <memory>
#include <ctime>
#include <map>
#include <sstream>

class Vehicle {
private:
    std::string vehicleId;
    std::string make;
    std::string model;
    int year;
    std::string type;
    std::string fuelType;
    std::string transmission;
    int seatingCapacity;
    int mileage;
    double dailyRate;
    bool isAvailable;
    std::string licensePlate;
    std::string color;
    std::vector<std::string> features;

public:
    Vehicle(std::string id, std::string mk, std::string mdl, int yr, std::string typ,
            std::string fuel, std::string trans, int seats, int mil, double rate,
            std::string plate, std::string col)
        : vehicleId(id), make(mk), model(mdl), year(yr), type(typ), fuelType(fuel),
          transmission(trans), seatingCapacity(seats), mileage(mil), dailyRate(rate),
          isAvailable(true), licensePlate(plate), color(col) {}

    void addFeature(const std::string& feature) {
        features.push_back(feature);
    }

    bool rentVehicle() {
        if (isAvailable) {
            isAvailable = false;
            return true;
        }
        return false;
    }

    void returnVehicle(int newMileage) {
        isAvailable = true;
        mileage = newMileage;
    }

    void updateDailyRate(double newRate) {
        dailyRate = newRate;
    }

    void displayInfo() const {
        std::cout << "\n=== " << year << " " << make << " " << model << " ===" << std::endl;
        std::cout << "ID: " << vehicleId << " | License: " << licensePlate << std::endl;
        std::cout << "Type: " << type << " | Color: " << color << std::endl;
        std::cout << "Fuel: " << fuelType << " | Transmission: " << transmission << std::endl;
        std::cout << "Seats: " << seatingCapacity << " | Mileage: " << mileage << " km" << std::endl;
        std::cout << "Daily Rate: $" << std::fixed << std::setprecision(2) << dailyRate << std::endl;
        std::cout << "Status: " << (isAvailable ? "Available" : "Rented") << std::endl;
        
        if (!features.empty()) {
            std::cout << "Features: ";
            for (const auto& feature : features) {
                std::cout << feature << ", ";
            }
            std::cout << std::endl;
        }
    }

    std::string getVehicleId() const { return vehicleId; }
    std::string getMake() const { return make; }
    std::string getModel() const { return model; }
    std::string getType() const { return type; }
    double getDailyRate() const { return dailyRate; }
    bool getAvailability() const { return isAvailable; }
    std::string getLicensePlate() const { return licensePlate; }
    int getMileage() const { return mileage; }
};

class Customer {
private:
    std::string customerId;
    std::string firstName;
    std::string lastName;
    std::string email;
    std::string phone;
    std::string address;
    std::string licenseNumber;
    std::string licenseExpiry;
    int age;
    int totalRentals;
    double totalSpent;
    std::string membershipLevel;

public:
    Customer(std::string id, std::string fname, std::string lname, std::string email,
             std::string phone, std::string addr, std::string license, std::string expiry, int age)
        : customerId(id), firstName(fname), lastName(lname), email(email), phone(phone),
          address(addr), licenseNumber(license), licenseExpiry(expiry), age(age),
          totalRentals(0), totalSpent(0.0), membershipLevel("Standard") {}

    void updateMembership() {
        if (totalSpent >= 5000.0) {
            membershipLevel = "Gold";
        } else if (totalSpent >= 2000.0) {
            membershipLevel = "Silver";
        } else {
            membershipLevel = "Standard";
        }
    }

    void addRental(double amount) {
        totalRentals++;
        totalSpent += amount;
        updateMembership();
    }

    bool isLicenseValid() const {
        std::string currentDate = getCurrentDate();
        return licenseExpiry > currentDate;
    }

    void displayInfo() const {
        std::cout << "\n=== Customer Information ===" << std::endl;
        std::cout << "ID: " << customerId << " | Name: " << firstName << " " << lastName << std::endl;
        std::cout << "Email: " << email << " | Phone: " << phone << std::endl;
        std::cout << "Address: " << address << std::endl;
        std::cout << "License: " << licenseNumber << " | Expiry: " << licenseExpiry << std::endl;
        std::cout << "Age: " << age << " | License Valid: " << (isLicenseValid() ? "Yes" : "No") << std::endl;
        std::cout << "Total Rentals: " << totalRentals << std::endl;
        std::cout << "Total Spent: $" << std::fixed << std::setprecision(2) << totalSpent << std::endl;
        std::cout << "Membership: " << membershipLevel << std::endl;
    }

    std::string getCustomerId() const { return customerId; }
    std::string getFullName() const { return firstName + " " + lastName; }
    std::string getEmail() const { return email; }
    std::string getLicenseNumber() const { return licenseNumber; }
    bool getLicenseValidity() const { return isLicenseValid(); }
    int getAge() const { return age; }
    std::string getMembershipLevel() const { return membershipLevel; }

private:
    std::string getCurrentDate() const {
        time_t now = time(0);
        tm* localTime = localtime(&now);
        std::stringstream ss;
        ss << (1900 + localTime->tm_year) << "-" 
           << std::setw(2) << std::setfill('0') << (1 + localTime->tm_mon) << "-" 
           << std::setw(2) << std::setfill('0') << localTime->tm_mday;
        return ss.str();
    }
};

class Rental {
private:
    std::string rentalId;
    std::string customerId;
    std::string vehicleId;
    std::string rentalDate;
    std::string returnDate;
    int rentalDays;
    double totalCost;
    std::string status;
    int initialMileage;
    int finalMileage;
    std::string insuranceType;
    double insuranceCost;

public:
    Rental(std::string rid, std::string cid, std::string vid, std::string rdate,
           std::string retdate, int days, double cost, int initMileage, std::string insType)
        : rentalId(rid), customerId(cid), vehicleId(vid), rentalDate(rdate),
          returnDate(retdate), rentalDays(days), totalCost(cost), status("Active"),
          initialMileage(initMileage), finalMileage(0), insuranceType(insType), 
          insuranceCost(0.0) {
        calculateInsuranceCost();
        totalCost += insuranceCost;
    }

    void calculateInsuranceCost() {
        if (insuranceType == "Full") {
            insuranceCost = totalCost * 0.15;
        } else if (insuranceType == "Partial") {
            insuranceCost = totalCost * 0.08;
        } else {
            insuranceCost = 0.0;
        }
    }

    void completeRental(int endMileage) {
        finalMileage = endMileage;
        status = "Completed";
    }

    void updateStatus(const std::string& newStatus) {
        status = newStatus;
    }

    void displayInfo() const {
        std::cout << "\n=== Rental " << rentalId << " ===" << std::endl;
        std::cout << "Customer: " << customerId << " | Vehicle: " << vehicleId << std::endl;
        std::cout << "Rental Date: " << rentalDate << " | Return Date: " << returnDate << std::endl;
        std::cout << "Days: " << rentalDays << " | Status: " << status << std::endl;
        std::cout << "Mileage: " << initialMileage << "km to " << finalMileage << "km" << std::endl;
        std::cout << "Insurance: " << insuranceType << " ($" << insuranceCost << ")" << std::endl;
        std::cout << "Total Cost: $" << std::fixed << std::setprecision(2) << totalCost << std::endl;
    }

    std::string getRentalId() const { return rentalId; }
    std::string getCustomerId() const { return customerId; }
    std::string getVehicleId() const { return vehicleId; }
    std::string getStatus() const { return status; }
    double getTotalCost() const { return totalCost; }
    int getFinalMileage() const { return finalMileage; }
};

class CarRentalSystem {
private:
    std::vector<std::shared_ptr<Vehicle>> vehicles;
    std::vector<std::shared_ptr<Customer>> customers;
    std::vector<std::shared_ptr<Rental>> rentals;
    std::string companyName;
    int nextRentalId;

    std::string generateRentalId() {
        return "RNT" + std::to_string(nextRentalId++);
    }

    std::string generateCustomerId() {
        return "CUST" + std::to_string(customers.size() + 1);
    }

    std::string generateVehicleId() {
        return "VEH" + std::to_string(vehicles.size() + 1);
    }

    std::string getCurrentDate() {
        time_t now = time(0);
        tm* localTime = localtime(&now);
        std::stringstream ss;
        ss << (1900 + localTime->tm_year) << "-" 
           << std::setw(2) << std::setfill('0') << (1 + localTime->tm_mon) << "-" 
           << std::setw(2) << std::setfill('0') << localTime->tm_mday;
        return ss.str();
    }

public:
    CarRentalSystem(std::string name) : companyName(name), nextRentalId(1001) {
        initializeVehicles();
    }

    void initializeVehicles() {
        addVehicle("Toyota", "Camry", 2023, "Sedan", "Gasoline", "Automatic", 5, 15000, 45.00, "ABC123", "White");
        addVehicle("Honda", "CR-V", 2023, "SUV", "Gasoline", "Automatic", 5, 12000, 55.00, "DEF456", "Black");
        addVehicle("Ford", "F-150", 2023, "Truck", "Gasoline", "Automatic", 3, 8000, 75.00, "GHI789", "Red");
        addVehicle("BMW", "5 Series", 2023, "Luxury", "Gasoline", "Automatic", 5, 5000, 120.00, "JKL012", "Blue");
        addVehicle("Tesla", "Model 3", 2023, "Electric", "Electric", "Automatic", 5, 3000, 85.00, "MNO345", "Gray");
    }

    void addVehicle(std::string make, std::string model, int year, std::string type,
                    std::string fuel, std::string trans, int seats, int mileage,
                    double rate, std::string plate, std::string color) {
        std::string vehicleId = generateVehicleId();
        auto vehicle = std::make_shared<Vehicle>(vehicleId, make, model, year, type, fuel, trans, seats, mileage, rate, plate, color);
        
        if (type == "Luxury") {
            vehicle->addFeature("Leather Seats");
            vehicle->addFeature("Navigation");
            vehicle->addFeature("Premium Sound");
        } else if (type == "SUV") {
            vehicle->addFeature("All-Wheel Drive");
            vehicle->addFeature("Roof Rack");
        } else if (type == "Electric") {
            vehicle->addFeature("Fast Charging");
            vehicle->addFeature("Autopilot");
        }
        
        vehicles.push_back(vehicle);
        std::cout << "Vehicle added successfully! ID: " << vehicleId << std::endl;
    }

    void displayAllVehicles() {
        std::cout << "\n=== All Vehicles ===" << std::endl;
        for (const auto& vehicle : vehicles) {
            vehicle->displayInfo();
        }
    }

    void displayAvailableVehicles() {
        std::cout << "\n=== Available Vehicles ===" << std::endl;
        bool found = false;
        for (const auto& vehicle : vehicles) {
            if (vehicle->getAvailability()) {
                vehicle->displayInfo();
                found = true;
            }
        }
        if (!found) {
            std::cout << "No available vehicles." << std::endl;
        }
    }

    void searchVehiclesByType(const std::string& type) {
        std::cout << "\n=== " << type << " Vehicles ===" << std::endl;
        bool found = false;
        for (const auto& vehicle : vehicles) {
            if (vehicle->getType() == type && vehicle->getAvailability()) {
                vehicle->displayInfo();
                found = true;
            }
        }
        if (!found) {
            std::cout << "No available " << type << " vehicles." << std::endl;
        }
    }

    void addCustomer() {
        std::string fname, lname, email, phone, address, license, expiry;
        int age;
        
        std::cout << "\n=== Add New Customer ===" << std::endl;
        std::cout << "First Name: ";
        std::cin >> fname;
        std::cout << "Last Name: ";
        std::cin >> lname;
        std::cout << "Email: ";
        std::cin >> email;
        std::cout << "Phone: ";
        std::cin >> phone;
        
        std::cin.ignore();
        std::cout << "Address: ";
        std::getline(std::cin, address);
        std::cout << "Driver License Number: ";
        std::getline(std::cin, license);
        std::cout << "License Expiry (YYYY-MM-DD): ";
        std::getline(std::cin, expiry);
        std::cout << "Age: ";
        std::cin >> age;

        if (age < 21) {
            std::cout << "Customer must be at least 21 years old." << std::endl;
            return;
        }

        std::string customerId = generateCustomerId();
        customers.push_back(std::make_shared<Customer>(customerId, fname, lname, email, phone, address, license, expiry, age));
        std::cout << "Customer added successfully! ID: " << customerId << std::endl;
    }

    void displayAllCustomers() {
        std::cout << "\n=== All Customers ===" << std::endl;
        for (const auto& customer : customers) {
            customer->displayInfo();
        }
    }

    void createRental() {
        if (customers.empty() || vehicles.empty()) {
            std::cout << "Need customers and vehicles to create a rental." << std::endl;
            return;
        }

        std::cout << "\nAvailable Customers:" << std::endl;
        for (size_t i = 0; i < customers.size(); ++i) {
            std::cout << i + 1 << ". " << customers[i]->getFullName();
            if (!customers[i]->getLicenseValidity()) {
                std::cout << " [LICENSE EXPIRED]";
            }
            std::cout << std::endl;
        }

        int customerIndex;
        std::cout << "Select customer (number): ";
        std::cin >> customerIndex;

        if (customerIndex < 1 || customerIndex > customers.size()) {
            std::cout << "Invalid customer selection." << std::endl;
            return;
        }

        if (!customers[customerIndex-1]->getLicenseValidity()) {
            std::cout << "Customer license is expired. Cannot proceed with rental." << std::endl;
            return;
        }

        displayAvailableVehicles();
        
        std::string vehicleId;
        std::cout << "Enter Vehicle ID to rent: ";
        std::cin >> vehicleId;

        auto vehicleIt = std::find_if(vehicles.begin(), vehicles.end(),
            [&vehicleId](const std::shared_ptr<Vehicle>& v) {
                return v->getVehicleId() == vehicleId && v->getAvailability();
            });

        if (vehicleIt == vehicles.end()) {
            std::cout << "Vehicle not available or doesn't exist." << std::endl;
            return;
        }

        std::string rentalDate, returnDate;
        int rentalDays;
        std::string insuranceType;
        
        std::cout << "Rental Date (YYYY-MM-DD): ";
        std::cin >> rentalDate;
        std::cout << "Return Date (YYYY-MM-DD): ";
        std::cin >> returnDate;
        std::cout << "Rental Days: ";
        std::cin >> rentalDays;
        std::cout << "Insurance Type (None/Partial/Full): ";
        std::cin >> insuranceType;

        double totalCost = (*vehicleIt)->getDailyRate() * rentalDays;
        int initialMileage = (*vehicleIt)->getMileage();

        std::string rentalId = generateRentalId();
        auto rental = std::make_shared<Rental>(rentalId, customers[customerIndex-1]->getCustomerId(),
                                              vehicleId, rentalDate, returnDate, rentalDays,
                                              totalCost, initialMileage, insuranceType);

        if ((*vehicleIt)->rentVehicle()) {
            rentals.push_back(rental);
            customers[customerIndex-1]->addRental(rental->getTotalCost());
            std::cout << "Rental created successfully! Rental ID: " << rentalId << std::endl;
            std::cout << "Total Cost: $" << rental->getTotalCost() << std::endl;
        } else {
            std::cout << "Failed to create rental." << std::endl;
        }
    }

    void completeRental() {
        std::string rentalId;
        std::cout << "Enter Rental ID to complete: ";
        std::cin >> rentalId;

        auto rentalIt = std::find_if(rentals.begin(), rentals.end(),
            [&rentalId](const std::shared_ptr<Rental>& r) {
                return r->getRentalId() == rentalId && r->getStatus() == "Active";
            });

        if (rentalIt != rentals.end()) {
            int finalMileage;
            std::cout << "Enter final mileage: ";
            std::cin >> finalMileage;

            (*rentalIt)->completeRental(finalMileage);

            auto vehicleIt = std::find_if(vehicles.begin(), vehicles.end(),
                [rentalIt](const std::shared_ptr<Vehicle>& v) {
                    return v->getVehicleId() == (*rentalIt)->getVehicleId();
                });

            if (vehicleIt != vehicles.end()) {
                (*vehicleIt)->returnVehicle((*rentalIt)->getFinalMileage());
            }

            std::cout << "Rental completed successfully!" << std::endl;
            (*rentalIt)->displayInfo();
        } else {
            std::cout << "Active rental not found!" << std::endl;
        }
    }

    void displayActiveRentals() {
        std::cout << "\n=== Active Rentals ===" << std::endl;
        bool found = false;
        for (const auto& rental : rentals) {
            if (rental->getStatus() == "Active") {
                rental->displayInfo();
                found = true;
            }
        }
        if (!found) {
            std::cout << "No active rentals." << std::endl;
        }
    }

    void generateRevenueReport() {
        double totalRevenue = 0.0;
        int totalRentals = rentals.size();
        int completedRentals = 0;
        std::map<std::string, double> revenueByType;

        for (const auto& rental : rentals) {
            if (rental->getStatus() == "Completed") {
                totalRevenue += rental->getTotalCost();
                completedRentals++;
                
                auto vehicleIt = std::find_if(vehicles.begin(), vehicles.end(),
                    [rental](const std::shared_ptr<Vehicle>& v) {
                        return v->getVehicleId() == rental->getVehicleId();
                    });

                if (vehicleIt != vehicles.end()) {
                    revenueByType[(*vehicleIt)->getType()] += rental->getTotalCost();
                }
            }
        }

        std::cout << "\n=== Revenue Report ===" << std::endl;
        std::cout << "Total Rentals: " << totalRentals << std::endl;
        std::cout << "Completed Rentals: " << completedRentals << std::endl;
        std::cout << "Total Revenue: $" << std::fixed << std::setprecision(2) << totalRevenue << std::endl;
        std::cout << "Revenue by Vehicle Type:" << std::endl;
        for (const auto& [type, revenue] : revenueByType) {
            std::cout << "  " << type << ": $" << revenue << std::endl;
        }
    }

    void displayMenu() {
        std::cout << "\n=== " << companyName << " Car Rental System ===" << std::endl;
        std::cout << "1. Display All Vehicles" << std::endl;
        std::cout << "2. Display Available Vehicles" << std::endl;
        std::cout << "3. Search Vehicles by Type" << std::endl;
        std::cout << "4. Add Customer" << std::endl;
        std::cout << "5. Display All Customers" << std::endl;
        std::cout << "6. Create Rental" << std::endl;
        std::cout << "7. Complete Rental" << std::endl;
        std::cout << "8. Display Active Rentals" << std::endl;
        std::cout << "9. Revenue Report" << std::endl;
        std::cout << "10. Add Vehicle" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Enter your choice: ";
    }
};

int main() {
    CarRentalSystem system("Speedy Rentals");
    
    int choice;
    do {
        system.displayMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                system.displayAllVehicles();
                break;
            case 2:
                system.displayAvailableVehicles();
                break;
            case 3: {
                std::string type;
                std::cout << "Enter vehicle type (Sedan/SUV/Truck/Luxury/Electric): ";
                std::cin >> type;
                system.searchVehiclesByType(type);
                break;
            }
            case 4:
                system.addCustomer();
                break;
            case 5:
                system.displayAllCustomers();
                break;
            case 6:
                system.createRental();
                break;
            case 7:
                system.completeRental();
                break;
            case 8:
                system.displayActiveRentals();
                break;
            case 9:
                system.generateRevenueReport();
                break;
            case 10: {
                std::string make, model, type, fuel, trans, plate, color;
                int year, seats, mileage;
                double rate;
                std::cin.ignore();
                std::cout << "Make: "; std::getline(std::cin, make);
                std::cout << "Model: "; std::getline(std::cin, model);
                std::cout << "Year: "; std::cin >> year;
                std::cout << "Type: "; std::cin >> type;
                std::cout << "Fuel Type: "; std::cin >> fuel;
                std::cout << "Transmission: "; std::cin >> trans;
                std::cout << "Seats: "; std::cin >> seats;
                std::cout << "Mileage: "; std::cin >> mileage;
                std::cout << "Daily Rate: "; std::cin >> rate;
                std::cout << "License Plate: "; std::cin >> plate;
                std::cout << "Color: "; std::cin >> color;
                system.addVehicle(make, model, year, type, fuel, trans, seats, mileage, rate, plate, color);
                break;
            }
            case 0:
                std::cout << "Thank you for using Car Rental System!" << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 0);

    return 0;
}
