echo 'Testing comment counter...'

echo 'should be 0'
./comment_counter ./comment_counter_test_suite/test_0.cpp
echo 'should be 1'
./comment_counter ./comment_counter_test_suite/test_1.cpp
echo 'should be 2'
./comment_counter ./comment_counter_test_suite/test_2.cpp
echo 'should be 3'
./comment_counter ./comment_counter_test_suite/test_3.cpp



echo 'Test end'
