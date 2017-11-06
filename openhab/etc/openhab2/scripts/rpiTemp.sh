#!/bin/bash
/opt/vc/bin/vcgencmd measure_temp| sed "s/[^0-9.]//g"