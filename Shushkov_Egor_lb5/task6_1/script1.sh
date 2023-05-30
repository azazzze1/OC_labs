#!/bin/bash
IP=127.0.0.1
PORT=8888

for i in {1..100}
do
    echo -e "client $i start" | ./client $IP $PORT &
done
