# Some algorithms for computing sums.
#
# 1. Nicholas J. Higham. The Accuracy Of Floating Point Summation. SIAM J. Sci.
# Comput., Vol 14, pp. 783--799. 1993.

options(digits=20)

builtin <- function (xs) {
  # Built-in implementation.
  return (sum(xs))
}

recursive <- function (xs) {
  sum <- 0.0
  for (x in xs) {
    sum <- sum + x
  }
  return (sum)
}

insertmin <- function (xs) {
  N <- length(xs)
  for (i in 1:(N - 1)) {

    i1 <- which.min(xs)
    x1 <- xs[i1]
    xs <- xs[-i1]

    i2 <- which.min(xs)
    x2 <- xs[i2]
    xs <- xs[-i2]

    xs <- append(xs, x1 + x2)
  }
  return(xs)
}

insertmax <- function (xs) {
  N <- length(xs)
  for (i in 1:(N - 1)) {

    i1 <- which.max(xs)
    x1 <- xs[i1]
    xs <- xs[-i1]

    i2 <- which.max(xs)
    x2 <- xs[i2]
    xs <- xs[-i2]

    xs <- append(xs, x1 + x2)
  }
  return(xs)
}

testSums <- function(xs) {
  x1 <- builtin(xs)
  x2 <- recursive(xs)
  x3 <- insertmin(xs)
  x4 <- insertmax(xs)
  z <- x1 - x2
  a <- exp(x1)
  b <- exp(x2)
  c <- a - b
  return (c(x1, x2, x3, x4))#, z, a, b, c))
}

testOrders <- function(xs) {

  original <- testSums(xs)
  nondecr <- testSums(sort(xs, decreasing = FALSE))
  nonincr <- testSums(sort(xs, decreasing = TRUE))
  abs_nondecr <- testSums(xs[order(abs(xs), decreasing = FALSE)])
  abs_nonincr <- testSums(xs[order(abs(xs), decreasing = TRUE)])

  return (matrix(c(
    original,
    nondecr,
    nonincr,
    abs_nondecr,
    abs_nonincr
  ), nrow=4))
}

set.seed(1337)
n <- 4096
#testOrders(runif(n, min = 0, max = n))
testOrders(rnorm(n, mean = 0, sd = 1))
#testOrders(rnorm(n, mean = 0, sd = 1))
#testOrders(rlnorm(n, meanlog = 0, sdlog = 1))
#testOrders(rlogis(n, location = 0, scale = 1))
#testOrders(rexp(n, rate = 1))
