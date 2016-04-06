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

testSums <- function(xs) {
  x <- builtin(xs)
  y <- recursive(xs)
  z <- x - y
  a <- exp(x)
  b <- exp(y)
  c <- a - b
  return (c(x, y, z, a, b, c))
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
  ), nrow=6))
}

set.seed(1337)
n <- 4096
#testOrders(runif(n, min = 0, max = n))
testOrders(rnorm(n, mean = 0, sd = 1))
#testOrders(rnorm(n, mean = 0, sd = 1))
#testOrders(rlnorm(n, meanlog = 0, sdlog = 1))
#testOrders(rlogis(n, location = 0, scale = 1))
#testOrders(rexp(n, rate = 1))
