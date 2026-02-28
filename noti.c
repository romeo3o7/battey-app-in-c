#include "battery.h"
#include <libnotify/notify.h>
#include <unistd.h>

void noti(char *c) {
   NotifyNotification *m = notify_notification_new("Charge", c, NULL);
   notify_notification_show(m, NULL);
    g_object_unref(G_OBJECT(m));
}

int main() {

    notify_init("battery_app");
    int b, low_notify = 0,high_notify = 0;
    while (1) {
    b = get_percentage();
    if (b == -1){ notify_uninit(); return -1; }

    if (b >= 76 && !high_notify) { noti("battery charged"); high_notify = 1; }
    else if (b <= 30 && !low_notify) { noti("battery too low"); low_notify = 1; }
    if (b < 75) high_notify = 0;
    if (b > 30) low_notify = 0;
    sleep(280);
    }
    notify_uninit();
    return 0;
}
