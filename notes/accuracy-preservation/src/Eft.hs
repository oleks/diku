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

-- Dekker 1971
split :: Double -> (Double, Double)
split a =
  let c   = 2097153 * a
      ab  = c - a
      ahi = c - ab
      alo = a - ahi
  in (ahi, alo)

-- Dekker 1971
twomul :: Double -> Double -> (Double, Double)
twomul a b =
  let x = a * b
      (ahi, alo) = split a
      (bhi, blo) = split b
      e1 = x - (ahi * bhi)
      e2 = e1 - (alo * bhi)
      e3 = e2 - (ahi * blo)
      y = (alo * blo) - e3
  in (x, y)

-- Shewchuk 1997
scaleexp :: [Double] -> Double -> [Double]
scaleexp [] _ = []
scaleexp (e:es) b =
  let (q, h) = twomul e b
      (q', hs) = foldl scale' (q, [h]) es
  in  q':hs
  where
    scale' (q, hs) x =
      let
        (thi, tlo) = twomul x b
        (q', h') = twosum q tlo
        (q'', h'') = twosum thi q'
      in (q'', h'':h':hs)


expdiv :: [Double] -> Double -> [Double]
expdiv xs d =
  let (cs, rs) = foldl expdiv' ([], []) xs
  in  (reverse rs) ++ cs
  where
    expdiv' (cs, ys) x =
      let
        (r:cs') = expsum [x] cs
        y = r / d
        (r', cs''') = twomul y d
        cs'' = r - r'
        cs'''' = growexp (growexp cs' cs'') cs'''
      in (cs'''', y:ys)
