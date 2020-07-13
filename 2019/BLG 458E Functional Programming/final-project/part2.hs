import Data.Char (toLower, isDigit, digitToInt)

data Color = Red | Black deriving (Eq, Show)
data Suit = Clubs | Diamonds | Hearts | Spades deriving (Eq, Show)
data Rank = Num Int | Jack | Queen | King | Ace deriving (Eq, Show)
data Card = Card { suit :: Suit, rank :: Rank } deriving (Eq, Show)
data Move = Draw | Discard Card deriving (Eq, Show)
type State = [Card]    

myCards = [Card Diamonds Jack, Card Diamonds (Num 5), Card Hearts Queen,
           Card Spades Ace, Card Clubs Jack]

cardColor :: Card -> Color
cardColor card = if suit card `elem` [Spades, Clubs] then Black else Red

cardValue :: Card -> Int
cardValue card = case rank card of
    Num i -> i
    Ace   -> 11
    _     -> 10

removeCard :: State -> Card -> State
removeCard [] _           = error "card not in list"
removeCard (c:cs) removed = if c == removed then cs else c:removeCard cs removed

allSameColor :: State -> Bool
allSameColor []     = True
allSameColor (c:cs) =  and $ map(\c' -> cardColor c' == cardColor c) cs

sumCards :: State -> Int
sumCards cs = sumIter cs 0
    where
        sumIter [] acc = acc
        sumIter (c:cs') acc = sumIter cs' (acc + cardValue c)

score :: State -> Int -> Int
score cs goal = if allSameColor cs then floor (fromIntegral (pre_scr) / 2) else pre_scr
    where
        sum = sumCards cs
        pre_scr = if sum > goal then 3 * (sum - goal) else goal - sum

runGame :: [Card] -> [Move] -> Int -> Int
runGame cs ms goal = score (playMoves cs ms []) goal
    where 
        playMoves :: [Card] -> [Move] -> State -> State
        playMoves _ [] hcl = hcl
        playMoves cl (m:ms') hcl = case m of
            Discard c -> playMoves cl ms' (removeCard hcl c)
            Draw      -> if null cl || sumCards ((head cl):hcl) >= goal then ((head cl):hcl) else playMoves (tail cl) ms' (head cl: hcl)

convertSuit :: Char -> Suit
convertSuit c = case (toLower c) of
    'c' -> Clubs
    'd' -> Diamonds
    'h' -> Hearts
    's' -> Spades
    _  -> error $ "unknown suit: " ++ show c

convertRank :: Char -> Rank
convertRank c = case (toLower c) of
    '1' -> Ace
    'j' -> Jack
    'q' -> Queen
    'k' -> King
    't' -> Num 10
    d   -> if isDigit d && digitToInt d > 1 then Num (digitToInt d) else error $ "unknown rank: " ++ show c

convertCard :: Char -> Char -> Card
convertCard s r = Card (convertSuit s) (convertRank r)

readCards :: IO [Card]
readCards = do
    cards <- getCards []
    return cards
        where
            getCards cs = do
                line <- getLine
                if line == "." then do
                    return cs
                else do
                    let [s,r] = line
                    let c = convertCard s r
                    getCards (c:cs)

convertMove :: Char -> Char -> Char -> Move
convertMove m s r = case (toLower m) of
    'd' -> Draw
    'r' -> Discard (convertCard s r)
    _   -> error "invalid input"
    

readMoves :: IO [Move]
readMoves = do
    moves <- getMoves []
    return moves
        where
            getMoves ms = do
                line <- getLine
                if line == "." then do
                    return ms
                else do
                    let line' = take 3 $ concat $ replicate 3 line
                    let [c, s, r] = line'
                    let m = convertMove c s r
                    getMoves (m:ms) 

    
main :: IO ()
main = do 
    putStrLn "Enter cards:"
    cards <- readCards
    putStrLn (show cards)
    putStrLn "Enter moves:"
    moves <- readMoves
    putStrLn (show moves)
    putStrLn "Enter goal:"
    line <- getLine
    let goal = read line :: Int
    let score = runGame cards moves goal
    putStrLn ("Score: " ++ show score)
