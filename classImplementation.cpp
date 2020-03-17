#include "requiredClasses.h"
#include <string>
#include <ctime>
#include <math.h>

void Ticket::setPrivlage(bool privLevel)
{
    this->isPrvilaged = privLevel;
}

void Ticket::setChargeRate(int rate)
{
    this->chargeRate = rate;
}

void Ticket::setTimeStarted(std::time_t time)
{
    this->timeStarted = time;
}


Ticket& Ticket::operator=( const Ticket& right ) 
{
    this->isPrvilaged = right.isPrvilaged;
    this->chargeRate = right.chargeRate;
    this->timeStarted = right.timeStarted;
    return *this;
}

void Space::setIsDisabled(bool isDisabled)
{
    this->isDisabled = isDisabled;

}

void Space::setIsFilled(bool filled)
{
    this->isFilled = filled;
}


Vehicle::Vehicle(Ticket ticket, bool isDisabled)
{
    this->ticket = ticket;
    this->disabilitySign = isDisabled;
}


void Vehicle::setDisabilitySign(bool sign)
{
    this->disabilitySign = sign;
}

void Credit::pay(float amount)
{
    // charge this->cardNumber for amount with specified vender
}


void Debit::pay(float amount)
{
    // charge this-cardNumber for amount with specified bank
}


void Cash::pay(float amount)
{
    // send command to machine to receive amount in cash
}

void ParkingLot::setNormalSpaceFilled(int n)
{
    this->normalSpacesFilled = n;
}

void ParkingLot::setDisabledSpaceFilled(int n)
{
    this->disabledSpacesFilled = n;
}

void TicketBooth::Enter(Vehicle &vehicle , bool isDisabled)
{
    const int rate = 5; // random value

    std::time_t time = (int) std::time(nullptr);

    // if they have a disability and no disabled spots left
    // or they dont have a disability and spots left
    if (this->parkingLotData.getDisabledSpacesRemaining() < 1 || 
    !vehicle.getDisabilitySign() && this->parkingLotData.getNormalSpacesRemaining() > 0)
    
    {
        Ticket newTicket;
        newTicket.setPrivlage(false);
        newTicket.setChargeRate(rate);
        newTicket.setTimeStarted(time);
        vehicle.getTicket() = newTicket;
        sys.recordLicencePlate(vehicle);

    } else if (vehicle.getDisabilitySign() && this->parkingLotData.getDisabledSpacesRemaining() > 0){
        Ticket newTicket;

        newTicket.setPrivlage(true);
        newTicket.setChargeRate(rate);
        newTicket.setTimeStarted(time);
        vehicle.getTicket() = newTicket;

        sys.recordLicencePlate(vehicle);
    }
 }

 void TicketBooth::Exit(Vehicle vehicle,Payment payment)
 {
    float amount;
    std::time_t time = (int) std::time(nullptr);
    Ticket ticket;

    if(vehicle.getTicket() == NULL){
        ticket = sys.verify(vehicle);
    }else{
        ticket = vehicle.getTicket();
    }

    // secs to hours, pays by the hour
    int timeSpent = ceil((time - ticket.getTimeStarted()) / 3600);

    amount = ticket.getChargeRate() * timeSpent;

    payment.pay(amount);

    sys.deletePlate(vehicle);
 }

void System::recordLicencePlate(Vehicle vehicle)
{
    cars.push_back(vehicle);
};


Ticket System::verify(Vehicle vehicleInfo)
{
    for(int i = 0; i < cars.size; i++){
        if(cars[i].getPlate() == vehicleInfo.getPlate()){
            return cars[i].getTicket();
        }
    }
    vehicleInfo.requestHelp();
}

void System::deletePlate(Vehicle vehicleInfo)
{
    for(int i = 0; i < cars.size; i++){
        if(cars[i].getPlate() == vehicleInfo.getPlate()){
            cars.erase (cars.begin() + i);
        }
    }
}