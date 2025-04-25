#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;



bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<int>& shiftsWorked,
    size_t day,
    size_t slot)
{
    if(day == sched.size())
    {
        return true;
    }

    if(slot == dailyNeed)
    {
        return scheduleHelper(avail, dailyNeed, maxShifts, sched, shiftsWorked, day+1, 0);
    }

    size_t numWorkers = avail[0].size();
    for(Worker_T worker = 0; worker < numWorkers; ++worker)
    {
        if(avail[day][worker] && shiftsWorked[worker] < (int)maxShifts)
        {
            if(find(sched[day].begin(), sched[day].end(), worker) != sched[day].end())
            {
                continue;
            }

            sched[day][slot] = worker;
            shiftsWorked[worker]++;

            if(scheduleHelper(avail, dailyNeed, maxShifts, sched, shiftsWorked, day, slot+1))
            {
                return true;
            }

            shiftsWorked[worker]--;
            sched[day][slot] = INVALID_ID;
        }
    }

    return false;
}



// Add prototypes for any helper functions here


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
     size_t n = avail.size();
    size_t k = avail[0].size();
    sched.resize(n, vector<Worker_T>(dailyNeed, INVALID_ID));

    vector<int> shiftsWorked(k, 0);

    return scheduleHelper(avail, dailyNeed, maxShifts, sched, shiftsWorked, 0, 0);



}

