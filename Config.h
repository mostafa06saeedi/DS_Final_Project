#ifndef CONFIG_H
#define CONFIG_H

class Config
{
public:
    static int MAX_RENTAL_DAYS;
    static double DAILY_PENALTY_RATE;
    static int MAX_CONCURRENT_RESERVATIONS;

    static void setMaxRentalDays(int days);
    static void setPenaltyRate(double rate);
    static void setMaxReservations(int count);
};

#endif