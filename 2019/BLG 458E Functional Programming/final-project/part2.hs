import Data.Char (toLower, isDigit, digitToInt)

data Color = Red | Black deriving (Eq, Show)
data Suit = Clubs | Diamonds | Hearts | Spades deriving (Eq, Show)
data Rank = Num Int | Jack | Queen | King | Ace deriving (Eq, Show)
data Card = Card { suit :: Suit, rank :: Rank } deriving (Eq, Show)
data Move = Draw | Discard Card deriving (Eq, Show)
data State = Playing | Finished  -- State of the game is either Playing or Finished

-- It is said that "You have to explain *everything* in detail"
-- but I won't do it in some parts of my code because I think 
-- they are self explanatory. For example the following line
-- don't need any explanation I think:

-- if c == removed then cs else c:removeCard cs removed

-- If I would do it, it would be basically repeating the code
-- in human language: 
-- if current card is to be removed return tail of cards else 
-- combine head with the result of calling this function on tail.


cardColor :: Card -> Color
cardColor card = if suit card `elem` [Spades, Clubs] then Black else Red

cardValue :: Card -> Int
cardValue card = case rank card of
    Num i -> i
    Ace   -> 11
    _     -> 10 -- This is safe because a card is created by convertCard function and
                -- it will take care of invalid inputs

removeCard :: [Card] -> Card -> [Card]
removeCard [] _           = error "card not in list" -- removing anything from empty list will result in an error
removeCard (c:cs) removed = if c == removed then cs else c:removeCard cs removed

allSameColor :: [Card] -> Bool
allSameColor []     = True                   -- assume that an empty card list is all same color
allSameColor (c:cs) =  and $ map(\c' -> cardColor c' == cardColor c) cs -- check the colors of the cards at the tail of the list against
                                                                        -- the color of head card. Applying 'and' function to the result
                                                                        -- will make it terminate on first False value. And it will return
                                                                        -- True only when all the items mapped to True.

sumCards :: [Card] -> Int
sumCards cs = sumIter cs 0
    where
        sumIter [] acc = acc
        sumIter (c:cs') acc = sumIter cs' (acc + cardValue c)

score :: [Card] -> Int -> Int
score cs goal = if allSameColor cs then floor (fromIntegral (pre_scr) / 2) else pre_scr
    where
        sum = sumCards cs
        pre_scr = if sum > goal then 3 * (sum - goal) else goal - sum

runGame :: [Card] -> [Move] -> Int -> Int
runGame cs ms goal = score (playMoves cs ms [] Playing) goal
    where 
        playMoves :: [Card] -> [Move] -> [Card] ->  State -> [Card] -- This function will start by held-cards being empty list
                                                        -- and will return the held-cards, when the State becomes Finished or no moves left.

        playMoves _ [] hcl _       = hcl                -- if no moves left, return the held-cards
        playMoves _ _ hcl Finished = hcl                -- if state is changed to Finished, return the held-cards
        playMoves cl (m:ms') hcl s = case m of
            Discard c -> playMoves cl ms' (removeCard hcl c) s -- if move is discard some card c, remove it from the held-cards and continue playing
            Draw      -> if null cl then -- if move is draw and no more cards left
                            playMoves cl ms' hcl Finished -- the game state changes to Finished to signal the end of the game
                        else
                            if sumCards ((head cl):hcl) >= goal then -- else if sum of the cards exceeds the goal after drawing a card from card list
                                playMoves (tail cl) ms' (head cl: hcl) Finished -- the game ends after drawing the card from card list
                            else playMoves (tail cl) ms' (head cl: hcl) s  -- else pop the top card of card-list and append it to the held-cards and continue playing 


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
                    let line' = take 3 $ concat $ replicate 3 line -- this will replicate whatever entered 3 times and take the first 3 chars
                    let [c, s, r] = line'                          -- so that this operation will be always safe
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
