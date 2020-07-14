import Data.Char (toLower)
import Data.List (nub, subsequences, permutations)
import Data.Set (Set)
import qualified Data.Set as Set
import Prelude hiding (Word)
import Data.Map (Map, assocs, differenceWith)
import qualified Data.Map as Map

type Word = String
type Sentence = [Word]
type CharCounts = [(Char, Int)]

-- I really try to comment, but everything is as its simplest form
-- already. The functions are just the sentences in the pdf spelled
-- in Haskell. Sorry, if this is not what you are expecting to see.

wordCharCounts :: Word -> CharCounts
wordCharCounts w = [(c, (length . filter (==c)) w') | c <- chars w] 
    where
        lower = map toLower
        chars = nub . lower
        w' = lower w


sentenceCharCounts :: Sentence -> CharCounts
sentenceCharCounts = wordCharCounts . foldl (++) []

dictCharCounts :: [Word] -> [CharCounts]
dictCharCounts = map wordCharCounts

dictWordsByCharCounts :: [CharCounts] -> [Word]
dictWordsByCharCounts = map wordFromCharCount
    where wordFromCharCount cc = foldl (++) [] [replicate (snd item) (fst item) | item <- cc]


wordAnagrams :: Word -> [Word] -> [Word]
wordAnagrams word wordList = anagrams
    where 
        mappedCharCounts = Map.fromList . wordCharCounts
        currentWordCharCounts = mappedCharCounts word
        anagrams = [w | w <- wordList, mappedCharCounts w == currentWordCharCounts]

charCountsSubsets :: CharCounts -> [CharCounts]
charCountsSubsets cc = dictCharCounts combsWODuplicates
    where
        combinations k ns = filter ((k==).length) $ subsequences ns
        word = head $ dictWordsByCharCounts [cc]
        allCombs = foldl (++) [] [combinations i word | i<-[0..length word]]
        removeDuplicates :: Ord a => [a] -> [a]
        removeDuplicates = Set.toList . Set.fromList
        combsWODuplicates = removeDuplicates allCombs

subtractCounts :: CharCounts -> CharCounts -> CharCounts
subtractCounts first second = Map.toList $ differenceWith f first' second'
    where
        f al ar = if al - ar == 0 then Nothing else Just (al - ar)
        first' = Map.fromList first
        second' = Map.fromList second

-- I couldn't find a way to complete this function. I have everything I need
-- but combining them here is just too much confusing for me. 
sentenceAnagrams :: Sentence -> [Word] ->[Sentence]
sentenceAnagrams s wordList = sentenceAnagramIter (concat s) [] 
    where
        sentenceAnagramIter "" acc     = acc
        sentenceAnagramIter (c:cs) acc = acc ++ [wordAnagrams (head $ dictWordsByCharCounts [s]) $ dictWordsByCharCounts $ dictCharCounts wordList' |  s <- subsets [c]] ++ sentenceAnagramIter cs acc
        wordList' = ["naber", "brena", "be", "are", "eb", "berna"]
        -- subsets = charCountsSubsets $ wordCharCounts "berna"
        -- allSubsets = charCountsSubsets . sentenceCharCounts
        subsets = charCountsSubsets . wordCharCounts

        -- subset = head allSubsets
        -- dictWords = dictWordsByCharCounts subset
        -- allPermutations = map permutations $ subsequences "sahin"
        -- anagrams = [wordAnagrams (head $ dictWordsByCharCounts [s]) $ dictWordsByCharCounts $ dictCharCounts wordList' |  s <- allSubsets]
        -- x = wordAnagrams (head s) $ dictWordsByCharCounts $ dictCharCounts s




main :: IO ()
main = do
    putStrLn "I couldn't complete this part because I didn't really understand how should I write sentenceAnagrams\n\
             \function. It was confusing for me."
    