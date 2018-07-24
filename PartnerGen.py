import random

random.seed(input("\nseed: "))

with open("Members") as f:
    Members = f.read().splitlines() 

cIndex = 0

print()

while len(Members) > 1:
    partner1 = random.choice(Members)
    Members.remove(partner1)
    partner2 = random.choice(Members)
    Members.remove(partner2)
    partner1 += ' '
    partner2 += ' '
    if (cIndex % 2 == 0):
        print("\033[1;36;40m" + partner1.ljust(20, '-') + "-> " + partner2)
    else:
        print("\033[1;35;40m" + partner1.ljust(20, '-') + "-> " + partner2)
    cIndex += 1

if len(Members) == 1:
    print("\033[93m" + "Loner ".ljust(20, '-') + "-> " + Members.pop())