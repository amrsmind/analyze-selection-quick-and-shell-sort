# analyze-selection-quick-and-shell-sort
using  c++ ........ plotted performance

testing three sorting algorithms (Selection, Quick and Shell sort). Sorter Class should sort any
data type (Generic). The class will have methods to support experimenting
and analyzing sorting algorithms performance.

GenerateRandomList(min, max, size) Generate a given
number of random integer data from a certain range. For example,
one can generate a vector/array of 10000 integer numbers that fall
in the range from 1 to 100000, e.g., [5554, 32300, 98000, 342, …]

3. GenerateReverseOrderedList(min, max, size) Generate a
given number of reverse ordered integer data from a certain range.
You can first generate random data and then sort them reversed

4. RunOnce(sorter, data, size) Run a given sorting algorithm on a
given set of data and calculate the time taken to sort the data

5. RunAndAverage(sorter, type, min, max, size, sets_num)
Run a given sorting algorithm on several sets of data of the same
length and same attributes (from the same range and equally
sorted; e.g., random or reversed) and calculate the average time

6. RunExperient (sorter, type, min, max, min_val, max_val,
sets_num, step) Develop an experiment to run a given sorting
algorithm and calculate its performance on sets of different sizes
(e.g., data of size 10000, 20000, etc.) as follows:

i) All sets are generated with values between min and max

ii) First, generate sets_num sets with size min_val. Use
RunAndAverage () and record average time to process the sets

iii) Next, repeat step ii but with sets whose size increases by step till
reaching max_val. Each time record average time to process the
sets

iv) For example I should be able to design an experiment to run
Quick sort algorithm on randomly sorted integers data taken
from the range (1 to 1,100,000) and with input value (data size)
from 0 to 100000, with step 5000. This means we will run the
algorithms on data sets of 5000, 10000, 15000, …, 100000
randomly sorted integers. Note that with each step you will
generate sets_num different sets and take the average of their
runs
