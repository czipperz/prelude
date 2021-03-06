{-# LANGUAGE CPP #-}

import Development.Shake
import Development.Shake.Command
import Development.Shake.FilePath
import Development.Shake.Util

src, test, srcout, testout :: FilePath
src = "src"
test = "test"
srcout = "out"
testout = "testout"

cflags, ldflags :: String
#ifndef cxx
#define cxx "clang++"
#endif
cflags = "-std=c++98 -g " ++
         "-Wold-style-cast -Wnon-virtual-dtor -Wnarrowing " ++
         "-Wdelete-non-virtual-dtor -Wctor-dtor-privacy " ++
         "-Woverloaded-virtual -Wsign-promo -Wall"
ldflags = "-lboost_regex -lncurses -lpthread -lboost_filesystem -lboost_system"

srctoos dir files = [takeAllButDirectory 2 c </> dir </> dropAllButDirectory 1 c -<.> "o" | c <- files]

main :: IO ()
main = shakeArgs shakeOptions{shakeFiles=srcout{-, shakeThreads=0-}} $ do
  want [testout </> srcout <.> exe]

  testout </> srcout <.> exe %> \out -> testRoutine
  phony test $ do testRoutine

  phony "clean" $
    removeFilesAfter srcout ["//*"] >>
    removeFilesAfter testout ["//*"] >>
    removeFilesAfter "." ["//~*", "//#*#"]

  phony "doc" $ cmd "doxygen" ["Doxyfile"]

  phony "tags" $ getSourceAndHeaders >>= cmd "etags"

  "//" ++ testout </> "*.o" %> compile test
  "//" ++ srcout </> "*.o" %> compile src

testRoutine = do
    sources <- getDir src
    tests <- getDir test
    let srcos = srctoos srcout sources
    let testos = srctoos testout tests
    let os = srcos ++ testos
    need os
    () <- cmd cxx "-o" [testout </> srcout <.> exe] os ldflags
    cmd $ "./" ++ testout </> srcout <.> exe

compile :: FilePath -> FilePath -> Action ()
compile dir out = do
    let includeDirectories = "-I" ++ src
    let c = takeAllButDirectory 2 out </> dir </> dropAllButDirectory 1 out -<.> "cc"
    let m = out -<.> "m"
    () <- cmd cxx "-c" [c] "-o" [out] cflags "-MMD -MF" [m] includeDirectories
    needMakefileDependencies m

getSourceAndHeaders :: Action [FilePath]
getSourceAndHeaders = getDirectoryFiles src ["//*.cc","//*.hh"]

getDir :: FilePath -> Action [FilePath]
getDir dir = getDirectoryFiles dir ["//*.cc"]

split :: (Eq a) => a -> [a] -> [[a]]
split = split' []
  where split' ll _ [] = [reverse ll]
        split' ll e (x:xs) | e == x = reverse ll : split' [] e xs
        split' ll e (x:xs) = split' (x:ll) e xs

dropAllBut, takeAllBut :: Int -> [a] -> [a]
dropAllBut i xx = drop (length xx - i) xx
takeAllBut i xx = take (length xx - i) xx

dropDirectory, dropAllButDirectory, takeDirectory, takeAllButDirectory :: Int -> String -> String
dropDirectory = fun drop
dropAllButDirectory = fun dropAllBut
takeDirectory = fun take
takeAllButDirectory = fun takeAllBut
fun :: (t -> [String] -> [String]) -> t -> String -> String
fun f n s = let res = f n (split '/' s) in
  if null res then "" else foldr1 (\l r -> l ++ '/' : r) res
