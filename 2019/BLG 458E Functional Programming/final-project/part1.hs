-- (math question) Is the number of weeks in 400 years an integer value? In other words, is the number of days
-- in 400 years a multiple of 7? 

-- Yes, it is. We can calculate how many days in 400 years like this:
-- assume every year is 365 days so number of days is equal to 365 * 400
-- assume every year that is divisable by 4 is leap year. So 400 / 4 = 100 leap years, 365 * 400 + 100 days
-- subtract years that are multiple of 100 as they are not leap year. 400 / 100 = 4 non leap year, 365 * 400 + 100 - 4
-- if a year is multiple of 400, it is actually a leap year. There is always a year which is multiple of 400 in 400 years
-- so 365 * 400 + 100 - 4 + 1 = 146097 days which is multiple of 7.


-- If so, what is the possibility that a certain day of a month (such as 1 Jan, or your
-- birthday) is a Sunday (or some other day)? Are all days equally possible?

-- No, they are not equally possible. Let's consider a day, 29th Feb. 
-- Number of 29th Feb's in 400 years = Number of leap years in 400 years = 100 - 4 + 1 = 97
-- 97 is not divisable by 7, the days can not be equally possible on 29th Feb.
-- Since the weekdays are not equally possible for one day, they cannot be equally possible in
-- any other days. 


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

-- What does the helper function (sundays') calculate?

-- it iterates over every month of every year from start year to end year while adding
-- 1 to the result on every sunday.


-- What if you don't define a "rest" and use its expression where it's needed?
    
-- I would need to update 'otherwise' part as:
-- otherwise = if dayOfWeek y m 1 == 1 then sundays' nextY nextM + 1 else sundays' nextY nextM
-- and it would still work same. Actually, I have a feeling that I misunderstood the question
-- because I can't see any difference in terms of performance, evaluation order etc.
        
sundays1tr :: Integer -> Integer -> Integer
sundays1tr start end = sundaysIter start 1 0 -- set accumulated value as 0 and call sundaysIter
    where 
        sundaysIter :: Integer -> Integer -> Integer -> Integer
        sundaysIter y m acc
            | y > end = acc  -- when the function ends, return the accumulated value
            | otherwise = if dayOfWeek y m 1 == 1 then rest (acc + 1) else rest acc -- increase accumulated value by 1 if this is a sunday
                where                                                               -- then recurse
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