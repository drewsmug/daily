#!/usr/bin/python3

import sys

seq = [1,2,2]
i = 2
val = 1
ones = 1
twos = 1

total = int(sys.argv[1])

print("Kolakoski Sequences")
print("\ttotal:" + sys.argv[1])

while len(seq) < total:
	if seq[i] == 1:
		ones += 1
	else:
		twos += 1

	c = seq[i]
	while c > 0:
		seq.append(val)
		c -= 1
	i += 1

	if val == 1:
		val = 2
	else:
		val = 1


while i < total:
	if seq[i] == 1:
		ones += 1
	else:
		twos += 1
	i += 1


def printseq ():
	c = 0
	while c < total:
		print(seq[c])
		c += 1


print("\tones:" + str(ones))
print("\ttwos:" + str(twos))
