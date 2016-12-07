# Catastrophic Cancellation

In the context of numerical analysis, "catastrophic cancellation" refers to the
act of of terms not "cancelling out", due to insufficiently precise arithmetic.
That is, terms that would otherwise "cancel out", don't.

This lack of "cancellation" is not bad in and of itself. The result is close
enough, but if this result is used in subsequent computation, it can have
"catastrophic" effects on the accuracy of the overall result.
