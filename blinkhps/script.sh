#!/bin/bash

target extended-remote 192.168.0.102:8081

remote /home/sabrina/work/blinkhps/hps_gpio hps_gpio

set remote exec-file hps_gpio

run
