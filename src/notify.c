#include <systemd/sd-bus.h>
#include <stdio.h>
#include <string.h>
int send_notification(const char *summary, const char *body) {
    sd_bus *bus = NULL;
    sd_bus_message *msg = NULL;
    int r;

    r = sd_bus_open_user(&bus);
    if (r < 0) goto finish;

    r = sd_bus_message_new_method_call(
        bus, &msg,
        "org.freedesktop.Notifications",
        "/org/freedesktop/Notifications",
        "org.freedesktop.Notifications",
        "Notify"
    );
    if (r < 0) goto finish;

    r = sd_bus_message_append(msg, "susss",
        "my-app", 0, "", summary, body);
    if (r < 0) goto finish;

    r = sd_bus_message_open_container(msg, 'a', "s"); /* actions */
    if (r < 0) goto finish;
    r = sd_bus_message_close_container(msg);
    if (r < 0) goto finish;

    r = sd_bus_message_open_container(msg, 'a', "{sv}"); /* hints */
    if (r < 0) goto finish;
    r = sd_bus_message_close_container(msg);
    if (r < 0) goto finish;

    r = sd_bus_message_append(msg, "i", -1); /* expire_timeout */
    if (r < 0) goto finish;

    r = sd_bus_message_set_expect_reply(msg, 0);
    if (r < 0) goto finish;

    r = sd_bus_send(bus, msg, NULL);
    if (r < 0) goto finish;

    sd_bus_flush(bus);

finish:
    if (r < 0) fprintf(stderr, "send_notification: %s\n", strerror(-r));
    sd_bus_message_unref(msg);
    sd_bus_unref(bus);
    return r;
}
