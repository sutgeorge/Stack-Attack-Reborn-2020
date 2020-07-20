#!/bin/bash
pid=`ps -A | grep -i StackAttack | awk '{print $1}'`
ps -o nlwp $pid
