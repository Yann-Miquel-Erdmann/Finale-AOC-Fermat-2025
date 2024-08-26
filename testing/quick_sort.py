import random

def swap(a, i0, i1):
    c = a[i1]
    a[i1] = a[i0]
    a[i0] = c

def partition(a, l0, hi):
    pivot = a[hi]
    i = l0
    for j in range(l0, hi):
        if a[j] <= pivot:
            swap(a, i, j)
            i += 1
    swap(a, i, hi)
    return i

def quicksort(a, l0, hi):
    if l0 >= hi or l0 < 0:
        return
    p = partition(a, l0, hi)
    quicksort(a, p + 1, hi)
    quicksort(a, l0, p - 1)

n = 100000
l = []

for i in range(1, n + 1):
    l.append(i)

random.seed(12)
for i in range(n - 1, -1, -1):
    j = random.random()
    swap(l, i, int(j * n))
    
quicksort(l, 0, n - 1)
