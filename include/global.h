#ifndef GLOBAL_H
#define GLOBAL_H
#include <stdbool.h>
#include <systemd/sd-bus.h>
int send_notification(const char *summary, const char *body);

#ifdef BUS
int parsing(sd_bus_message *m, void *userdata, sd_bus_error *error);
#endif

typedef struct  { 
    bool hpn;
    bool lpn;
    uint32_t isCharging;
    double per;
}battery;


int sendMessage(const char *c);
int logic (battery *s);
#endif
