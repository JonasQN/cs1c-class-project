#!/bin/bash

g++ -I../src VectorUnitTest.cpp -lgtest -o VectorUnitTest

valgrind ./VectorUnitTest
