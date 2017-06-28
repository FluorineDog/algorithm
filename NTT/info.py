#!/bin/python
from gmpy import *

def powp(n, exp, p):
  if(exp == 0):
    return 1
  tmp = powp(n, exp//2, p)
  if exp%2 == 0:
    return tmp * tmp % p
  else:
    return tmp * tmp * n % p

def main():
  n = 2**20
  mk = 2**8
  prime_arr = [ (i,p) for (i, p) in [(i, i*n+1) for i in range(mk+0,mk+20)] if is_prime(p) ]
  k, p = prime_arr[0]
  print(prime_arr)
  root_arr = [root for root in [i**k % p for i in range(2,22)] if powp(root,n//2,p) == p-1]
  root = root_arr[0]
  rootRev = powp(root, p-2, p)
  NRev = powp(n, p-2, p)
  print(root, rootRev, p)
  print(n, NRev)
  # rootRev = root ** (p-2) % p
  # arr = [root**i%p for i in range(0,16)]
  # print(root, rootRev)
  # print(arr)
main()

