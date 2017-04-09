ALGORITHM ANALYSIS PROJECT README
---------------------------------
05-06-7670 Umut BENZER
05-07-8496 Ozlem GURSES
05-07-8569 Savas YILDIZ
---------------------------------

How to run?
-----------

1. Open Command Prompt (cmd)
2. Type: 
	java -jar "LocationOfJarFile\AlgorithmAnalysis.jar" [PARAMS]
	
Parameters
----------
p1 inputFileName outputFileName [sampleCount]
p2 inputFileName outputFileName [sampleCount]
p1benchmark outputFileName sampleCount fromItem toItem stepSize
p2benchmark outputFileName sampleCount fromItem toItem fromCapacity toCapactiy

Parameters that are surrounded with [] are optional.

Some examples...
-----------------
java -jar "C:\AlgorithmAnalysis.jar" p1 input_part1.txt output_part1.txt
java -jar "C:\AlgorithmAnalysis.jar" p1 input_part1.txt output_part1.txt 2000
java -jar "C:\AlgorithmAnalysis.jar" p2 input_part2.txt output_part2.txt
java -jar "C:\AlgorithmAnalysis.jar" p2 input_part2.txt output_part2.txt 2000
java -jar "C:\AlgorithmAnalysis.jar" p1benchmark part1bench.txt 1000 0 10000 2000
java -jar "C:\AlgorithmAnalysis.jar" p2benchmark part2bench.txt 1000 0 10 0 50

Some Notes
----------
* JRE 6 is required.
* Returned times are all in nanoseconds. (since for some inputs, algorithms work faster than ms scales)

