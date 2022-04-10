NAME := gridgraph
PRIORITY_QUEUE_TEST_NAME := pq_test

DEPENDENCIES_FILE := dep.d

TEST_RESULTS_FOLDER := ./test_results

PRIORITY_QUEUE_SOURCE := priority_queue.c
PRIORITY_QUEUE_TEST_SOURCE := ../Tests/priority_queue_test.c

SOURCES := $(wildcard *.c)
OBJECTS := $(SOURCES:%.c=%.o)



all: dependencies compile clean_after_compile



dependencies:
	cc -MM $(SOURCES) > $(DEPENDENCIES_FILE)

-include $(DEPENDENCIES_FILE)

compile: $(OBJECTS)
	cc -o $(NAME) $(OBJECTS)

clean_after_compile:
	rm $(OBJECTS) $(DEPENDENCIES_FILE)



clean:
	rm $(NAME) $(OBJECTS) $(DEPENDENCIES_FILE)



test: all
	rm -r $(TEST_RESULTS_FOLDER)
	mkdir $(TEST_RESULTS_FOLDER)
	@echo
	@echo T1
	./gridgraph -w -xw 5 -xh 5 -f $(TEST_RESULTS_FOLDER)/test1
	@echo
	@echo T2
	./gridgraph -w -xw 1000 -xh 1000 -f $(TEST_RESULTS_FOLDER)/test2
	@echo
	@echo T3
	./gridgraph -w -xw 50 -xh 50 -s 0 -f $(TEST_RESULTS_FOLDER)/test3
	./gridgraph -w -xw 50 -xh 50 -s 0 -f $(TEST_RESULTS_FOLDER)/test4
	cmp $(TEST_RESULTS_FOLDER)/test3 $(TEST_RESULTS_FOLDER)/test4
	@echo $$?
	cmp $(TEST_RESULTS_FOLDER)/test3 ../Tests/expected_test3
	@echo $$?
	@echo
	@echo T4
	./gridgraph -w -xw 50 -xh 50 -Cmax 1 -f $(TEST_RESULTS_FOLDER)/test5
	./gridgraph -r -c -f $(TEST_RESULTS_FOLDER)/test5 > $(TEST_RESULTS_FOLDER)/test6
	cmp $(TEST_RESULTS_FOLDER)/test6 ../Tests/expected_test6
	@echo $$?
	@echo
	@echo T5
	./gridgraph -w -xw 50 -xh 50 -Cmin 4 -f $(TEST_RESULTS_FOLDER)/test7
	./gridgraph -r -c -f $(TEST_RESULTS_FOLDER)/test7 > $(TEST_RESULTS_FOLDER)/test8
	cmp $(TEST_RESULTS_FOLDER)/test8 ../Tests/expected_test8
	@echo $$?
	@echo
	@echo T6
	./gridgraph -w -xw 50 -xh 50 -Wmin 0.3 -Wmax 0.7 -f $(TEST_RESULTS_FOLDER)/test9
	@echo
	@echo T7
	./gridgraph -w -xw 100 -xh 100 -Cmin 1 -Cmax 3 -Wmin 0.4 -Wmax 0.9 -s 0 -f $(TEST_RESULTS_FOLDER)/test10
	cmp $(TEST_RESULTS_FOLDER)/test10 ../Tests/expected_test10
	@echo $$?
	./gridgraph -r -sA 0 -f $(TEST_RESULTS_FOLDER)/test10 > $(TEST_RESULTS_FOLDER)/test11
	cmp $(TEST_RESULTS_FOLDER)/test11 ../Tests/expected_test11
	@echo $$?
	@echo
	@echo T8
	cc -o $(PRIORITY_QUEUE_TEST_NAME) $(PRIORITY_QUEUE_SOURCE) $(PRIORITY_QUEUE_TEST_SOURCE)
	./pq_test 1000 $(TEST_RESULTS_FOLDER)/test12
	rm $(PRIORITY_QUEUE_TEST_NAME)