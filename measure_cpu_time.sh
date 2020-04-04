#!/bin/bash
rm Results

sudo find . -name *.bench |
while read filename
do
    echo "Running simulator on $filename"    # ... or any other command using $filename
		
		./simulator -C $filename -T ms >> Results
done

exit 0

for f in ISCAS/iscas89/*; do
    # do some stuff here with "$f"
    # remember to quote it or spaces may misbehave
		#echo $f >> Results
		echo "Running" $f		
		#$f >> Results		

		#exec="$(time ./simulator -C $f)"
		./simulator -C $f -T ms >> Results
done

