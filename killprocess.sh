#!/bin/bash
kill -9 `ps -A | grep -i StackAttack | awk '{print $1}'`
