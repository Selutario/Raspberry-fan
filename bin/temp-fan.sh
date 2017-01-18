echo `sensors | grep -m 1 temp1 | cut -d" " -f9 | cut -d"+" -f2 | cut -c 1-2`
