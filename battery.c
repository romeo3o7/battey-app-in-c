#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>

#define PATH "/sys/class/power_supply/BAT1/capacity"

int get_percentage() {
    int lookup = open(PATH, O_RDONLY);
    if (lookup == -1) return -1;
    char i;
    int percentage = 0;
    while (read(lookup, &i , 1) == 1 && i != '\n') {
        percentage = percentage * 10 + (i - '0');
    }
    close(lookup);
    return percentage;
}
