findFloor :: String -> Int
findFloor [] = 0
findFloor (n:ns) 
    | n == '(' = findFloor ns + 1
    | n == ')' = findFloor ns - 1
    | otherwise = findFloor ns

findPosition :: String -> [Char] -> [Char] -> Int
findPosition [] _ _ = 0
findPosition (n:ns) m o
    | n == '(' = if findPositionAux (n : m) o /= 0 then findPositionAux (n : m) o else  findPosition ns (n : m) o
    | n == ')' = if findPositionAux m (n : o) /= 0 then findPositionAux m (n : o) else findPosition ns m (n : o)
    | otherwise = 0

findPositionAux :: [Char] -> [Char] -> Int
findPositionAux [] [] = 0
findPositionAux a b
    | length a - length b == -1 = length a + length b
    | otherwise = 0

main = do
    input <- getLine
    putStrLn (show (findFloor input))
    putStrLn (show (findPosition input [] []))
