dayOfWeek :: Integer -> Integer -> Integer -> Integer
dayOfWeek y m d = z 
    where
        m' = if m <= 2 then m + 12 else m
        y' = if m' > 12 then y - 1 else y
        j = floor (fromIntegral (y') / 100)
        k = y' `mod` 100
        t1 = floor (fromIntegral (13 * (m' + 1)) / 5.0)
        t2 = floor (fromIntegral (k) / 4)
        t3 = floor (fromIntegral (j) / 4)
        z = (d + t1 + k + t2 + t3 + 5 * j) `mod` 7


sundays1 :: Integer -> Integer -> Integer
sundays1 start end = sundays' start 1
    where
        sundays' :: Integer -> Integer -> Integer
        sundays' y m
            | y > end = 0
            | otherwise = if dayOfWeek y m 1 == 1 then rest + 1 else rest
                where
                    nextY = if m == 12 then y + 1 else y
                    nextM = if m == 12 then 1 else m + 1
                    rest = sundays' nextY nextM
        
sundays1tr :: Integer -> Integer -> Integer
sundays1tr start end = sundaysIter start 1 0
    where 
        sundaysIter :: Integer -> Integer -> Integer -> Integer
        sundaysIter y m acc
            | y > end = acc
            | otherwise = if dayOfWeek y m 1 == 1 then rest (acc + 1) else rest acc
                where
                    nextY = if m == 12 then y + 1 else y
                    nextM = if m == 12 then 1 else m + 1
                    rest = sundaysIter nextY nextM 

leap :: Integer -> Bool
leap y = (y `mod` 4 == 0) && (y `mod` 100 /= 0) || (y `mod` 400 == 0)

daysInMonth :: Integer -> Integer -> Integer
daysInMonth m y
    | m == 2                 = if leap y then 29 else 28
    | m `elem` [4, 6, 9, 11] = 30
    | otherwise              = 31
                   
sundays2 :: Integer -> Integer -> Integer
sundays2 start end = sundaysIter start 1 (dayOfWeek start 1 1) 0
    where
        sundaysIter :: Integer -> Integer -> Integer -> Integer -> Integer
        sundaysIter y m weekDay acc
            | y > end = acc
            | otherwise = if weekDay `mod` 7 == 1 then rest (acc + 1) else rest acc

                where
                    nextY = if m == 12 then y + 1 else y
                    nextM = if m == 12 then 1 else m + 1
                    rest = sundaysIter nextY nextM (weekDay + (daysInMonth m y) `mod` 7)

getFunction :: String -> (Integer -> Integer -> Integer)
getFunction name
    | name == "sundays1" = sundays1
    | name == "sundays1tr" = sundays1tr
    | name == "sundays2" = sundays2
    | otherwise = error "unknown function"
           
    
    
main :: IO ()
main = do
    line <- getLine
    let [f, start, end] = words line
    putStrLn $ show $ (getFunction f) (read start :: Integer) (read end :: Integer)