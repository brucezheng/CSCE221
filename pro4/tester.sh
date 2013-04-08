#!/bin/bash
> out.txt
for i in `seq 7 7`;
do
	for j in `seq 3 4`;
	do
		echo $i " " $j
		echo "---" $i " " $j >> out.txt
		for k in `seq 1 15`;
		do
			./a.out $i $j $k >> out.txt
		done
	done	
done
echo "Done!"
