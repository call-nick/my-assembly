./decoder < "test/001.in" &> "result.txt"
if cmp -s "result.txt" "test/001.out";
    then echo "Test passed"
    else echo "Test failed"
fi
rm "result.txt"