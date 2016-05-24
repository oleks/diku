printf <- function(...) invisible(print(sprintf(...)))

account <- exp(1) - 1;
printf("%f", account);
for (i in 1:25) {
  account = i * account - 1;
  printf("%f", account);
}
