# Bad Variance function.

# Classical example, occurs in:
#
# 1. Seydel, Rüdiger. Tools for computational finance. Berlin: Springer, 2006.
# Exercise 1.4 on page 53.
#
# 2. Nicholas J. Higham. Accuracy and Stability of Numerical Algorithms, 2002.
# Section 1.9, page 11.
#
# 3. Donald Knuth. The Art of Computer Programming, Vol. 2: Seminumerical
# Algorithms. 23rd printing, 2008. Section 4.2.2, page 232.

mv1 <- function (xs) {
  # Built-in implementation.
  return (c(mean(xs), var(xs)))
}

mv2 <- function (xs) {
  # Supposed to be a good, two-loop implementation.
  n <- length(xs)

  sum <- 0.0
  for (x in xs) {
    sum <- sum + x
  }
  mean <- sum / n

  varsum <- 0.0
  for (x in xs) {
    varsum <- varsum + (x - mean)^2
  }
  var <- varsum / (n - 1)

  return (c(mean, var))
}

mv3 <- function(xs) {
  # Supposed to be a bad, one-loop implementation.
  n <- length(xs)

  sum <- 0.0
  sqsum <- 0.0
  for (x in xs) {
    sum <- sum + x
    sqsum <- sqsum + x^2
  }

  mean <- sum / n
  var <- (sqsum - (sum^2 / n)) / (n - 1)

  return (c(mean, var))
}

mv4 <- function(xs) {
  # Supposed to be a good, one-loop implementation.
  n <- length(xs)

  a <- xs[1]
  b <- 0.0
  for (i in 2:length(xs)) {
    b <- b + ((i-1)*(xs[i]-a)^2)/i
    a <- a + (xs[i]-a)/i
  }

  mean <- a
  var <- b / (n - 1)

  return (c(mean, var))
}

testMvs <- function(xs) {
  return (data.frame(
    mv1(xs), mv2(xs), mv3(xs), mv4(xs)))
}

testOrders <- function(xs) {

  mv0 <- testMvs(xs)

  xs <- sort(xs)
  mv1 <- testMvs(xs)

  xs <- rev(xs)
  mv2 <- testMvs(xs)

  return (c(mv0, mv1, mv2))
}

set.seed(1337)
n <- 100
testOrders(runif(n, min = 0, max = n))
testOrders(rnorm(n, mean = 0, sd = 1))
testOrders(rnorm(n, mean = 0, sd = 1))
testOrders(rlnorm(n, meanlog = 0, sdlog = 1))
testOrders(rlogis(n, location = 0, scale = 1))
testOrders(rexp(n, rate = 1))
