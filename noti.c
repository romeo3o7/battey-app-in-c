#include "battery.h"
#include <libnotify/notify.h>
#include <unistd.h>
#include <stdio.h>

void noti(char *c) {
   NotifyNotification *m = notify_notification_new("Charge", c, NULL);
   notify_notification_show(m, NULL);
    g_object_unref(G_OBJECT(m));
}

int main() {

    notify_init("battery_app");
    int percentage;
    _Bool low_battery_notify = 0,high_battery_notify = 0;
    while (1) {
    printf("Program is running...");
    percentage = get_percentage();
    if (percentage == -1){ notify_uninit(); fprintf(stderr,"Failed to retrive Percentage"); return -1; }

    if (percentage >= 76 && !high_battery_notify) { noti("battery charged");high_battery_notify = 1; }

    if (percentage <= 30 && !low_battery_notify ) { noti("battery too low"); low_battery_notify  = 1; }

    if (percentage < 75) high_battery_notify = 0;
    if (percentage > 29) low_battery_notify = 0;
    sleep(280);
    }
    notify_uninit();
    return 0;
}
