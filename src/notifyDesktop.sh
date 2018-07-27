#!/bin/sh
# get list of current users
for x in $(who | sort -u -k1,1 | awk '{print $1}'); do
  # send message to anyone on display 0
  dbus_session_file=$(eval echo "~$x")/.dbus/session-bus/$(cat /var/lib/dbus/machine-id)-0
  if [ -e "$dbus_session_file" ]; then
    su -l "$x" -c "source '$dbus_session_file'; export DISPLAY=:0; notify-send -u critical -t 2000 '$1' '$2'"
  fi
done

