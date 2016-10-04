module Eft where

import Data.Char ( intToDigit )
import Data.Word ( Word64 )
import Data.List ( intercalate )
import Numeric ( showHex, showIntAtBase )
import Unsafe.Coerce ( unsafeCoerce )

newtype ECDouble = ECDouble (Double, [Double])
  deriving (Show)

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

nozero :: [Double] -> [Double]
nozero = filter (/= 0.0)

esum :: [Double] -> [Double]
esum = nozero . foldl growexp []

-- Useful for debugging

hex :: Double -> String
hex d = "0x" ++ (showHex ((unsafeCoerce d)::Word64) "")

bin :: Double -> String
bin d =
  let
    raw = showIntAtBase 2 intToDigit ((unsafeCoerce d)::Word64) ""
    pad = take (64 - length raw) $ repeat '0'
    bits = pad ++ raw
    s = take 1 bits
    e = take 11 $ drop 1 bits
    f = drop 12 bits
  in
    intercalate " " [s, e, f]

eshow :: (Double -> String) -> [Double] -> IO ()
eshow f = (mapM_ putStrLn) . (map f) . nozero
