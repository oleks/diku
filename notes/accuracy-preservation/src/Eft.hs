module Eft where

-- Knuth 1997
twosum :: Double -> Double -> (Double, Double)
twosum a b =
  let x     = (+) a   b
      b'    = (-) x   a
      a'    = (-) x   b'
      b''   = (-) b   b'
      a''   = (-) a   a'
      y     = (+) a'' b''
  in  (x, y)

-- Shewchuk 1997
growexp :: [Double] -> Double -> [Double]
growexp es b =
  let
    ps = scanl (\ (_, q) e -> twosum q e) (0.0, b) es
    vs = tail $ map fst ps
    vn = snd $ last ps
  in vs ++ [vn]

nozero :: [Double] -> [Double]
nozero = filter (/= 0.0)

esum :: [Double] -> [Double]
esum = nozero . foldl growexp []

-- Shewchuk 1997
expsum :: [Double] -> [Double] -> [Double]
expsum es [0.0] = es  -- fast
expsum [0.0] fs = fs  -- fast
expsum es fs =
  let (xs, ys) = foldl expsum' ([], es) fs
  in reverse xs ++ ys
  where
    expsum' (hs', hs) f =
      let (h:hs'') = growexp hs f
      in  if h == 0.0     -- fast
          then (hs', hs'')
          else (h:hs', hs'')
