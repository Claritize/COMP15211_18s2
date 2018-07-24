import random

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

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
    print(bcolors.WARNING + "Loner ".ljust(20, '-') + "-> " + Members.pop())