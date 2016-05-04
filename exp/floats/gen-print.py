#!/usr/bin/env python3

import sys, subprocess

N_DIGITS = 1
BUF_SIZE = 4

def genCFile(number):
  sys.stdout.write(".")
  sys.stdout.flush()
  cfile = open("print.c", "w")

  cfile.write("#include <stdio.h>\n#include<string.h>\n\n")

  cfile.write("int main() {\n")
  cfile.write("  char buffer[" + str(BUF_SIZE) + "];\n")
  cfile.write("  char *buf = buffer;\n\n")

  cfile.write("  snprintf(buf, " + str(BUF_SIZE) + \
                  ", \"%.0" + str(N_DIGITS) + "f\\n\", " + \
                  number + ");\n")
  cfile.write(
    "  if (strcmp(buf, \"" + number + "\") != 0) {\n" + \
    "    printf(\"\\n%s (read) != " + number + \
          " (written)\\n\", buf);\n" + \
    "  }\n\n")
  cfile.write("  return 0;\n}\n")
  cfile.close()

  p1 = subprocess.Popen("make", shell=True, stdout=subprocess.PIPE)
  p1.wait()

  p2 = subprocess.Popen("./print.bin", shell=True, stdout=subprocess.PIPE)
  p2.wait()

def genPrintfsAux(depth, number):
  if depth == 0:
    genCFile(number)
    return

  if depth == 1:
    print()
    print(number + "_")

  for i in range(10):
    genPrintfsAux(depth - 1, number + str(i))

def genPrintfs():
  genPrintfsAux(N_DIGITS, "0.")

def main():
  global N_DIGITS
  global BUF_SIZE

  if len(sys.argv) > 1:
    N_DIGITS = int(sys.argv[1])

  BUF_SIZE = N_DIGITS + 3

  genPrintfs()
  print()

if __name__ == "__main__":
  main()
