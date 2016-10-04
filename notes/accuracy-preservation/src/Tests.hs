module Tests where

import Eft

import Test.Tasty
import Test.Tasty.QuickCheck

properties :: TestTree
properties = testGroup "QuickCheck"
  [ testProperty "esum doesn't grow unboudedly" $
    \ds -> length (esum ds) < 41
  ]

tests :: TestTree
tests = testGroup "Tests" [properties]

main :: IO ()
main = defaultMain tests
