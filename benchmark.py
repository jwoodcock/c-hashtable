# benchmark.py - python equivalent of benchmark.c
# to run it:
#   $ python benchmark.py < sam.txt

import sys

seen = set()
for word in sys.stdin.read().split():
    word = word.lower().rstrip('?!.,')[:9]
    if word not in seen:
        print(word)
        seen.add(word)

print("\nFound %d different words." % len(seen))
