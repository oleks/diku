module Tests where

import Eft

import Test.Tasty
import Test.Tasty.QuickCheck

properties :: TestTree
properties = testGroup "QuickCheck"
  [ testProperty "" $
    \ds -> foldl' growexp ds ==
      foldl' (\es d -> expsum es [d]) ds
  , testProperty "expsum is associative" $
    \ds -> foldl' (\es d -> expsum es [d]) ds ==
      foldl' (\es d -> expsum [d] es) ds
  , testProperty "growexp doesn't grow unboudedly" $
    \ds -> length (nozero $ foldl' growexp ds) < 41
  ]
  where
      foldl' :: ([Double] -> Double -> [Double]) -> [Double] -> [Double]
      foldl' f = nozero . foldl f []

tests :: TestTree
tests = testGroup "Tests" [properties]

main :: IO ()
main = defaultMain tests
