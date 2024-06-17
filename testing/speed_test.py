
# def main():
to_find = 100000
primes = [2]
num = 3
while len(primes) < to_find:
    for i in range(len(primes)):
        if num % primes[i] == 0:
            break

        if primes[i]*primes[i] > num:
            primes.append(num)
            break

    num += 2

print(primes[-1])


# if __name__ == '__main__':
#     main()