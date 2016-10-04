module FPPrint where

import Data.Char ( intToDigit )
import Data.Word ( Word64 )
import Data.List ( intercalate )
import Numeric ( showHex, showIntAtBase )
import Unsafe.Coerce ( unsafeCoerce )

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
eshow f = (mapM_ putStrLn) . (map f)
