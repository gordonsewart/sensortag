#!/bin/bash

echo `sudo hciconfig hci0 down`
echo `sudo hciconfig hci0 up`
echo `sudo hciconfig hci0 noscan`

usage() {
    echo "./sensorTag.sh <MAC Address> > <Hex-Dump Filename>"
    exit 1
}

[[ $# -ne 1 ]] && usage

echo "starting run_gatttool.sh"

./run_gatttool.sh $1 | gawk '{ print system("date"), $0; }'
