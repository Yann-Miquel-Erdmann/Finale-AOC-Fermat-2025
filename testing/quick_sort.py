import random

def swap(a, i0, i1):
    c = a[i1]
    a[i1] = a[i0]
    a[i0] = c
    return a

def partition(a, l0, hi):
    pivot = a[hi]
    i = l0
    for j in range(l0, hi):
        if a[j] <= pivot:
            a = swap(a, i, j)
            i += 1
    a = swap(a, i, hi)
    b = []
    b.append(i)
    b.append(a)
    return b

def quicksort(a, l0, hi):
    if l0 > hi or l0 < 0:
        return a
    result = partition(a, l0, hi)
    p = result[0]
    a = result[1]
    a = quicksort(a, p + 1, hi)
    a = quicksort(a, l0, p - 1)
    return a

n = 5000
l = []

for i in range(1, n + 1):
    l.append(i)

random.seed(12)
for i in range(n - 1, -1, -1):
    j = random.random()
    l = swap(l, i, int(j * n))
    
l2 = quicksort(l, 0, n - 1)
