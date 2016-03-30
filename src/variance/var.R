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
  m <- 0.0
  for (x in xs) {
    m <- m + x
  }
  m <- m / length(xs)
  v <- 0.0
  for (x in xs) {
    v <- v + (x - m)^2
  }
  return (c(m, v/(length(xs) - 1)))
}

mv3 <- function(xs) {
  # Supposed to be a bad, one-loop implementation. 
  s <- 0.0
  sq <- 0.0
  for (x in xs) {
    s <- s + x
    sq <- sq + x^2
  }

  return (c(s/length(xs), (sq-(s^2/length(xs)))/(length(xs)-1)))
}

mv4 <- function(xs) {
  # Supposed to be a good, one-loop implementation.
  a <- xs[1]
  b <- 0.0
  for (i in 2:length(xs)) {
    b <- b + ((i-1)*(xs[i]-a)^2)/i
    a <- a + (xs[i]-a)/i
  }
  return (c(a, b/(length(xs)-1)))
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
