#ifndef REQUIREDCLSSES_H
#define REQUIREDCLSSES_H
#include <string>
#include <ctime>
#include <vector>

class Ticket
{
    private:
        bool isPrvilaged;
        int chargeRate;
        std::time_t timeStarted;

    public:
        bool getPrivlage(){return this->isPrvilaged;}
        int getChargeRate(){return this->chargeRate;}
        int getTimeStarted(){return this->timeStarted;}
        void setPrivlage(bool privLevel);
        void setChargeRate(int rate);
        void setTimeStarted(std::time_t time);
        Ticket& operator=( const Ticket& right ); 
};

class Space
{
    private:
        bool isFilled, isDisabled;

    public:
        bool getIsFilled(){ return this->isFilled;}
        bool getIsDisabled(){ return this->isDisabled;}
        void setIsDisabled(bool isDisabled);
        void setIsFilled(bool filled);
};


class Vehicle
{
    private:
        Ticket ticket;
        bool disabilitySign;
        std::string licensePlate;
    public:
        Vehicle(Ticket ticket, bool isDisabled);
        Ticket& getTicket(){ return this->ticket;}
        std::string getPlate(){return this->licensePlate;}
        bool getDisabilitySign(){return this->disabilitySign;}
        void setDisabilitySign(bool sign);
        
    
        void requestHelp();

};


class Payment
{
    public:
        virtual void pay(float amount);
};



class Credit : public Payment
{
    private:
        int cardNumber;
        int pin;
    public:
        void pay(float amount);
};


class Debit : public Payment
{
    private:
        int cardNumber;
        int pin;
    public:
        void pay(float amount);
};


class Bank
{
    public:
        std::string name;
        void verify(int cardNumber,int pin);
};

class Cash : public Payment
{
   
    public:
        void pay(float amount);
};


class ParkingLot
{
    private:
        const int normalSpaces;
        const int disabledSpaces;
        int normalSpacesFilled;
        int disabledSpacesFilled;

    public:
        int getDisabledSpacesRemaining(){return disabledSpaces-disabledSpacesFilled;}
        int getNormalSpacesRemaining(){return normalSpaces-normalSpacesFilled;}
        void setNormalSpaceFilled(int n);
        void setDisabledSpaceFilled(int n);
        
};

class System
{
    public:
        std::vector<Vehicle> cars;
        Ticket verify(Vehicle vehicleInfo);
        void recordLicencePlate(Vehicle vehicle);
        void deletePlate(Vehicle vehicleInfo);
};

class TicketBooth
{
    public:
        System sys;
        ParkingLot parkingLotData;
        void Enter(Vehicle &vechicle , bool isDisabled);
        void Exit(Vehicle vehicle,Payment payment);

};

#endif
