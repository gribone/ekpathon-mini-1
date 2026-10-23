#include "api.h"
#include "helpers.h"
#include "parser.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char *get_bus_line_name(int bus_choice, int direction) {
  int bus_index = index_of_bus(bus_choice, direction);
  return bus_lines[bus_index];
}

int get_number_of_stops(int bus_choice, int direction) {
  int bus_index = index_of_bus(bus_choice, direction);
  int num_stops = 0;
  grab_bus_indices(bus_index, &num_stops);
  return num_stops;
}

char *get_stop_name_on_line(int bus_choice, int direction, int stop_number) {
  int bus_index = index_of_bus(bus_choice, direction);
  int num_stops = 0;
  int *indices = grab_bus_indices(bus_index, &num_stops);
  if (stop_number < 1 || stop_number > num_stops) {
    return "INVALID_STOP";
  }
  return bus_stops[indices[stop_number - 1]][1];
}

int get_stop_code_on_line(int bus_choice, int direction, int stop_number) {
  int bus_index = index_of_bus(bus_choice, direction);
  int num_stops = 0;
  int *indices = grab_bus_indices(bus_index, &num_stops);
  if (stop_number < 1 || stop_number > num_stops) {
    return -1;
  }
  return atoi(bus_stops[indices[stop_number - 1]][0]);
}

void print_stops_of_bus_line(int bus_choice, int direction) {
  int bus_index = index_of_bus(bus_choice, direction);
  int num_stops = 0;
  int *indices = grab_bus_indices(bus_index, &num_stops);
  printf("%s:\n", bus_lines[bus_index]);
  for (int i = 0; i < num_stops; i++) {
    int stop_index = indices[i];
    printf("%d. %s (%s)\n", i + 1, bus_stops[stop_index][1],
           bus_stops[stop_index][0]);
  }
}

char *get_stop_name_by_code(int stop_code) {
  int index = search_for_code_index(stop_code);
  if (index == -1) {
    return "UNKNOWN_STOP";
  }
  return bus_stops[index][1];
}

int does_bus_stop_at_code(int bus_choice, int direction, int stop_code) {
  int bus_index = index_of_bus(bus_choice, direction);
  int num_stops = 0;
  int *indices = grab_bus_indices(bus_index, &num_stops);
  for (int i = 0; i < num_stops; i++) {
    if (atoi(bus_stops[indices[i]][0]) == stop_code) {
      return i + 1;
    }
  }
  return 0;
}

int get_next_arrival_time(int bus_choice, int direction, int stop_number) {
  int bus_index = index_of_bus(bus_choice, direction);
  int num_stops = 0;
  grab_bus_indices(bus_index, &num_stops);
  if (stop_number < 1 || stop_number > num_stops) {
    return -1;
  }
  int *local_time = grab_local_time();
  int *arrival_times = list_of_arrival_times_two_hour_window(
      local_time, stop_number - 1, bus_index);
  int next_arrival = -1;
  if (arrival_times && arrival_times[0] >= 0) {
    next_arrival = arrival_times[0];
  }
  free(arrival_times);
  free(local_time);
  return next_arrival;
}

int get_all_arrival_times(int bus_choice, int direction, int stop_number,
                          int results[15]) {
  for (int k = 0; k < 15; k++) {
    results[k] = -1;
  }
  int bus_index = index_of_bus(bus_choice, direction);
  int num_stops = 0;
  grab_bus_indices(bus_index, &num_stops);
  if (stop_number < 1 || stop_number > num_stops) {
    return 0;
  }
  int *local_time = grab_local_time();
  int *arrival_times = list_of_arrival_times_two_hour_window(
      local_time, stop_number - 1, bus_index);
  int count = 0;
  if (arrival_times) {
    while (count < 15 && arrival_times[count] >= 0) {
      results[count] = arrival_times[count];
      count++;
    }
    free(arrival_times);
  }
  free(local_time);
  return count;
}

int get_number_of_departures(int bus_choice, int direction) {
  int bus_index = index_of_bus(bus_choice, direction);
  return departures[bus_index][0][1] - 1;
}

int get_departure_hour(int bus_choice, int direction, int departure_number) {
  int bus_index = index_of_bus(bus_choice, direction);
  int total = departures[bus_index][0][1] - 1;
  if (departure_number < 1 || departure_number > total) {
    return -1;
  }
  return departures[bus_index][departure_number][0];
}

int get_departure_minute(int bus_choice, int direction, int departure_number) {
  int bus_index = index_of_bus(bus_choice, direction);
  int total = departures[bus_index][0][1] - 1;
  if (departure_number < 1 || departure_number > total) {
    return -1;
  }
  return departures[bus_index][departure_number][1];
}

int get_current_hour() {
  int *local_time = grab_local_time();
  int hour = local_time[0];
  free(local_time);
  return hour;
}

int get_current_minute() {
  int *local_time = grab_local_time();
  int min = local_time[1];
  free(local_time);
  return min;
}

inline static double std_divation(int hour, int minute, double max) {
  const double time_x = hour + minute / 60.0;
  const double a = 0.5;
  return max * exp(-a * time_x * time_x);
}

inline static double demo_rush_hour(int hour, int minute) {
  const double time_x = hour + minute / 60.0;
  const double max = 100;
  return sin(time_x) + max / 2 + std_divation(hour - 9, minute, max - 2) +
         std_divation(hour - 17, minute, max);
}

double demo_get_fullness(int bus_choice, int direction, int hour, int minute) {
  srand(time(NULL));
  int deviation =
      rand() % 15; /* How much to deviate from the rush_hour function */
  return demo_rush_hour(hour, minute);
}
