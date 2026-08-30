#include "Config.h"

int Config::MAX_RENTAL_DAYS = 30;
double Config::DAILY_PENALTY_RATE = 0.1;
int Config::MAX_CONCURRENT_RESERVATIONS = 3;

void Config::setMaxRentalDays(int days)
{
    if (days > 0)
        MAX_RENTAL_DAYS = days;
}

void Config::setPenaltyRate(double rate)
{
    if (rate >= 0 && rate <= 1.0)
        DAILY_PENALTY_RATE = rate;
}

void Config::setMaxReservations(int count)
{
    if (count > 0)
        MAX_CONCURRENT_RESERVATIONS = count;
}
