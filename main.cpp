#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>

using namespace std;

// Function to get the target time (New Year's Day 2026)
chrono::system_clock::time_point get_new_year_time() {
    tm new_year_tm = {};
    new_year_tm.tm_year = 2027 - 1900; // Years since 1900
    new_year_tm.tm_mon = 0;            // January
    new_year_tm.tm_mday = 1;           // 1st
    new_year_tm.tm_hour = 0;
    new_year_tm.tm_min = 0;
    new_year_tm.tm_sec = 0;

    return chrono::system_clock::from_time_t(mktime(&new_year_tm));
}

int main() {
    auto target = get_new_year_time();

    while (true) {
        auto now = chrono::system_clock::now();
        
        // Calculate the duration between now and the target
        auto diff = target - now;

        if (diff.count() <= 0) {
            cout << "\nHAPPY NEW YEAR 2027! \a" << endl;
            break;
        }

        // Convert duration into days, hours, minutes, and seconds
        auto days = chrono::duration_cast<chrono::hours>(diff).count() / 24;
        auto hours = chrono::duration_cast<chrono::hours>(diff).count() % 24;
        auto minutes = chrono::duration_cast<chrono::minutes>(diff).count() % 60;
        auto seconds = chrono::duration_cast<chrono::seconds>(diff).count() % 60;

        // Display the countdown ( \r returns the cursor to the start of the line)
        cout << "\rTime until New Year: " 
             << days << "d " 
             << setfill('0') << setw(2) << hours << "h " 
             << setfill('0') << setw(2) << minutes << "m " 
             << setfill('0') << setw(2) << seconds << "s " << flush;

        // Sleep for 1 second before updating
        this_thread::sleep_for(chrono::seconds(1));
    }

    return 0;
}