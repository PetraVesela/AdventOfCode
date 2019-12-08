import System.IO
import Data.List

readNumbers :: [String] -> [Integer]
readNumbers = map read

getFuel :: Integer -> Integer
getFuel x = x `div` 3 - 2



d1 = do
    contents <- readFile "inputs/1.txt"
    let singleLines = words contents
        list = readNumbers singleLines
    
    print $ sum [getFuel x| x <- list]
