#!/bin/python
def main():
  p = 3*2**12 + 1
  print("pp=", p) 
  root = 11*11*11
  rootRev = root ** (p-2) % p
  arr = [root**i%p for i in range(0,16)]
  print(root, rootRev)
  print(arr)
main()
