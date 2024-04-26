#include "sort.h"

void usage(const char *prog_name) {
    fprintf(stderr, "Usage: %s [ARGS] [-M members] [SORT METHOD]\n\n"
                    "\tSort methods:\n"
                    "\t\t-s - selection sort\n"
                    "\t\t-i - insertion sort\n"
                    "\t\t-q - quick sort\n"
                    "\t\t-m - merge sort\n"
                    "\t\t-H - heap sort\n"
                    "\t\t-c - counting sort\n"
                    "\tArgs:\n"
                    "\t\t-p - prints sorted array in stdout\n"
                    "\n\t-M members - used to change array[members] size (default members == 1000)\n"
                    "\n\tExample:\n"
                    "\t\t%s -m 100000 -s - sorting 100000 members array with selection sort method\n"
                    "\n\t-h - show this help page\n"
    , prog_name, prog_name);
}