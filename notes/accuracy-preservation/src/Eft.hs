module Eft where

newtype ECDouble = ECDouble (Double, [Double])
  deriving (Show)

-- Knuth 1997
sum2 :: Double -> Double -> (Double, Double)
sum2 a b =
  let x     = (+) a   b
      b'    = (-) x   a
      a'    = (-) x   b'
      b''   = (-) b   b'
      a''   = (-) a   a'
      y     = (+) a'' b''
  in  (x, y)

nsum :: [Double] -> ECDouble
nsum xs = foldl sum' (ECDouble (0.0, [])) xs
  where
    sum' (ECDouble (r1, es)) x =
      let (r2, e2) = sum2 r1 x
      in  ECDouble (r2, e2:es)

opt :: ECDouble -> ECDouble
opt (ECDouble (x, es)) =
  let (ECDouble (e', es')) = nsum es
      es'' = filter (/= 0.0) $ es'
  in  ECDouble (x, e':es'')
