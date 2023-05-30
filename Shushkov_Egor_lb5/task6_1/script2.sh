#!/bin/bash
IP=127.0.0.1
PORT=9999

for i in {1..20}
do
    echo -e "client $i start" | ./client $IP $PORT &
done
