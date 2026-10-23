// returns the full name of the bus, eg. "040 - PEIRAIAS - SINTAGMA"
// if you input 040 and 0 (0 is the normal direction, 1 is the return direction)
char *get_bus_line_name(int bus_choice, int direction);

// returns the total number of the stops a line (and direction) has.
// For example, 608 has 41 stops in the normal direction and 45 stops in the
// return direction.
int get_number_of_stops(int bus_choice, int direction);

// returns the name of the stop -- If the stop_number is out of bounds,
// it returns "INVALID_STOP"
// HOW TO GET stop_number: 1st. print (use print_stops_of_bus_line() below) the
// stops of a specific bus line (+direction)
// 2. The stop list is numbered by the printing function (starting from 1)
// 3. Grab the number of the stop you want to get the name of and input it as
// stop_number
char *get_stop_name_on_line(int bus_choice, int direction, int stop_number);

// returns the code of 6 digits of the stop
// given by the stop_number (see above how to get it)
int get_stop_code_on_line(int bus_choice, int direction, int stop_number);

// prints the numbered list of every stop
// of a specific bus line (+direction)
void print_stops_of_bus_line(int bus_choice, int direction);

// returns the name of a stop with a
// 6-digit integer code input --- returns "UNKNOWN STOP"
// if such code doesn't exist
char *get_stop_name_by_code(int stop_code);

// returns 1 (or higher) if a given bus route (bus_choice + direction)
// passes through the stop with the input stop_code
// returns 0 if not
int does_bus_stop_at_code(int bus_choice, int direction, int stop_code);

// returns the number of minutes left until the
// next bus (you must input what bus you want with bus_choice) arrives at
// a specific stop (input: stop_number of the bus route, not the 6-digit code!)
// returns -1 if no bus is arriving in the next two hours.
int get_next_arrival_time(int bus_choice, int direction, int stop_number);

// the results array is filled with the time (minutes) of all of the buses that
// are arriving within a two-hour window.
int get_all_arrival_times(int bus_choice, int direction, int stop_number,
                          int results[15]);

// returns the number of departures from
// a specific bus route (bus_choice + direction input)
int get_number_of_departures(int bus_choice, int direction);

// returns the hour (in integer form -> 23 instead of 11pm)
// of a departure with position number "departure_number" of a bus (+ direction)
// returns -1 if the position number does not exist
int get_departure_hour(int bus_choice, int direction, int departure_number);

// similar to the above, but for minutes.
// also -1 if the position number doesn't exist
int get_departure_minute(int bus_choice, int direction, int departure_number);

// gets local time hour in integer form
int get_current_hour();
// same as above but for minutes
int get_current_minute();

///////////////// DEMO JUST IN CASE FUNCTIONS //////////////////////////////

// retuerns how full in % the given bus is at a given time.
double demo_get_fullness(int bus_choice, int direction, int hour, int minute);
