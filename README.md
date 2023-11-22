
## Report
Include the following in this section of your README.md file:
* Information about your data set. You will be assigned a different grader for this project.
* Create graphs for the number of reads for inserting your dataset into all 20 hash tables.
  * Clearly label the graph titles and axes.
  * Set up the graph in a way that makes the most sense to you. Here are some options I have seen before:
    * Using a line graph to track the *individual* read counts as each insertion is made. High-valued blips happen in open addressing when rehashes occur.
    * Using a line graph to track the *cumulative* read count as each insertion is made. Vertical jumps happen in open addressing when rehashes occur.
    * Using a line graph to track the *average* number of reads per insertion, where each hash table has one value and you can see the trends as the initial table size grows.
* Using the graphs, analyze why the read counts are different for the different size hash tables. Use what you know about your keys and the hash tables to justify why the read counts make sense.
* Determine which getKey function works best on your dataset based on the read counts.
* Draw conclusions about which hash collision detection method works best on your dataset (separate chaining or open addressing).

**Note: Any code that was not authored by yourself or the instructor must be cited in your report. This includes the use of concepts not taught in lecture.**

## Submit
You must include your source (all .cpp and .h) files, your data (.csv) file(s), your output file(s), CMakeLists.txt, and your updated README.md file that contains your report to your repository. Submit to Gradescope using the GitHub repository link, double-check that all the correct files are there, and wait for the autograder to provide feedback.

## Grading
The project is out of 70 points.

| Points Possible | Description of requirement                                                    |
|------------------- |-------------------------------------------------------------------------------|
| 5 pts | Program compiles and runs.                                                    |
| 5 pts | Code style. Readable, naming style is consistent, comments where appropriate. |
| 5 pts | Hashed at least 1000 objects using separate chaining.                         |
| 15 pts | Hashed at least 1000 objects using open addressing other than linear probing. |
| 5 pts | Used at least 5 different hash table sizes, as specified above.               |
| 5 pts | Used two getKey functions, as specified above.                                |
| 10 pts | Recorded the number of reads for each type of hashing.                        |
| 15 pts | Analyzed the results and wrote about everything outlined above.               |
| 5 pts | Report: professional, grammatically correct, cites sources.                   |